#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>

using IDs = std::set<size_t>;
using ID_Ranges = std::vector<std::pair<size_t, size_t>>; 

void add_fresh_IDs(size_t start, size_t end, ID_Ranges& fresh_ID_ranges);
size_t count_fresh_IDs(const IDs& available_IDs, 
                       const ID_Ranges& fresh_ID_ranges);

int main() {
    //std::string file_name{"Day_5_Test.txt"};
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
            //std::cout << "from " << range_start;
            //std::cout << " to " << range_end << std::endl;
            fresh_ID_ranges.push_back(std::make_pair(start, end));
        }
        else {
            throw std::runtime_error("Invalid fresh ingredient ID ranges");
        }
    }
    // for (auto &i : fresh_IDs) {
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;
    size_t number;
    while (std::getline(file, line)) {
        std::stringstream line_ss{line};
        if (line_ss >> number) {
            //std::cout << number << std::endl;
            available_IDs.insert(number);
        }
        else {
            throw std::runtime_error("Invalid ingredient ID");
        }
    }
    size_t fresh_IDs_count = count_fresh_IDs(available_IDs, fresh_ID_ranges);
    std::cout << "total fresh IDs = " << fresh_IDs_count << std::endl;
    return 0;
}

size_t count_fresh_IDs(const IDs& available_IDs, 
                       const ID_Ranges& fresh_ID_ranges) {
    size_t total{0};
    for (auto & i : available_IDs) {
        for (const auto& [start, end] : fresh_ID_ranges) {
            if (i >= start && i <= end) {
                ++total;
                break;
            }
        }
    }
    return total;
}