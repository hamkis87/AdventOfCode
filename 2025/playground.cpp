#include "playground.h"

#include <sstream>
#include <cmath>
#include <algorithm>

bool Position::operator<(const Position& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
}

float Position::distance(const Position& other) const {
        float x_diff = x - other.x;
        float y_diff = y - other.y;
        float z_diff = z - other.z;
        return sqrtf(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
}

void Position::print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")";
}

bool CompareBySecond::operator()(
        const std::pair<std::pair<Position, Position>, float>& a,
        const std::pair<std::pair<Position, Position>, float>& b) const {
        return a.second > b.second;
}

void get_data(std::ifstream& file, Positions& positions) {
    std::string line;
    while(file >> line) {
        std::stringstream line_ss{line};
        char c;        
        Position p;
        if (line_ss >> p.x && line_ss >> c && line_ss >> p.y &&
            line_ss >> c && line_ss >> p.z) {
            positions.push_back(p);            
        }
        else {
            throw std::runtime_error("Invalid input data");
        }
        if (positions.size() == 0) {
            throw std::runtime_error("No input data");
        }
    }
}

void sort_data(PriorityQueue& pq, const Positions& positions) {
    for(auto i{0}; i < positions.size(); ++i) {
        const Position& p1 = positions[i];
        for (auto j{i + 1}; j < positions.size(); ++j) {
            const Position& p2 = positions[j];
            pq.emplace(std::make_pair(p1, p2), p1.distance(p2));
        }
    }
}

void print_closest_points(PriorityQueue pq, int k) {
    while (!pq.empty() && k >= 0) {
        const auto& [pair, dist] = pq.top();
        const auto& [p1, p2] = pair;
        p1.print();
        std::cout << ", ";
        p2.print();
        std::cout << " distance: " << dist << std::endl;
        pq.pop();
        --k;        
    }
}

std::pair<Position, Position> create_single_circuit(PriorityQueue& pq, Circuits& circuits, 
                   std::set<Position>& unconnected_positions) {
    auto [pair, _] = pq.top();
    auto [p1, p2] = pair;
    Circuit c;
    c.insert(p1);
    c.insert(p2);
    circuits.push_back(c);
    pq.pop();
    unconnected_positions.erase(p1);
    unconnected_positions.erase(p2);
    int i{1};
    std::pair<Position, Position> last_connected;
    while (!pq.empty() && !unconnected_positions.empty()) {
        ++i;
        auto [pair, _] = pq.top();
        auto [p1, p2] = pair;
        pq.pop();
        size_t p1_circuit_id = get_circuit_id(p1, circuits);
        size_t p2_circuit_id = get_circuit_id(p2, circuits);
        bool p1_is_connected = p1_circuit_id < circuits.size();
        bool p2_is_connected = p2_circuit_id < circuits.size();
        if (p1_is_connected) {
            if (p2_is_connected) {
                if (p1_circuit_id == p2_circuit_id) { 
                    continue;
                }
                else {
                    auto min_id = std::min(p1_circuit_id, p2_circuit_id);
                    auto max_id = std::max(p1_circuit_id, p2_circuit_id);
                    merge_two_circuits(circuits, min_id, max_id);
                    last_connected = std::make_pair(p1, p2);
                }
            }
            else {
                circuits.at(p1_circuit_id).insert(p2);
                last_connected = std::make_pair(p1, p2);
                unconnected_positions.erase(p2);
            }
        }
        else if (p2_is_connected) {
            circuits.at(p2_circuit_id).insert(p1);
            last_connected = std::make_pair(p1, p2);
            unconnected_positions.erase(p1);                     
        }
        else {
            Circuit c;
            c.insert(p1);
            c.insert(p2);
            circuits.push_back(c);
            last_connected = std::make_pair(p1, p2);
            unconnected_positions.erase(p1);
            unconnected_positions.erase(p2);
        }
    }
    return last_connected;
}

size_t get_circuit_id(const Position& p, const Circuits& circuits) {
    for (size_t i{0}; i < circuits.size(); ++i) {
        if (circuits.at(i).count(p) == 1) {
            return i;
        }
    }
    return circuits.size();
}

void merge_two_circuits(Circuits& circuits, size_t min_id, size_t max_id) {
    for (const auto & p : circuits.at(max_id)) {
        circuits.at(min_id).insert(p);
    }
    circuits.erase(circuits.begin() + max_id);
}

void print_circuits_info(const Circuits& circuits) {
    std::cout << "No. of circuits = " << circuits.size() << std::endl;
    for (auto i{0}; i < circuits.size(); ++i) {
        std::cout << "circuit " << i << ": ";
        std::cout << "Number of boxes = ";
        std::cout << circuits[i].size();
        std::cout << std::endl;
    }
}

void sort_circuits(Circuits& circuits) {
    std::sort(circuits.begin(), circuits.end(),
          [](const Circuit& a, const Circuit& b) {
              return a.size() > b.size();
          });
}

size_t get_result(const Circuits& circuits) {
    size_t size1 = circuits.at(0).size();
    size_t size2 = circuits.at(1).size();
    size_t size3 = circuits.at(2).size();
    return size1 * size2 * size3;
}

std::set<Position> get_unconnected_positions(const Positions& positions) {
    std::set<Position> unconnected_positions;
    for (const auto& p: positions) {
        unconnected_positions.insert(p);
    }
    return unconnected_positions;
}
