#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>

#include "fresh_IDs.h"

int main() {
    std::string file_name{"Day_5_Cafeteria.txt"};
    std::ifstream file{file_name};
    std::string line;
    ID_Ranges fresh_ID_ranges;
    IDs available_IDs;
    while (std::getline(file, line)) {
        if (line.empty()) {
            break;
        }
        std::stringstream line_ss{line};
        size_t start;
        char hyphen;
        size_t end;
        if (line_ss >> start >> hyphen >> end) {
            fresh_ID_ranges.push_back(std::make_pair(start, end));
        }
        else {
            throw std::runtime_error("Invalid fresh ingredient ID ranges");
        }
    }
    
    sort_ID_ranges(fresh_ID_ranges);
    ID_Ranges merged_ID_ranges = compute_merged_ID_ranges(fresh_ID_ranges);
    size_t fresh_IDs_count = compute_fresh_IDs_total(merged_ID_ranges);
    std::cout << "total fresh IDs = " << fresh_IDs_count << std::endl;
    return 0;
}