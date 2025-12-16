#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string_view>
#include <numeric>
#include <cassert>

bool symbol_line(const std::string& line);

void update_symbol_vec(const std::string& line,
                       std::vector<std::string>& symbol_vec);

size_t get_columns_count(const std::string& line);
std::vector<size_t> get_columns_widths(const std::string& symbols);                      
void update_column_partitions(const std::vector<size_t>& columns_widths,
                const std::vector<std::string>& num_vec,
                std::vector<std::vector<std::string>>& column_partitions);
std::vector<std::vector<size_t>> get_each_column_numbers(
                const std::vector<std::vector<std::string>>& column_partitions);
std::vector<size_t> get_numbers(const std::vector<std::string>& column);
std::vector<size_t> apply_operation(
                      const std::vector<std::string>& symbol_vec, 
                      const std::vector<std::vector<size_t>>& numbers);

int main() {
    std::string file_name{"Day_6_input.txt"};
    std::ifstream file{file_name};
    std::vector<std::string> num_vec;
    std::string symbols;
    std::string line;
    while (std::getline(file, line)) {
        if (symbol_line(line)) { // bottom line which contains symbols + *
            symbols = line;
        }
        else {
            num_vec.push_back(line);
        }
    }
    std::vector<std::string> symbol_vec;
    update_symbol_vec(symbols, symbol_vec);
    std::vector<size_t> columns_widths = get_columns_widths(symbols);
    size_t num_of_columns = get_columns_count(symbols);
    assert(num_of_columns == columns_widths.size());
    
    std::vector<std::vector<std::string>> num_partitions_vec(num_of_columns);
    update_column_partitions(columns_widths, num_vec, num_partitions_vec);

    std::vector<std::vector<size_t>> numbers;
    numbers = get_each_column_numbers(num_partitions_vec);

    std::vector<size_t> results = apply_operation(symbol_vec, numbers);
    size_t total = std::accumulate(results.begin(), results.end(), size_t{0});
    std::cout << "total = " << total << std::endl;
    
    return 0;
}

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

std::vector<size_t> get_columns_widths(const std::string& symbols) {
    std::vector<size_t> widths;
    std::size_t plus_pos = symbols.find("+");
    std::size_t star_pos = symbols.find("*");
    auto last_symbol_pos = std::min(plus_pos, star_pos);
    for (auto i{last_symbol_pos + 1}; i < symbols.size(); ++i) {
        if (symbols.at(i) != ' ') {
            widths.push_back(i - last_symbol_pos - 1);
            last_symbol_pos = i;
        }
    }
    widths.push_back(symbols.size() - last_symbol_pos);
    return widths;
}

size_t get_columns_count(const std::string& line) {
    size_t num_of_columns{0};
    std::string symbol;
    std::stringstream line_ss{line};
    while (line_ss >> symbol) {
        ++num_of_columns;
    }
    return num_of_columns;
}

void update_column_partitions(const std::vector<size_t>& columns_widths,
                const std::vector<std::string>& num_vec,
                std::vector<std::vector<std::string>>& column_partitions) {
    for (const auto& line : num_vec) {
        size_t pos{0};
        for (auto i{0}; i < columns_widths.size(); ++i) {
            auto width = columns_widths.at(i);
            auto partition = line.substr(pos, width);
            column_partitions.at(i).push_back(partition);
            pos += width + 1;
        }
    }
}

std::vector<std::vector<size_t>> get_each_column_numbers(
        const std::vector<std::vector<std::string>>& column_partitions) {
    std::vector<std::vector<size_t>> 
            numbers_per_column;
    for(auto i{0}; i < column_partitions.size(); ++i) {
        auto column = column_partitions.at(i);
        std::vector<size_t> numbers = get_numbers(column);
        numbers_per_column.push_back(numbers);
    }
    return numbers_per_column;
}

std::vector<size_t> get_numbers(const std::vector<std::string>& column) {
    std::vector<size_t> numbers(column.at(0).size(), 0);
    for (auto i{0}; i < column.size() ; ++i) {
        std::string s = column.at(i);
        //std::cout << "s size = " << s.size();
        //std::cout << "numbers size = " << numbers.size() << std::endl;
        for (auto j{0}; j < s.size(); ++j) {
            size_t n = numbers.at(j);
            if (s.at(j) != ' ') {
                numbers.at(j) = 10 * n + static_cast<size_t>(std::stoi(s.substr(j,1)));                
            } 
        }
    }
    return numbers;
}

std::vector<size_t> apply_operation(
                      const std::vector<std::string>& symbol_vec, 
                      const std::vector<std::vector<size_t>>& numbers) {
    std::vector<size_t> results;
    for (auto i{0}; i < symbol_vec.size(); ++i) {
        std::vector<size_t> v = numbers.at(i);
        if (symbol_vec.at(i) == "+") {
            size_t sum = std::accumulate(v.begin(), v.end(), size_t{0});
            results.push_back(sum);
        }
        else {
            size_t product = std::accumulate(v.begin(), v.end(), size_t{1}, std::multiplies<size_t>());
            results.push_back(product);
        }   
    }
    return results;
}