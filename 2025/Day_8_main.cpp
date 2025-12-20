#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "playground.h"


int main() {
    std::string file_name{"Day_8_input.txt"};
    //std::string file_name{"Day_8_test.txt"};
    std::ifstream file{file_name};
    Positions positions;
    get_data(file, positions);
    PriorityQueue pq;
    sort_data(pq, positions);
    PriorityQueue pq2{pq};
    Circuits circuits;
    int number_of_pairs{1000};
    connect_pairs(pq, circuits, number_of_pairs);
    sort_circuits(circuits);
    size_t result = get_result(circuits);
    std::cout << "result is " << result << std::endl;
    return 0;
}