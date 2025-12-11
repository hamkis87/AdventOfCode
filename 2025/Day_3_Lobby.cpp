#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>


int get_largest_joltage(const std::string& bank);


int main() {
    std::string file_name{"Day_3_Lobby.txt"};
    std::ifstream input_file{file_name};
    std::string line;
    int total{0};
    while (std::getline(input_file, line)) {
        int joltage = get_largest_joltage(line);
        total += joltage;
    }
    std::cout << "total is " << total << std::endl;
    return 0;
}

int get_largest_joltage(const std::string& bank) {
    auto begin_it = bank.begin();
    auto end_it = bank.end();
    auto tens_digit_it = std::max_element(begin_it, 
                                              begin_it + bank.length() - 1);
    auto ones_digit_it = std::max_element(tens_digit_it + 1, end_it);
    std::stringstream joltage_ss;
    int joltage;
    if (joltage_ss << *tens_digit_it << *ones_digit_it
            && joltage_ss >> joltage) {
        return joltage;
    }
    else {
        std::cout << "Parse Error." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}