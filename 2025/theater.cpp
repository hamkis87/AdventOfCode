#include "theater.h"

#include <sstream>
#include <cstdlib>
#include <algorithm>

bool Location::operator<(const Location& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return false;
}

void Location::print() const {
        std::cout << "(" << x << ", " << y << ")";
}

Rectangle::Rectangle(const Location& c1, const Location& c2) :
    corner1{c1}, corner2{c2} { } 

size_t Rectangle::area() const {
        size_t x_diff = 1 + std::abs(static_cast<long long>(corner1.x) 
                            - static_cast<long long>(corner2.x));
        size_t y_diff = 1 + std::abs(static_cast<long long>(corner1.y) 
                            - static_cast<long long>(corner2.y));
        return x_diff * y_diff;
}

void Rectangle::print() const {
        std::cout << "(";
        corner1.print();
        std::cout << ", ";
        corner2.print();
        std::cout << ")";
}



bool CompareByArea::operator()(const Rectangle& a,
                               const Rectangle& b) const {
        return a.area() < b.area();
}

void get_data(std::ifstream& file, Locations& locations) {
    std::string line;
    while(file >> line) {
        std::stringstream line_ss{line};
        char c;        
        Location location;
        if (line_ss >> location.x && line_ss >> c && line_ss >> location.y) {
            locations.push_back(location);            
        }
        else {
            throw std::runtime_error("Invalid input data");
        }
        if (locations.size() == 0) {
            throw std::runtime_error("No input data");
        }
    }
}

void get_rectangles(const Locations& locations, Rectangles& rectangles) {
    for (auto i{0}; i < locations.size() - 1; ++i) {
        auto c1 = locations.at(i);
        for (auto j{i + 1}; j < locations.size(); ++j) {
            auto c2 = locations.at(j);
            rectangles.push_back(Rectangle(c1, c2));
        }
    }
}

Rectangle get_largest_rectangle(const Rectangles& rectangles) {
    PriorityQueue pq;
    for (const auto& r : rectangles) {
        pq.emplace(r);
    }
    return pq.top();
}

// void sort_data(PriorityQueue& pq, const Positions& positions) {
//     for(auto i{0}; i < positions.size(); ++i) {
//         const Position& p1 = positions[i];
//         for (auto j{i + 1}; j < positions.size(); ++j) {
//             const Position& p2 = positions[j];
//             pq.emplace(std::make_pair(p1, p2), p1.distance(p2));
//         }
//     }
// }


// void print_circuits_info(const Circuits& circuits) {
//     std::cout << "No. of circuits = " << circuits.size() << std::endl;
//     for (auto i{0}; i < circuits.size(); ++i) {
//         std::cout << "circuit " << i << ": ";
//         std::cout << "Number of boxes = ";
//         std::cout << circuits[i].size();
//         std::cout << std::endl;
//     }
// }
