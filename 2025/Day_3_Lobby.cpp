#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>
#include <cstdint>


using NumType = std::uint64_t;

NumType get_largest_joltage(const std::string& bank);

int main() {
    std::string file_name{"Day_3_Lobby.txt"};
    std::ifstream input_file{file_name};
    std::string line;
    NumType total{0ULL};
    while (std::getline(input_file, line)) {
        NumType joltage = get_largest_joltage(line);
        total += joltage;
    }
    std::cout << "total is " << total << std::endl;
    return 0;
}

NumType get_largest_joltage(const std::string& bank) {
    auto begin_it = bank.begin();
    auto end_it = bank.end();
    std::stringstream joltage_ss;
    auto start_pos = begin_it;
    auto joltage_size = 12;
    for (auto i{joltage_size - 1}; i >= 0; --i) {
        auto digit_it = std::max_element(start_pos, 
                                         begin_it + bank.length() - i);
        if (joltage_ss << *digit_it) {
            auto pos = std::distance(begin_it, digit_it);
            start_pos = begin_it + (1 + pos);
        }
        else {
            throw std::runtime_error("Invalid joltage");
        }
    }
    NumType joltage;
    if (joltage_ss >> joltage) {
        return joltage;
    }
    else {
        throw std::runtime_error("Invalid joltage");
    }
}