#include "trash.h"
#include <sstream>
#include <iostream>

bool symbol_line(const std::string& line) {
    std::stringstream line_ss{line};
    std::string data;
    if (line_ss >> data) {
        return data.at(0) == '+' || data.at(0) == '*';
    }
    else {
        throw std::runtime_error("Invalid input data");
    }    
}

void update_symbol_vec(const std::string& line,
                       std::vector<std::string>& symbol_vec) {
    std::stringstream line_ss{line};
    std::string symbol;
    while (line_ss >> symbol) {
        symbol_vec.push_back(symbol);
    }
}

void update_num_vecs(const std::string& line, 
                     std::vector<std::int64_t>& add_vec,
                     std::vector<std::int64_t>& mul_vec) {
    std::stringstream line_ss{line};
    std::int64_t number;
    std::vector<std::int64_t> numbers;
    while (line_ss >> number) {
        numbers.push_back(number);
    }
    if (add_vec.size() == 0) {
        for (auto & x : numbers) {
            add_vec.push_back(x);
            mul_vec.push_back(x);
        }
    }
    else {
        if (numbers.size() != add_vec.size() ||
            numbers.size() != add_vec.size()) {
            throw std::runtime_error("Inconsistent amount of input numbers");
        }
        for (auto i{0}; i < numbers.size(); ++i) {
            add_vec.at(i) += numbers.at(i);
            mul_vec.at(i) *= numbers.at(i);
        }
    }
}

template <typename T>
void print_vec(const std::vector<T>& vec) {
    for (auto& v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

template void print_vec<std::string>(const std::vector<std::string>&);
template void print_vec<std::int64_t>(const std::vector<std::int64_t>&);

std::vector<std::int64_t> get_results(
                          const std::vector<std::string>& symbol_vec,
                          const std::vector<std::int64_t>& add_vec,
                          const std::vector<std::int64_t>& mul_vec) {
    std::vector<std::int64_t> result;
    for (auto i{0}; i < symbol_vec.size(); ++i) {
        if (symbol_vec.at(i) == "+") {
            result.push_back(add_vec.at(i));
        }
        else {
            result.push_back(mul_vec.at(i));
        }
    }
    return result;
}

std::int64_t get_total(const std::vector<std::int64_t>& vec) {
    std::int64_t total{0};
    for (const auto& x: vec) {
        total += x;
    }
    return total;
}