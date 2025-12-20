#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cassert>
#include "playground.h"


int main() {
    std::string file_name{"Day_8_input.txt"};
    std::ifstream file{file_name};
    Positions positions;
    get_data(file, positions);
    PriorityQueue pq;
    sort_data(pq, positions);
    std::set<Position> unconnected_positions{get_unconnected_positions(positions)};
    Circuits circuits;
    int number_of_pairs{1000};
    auto [p1, p2] = create_single_circuit(pq, circuits, unconnected_positions);
    assert(circuits.size() == 1);
    auto result = p1.x * p2.x;
    std::cout << "result = " << result << std::endl; 
    return 0;
}