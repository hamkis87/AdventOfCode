#include <iostream>
#include <fstream>
#include <sstream>
#include "trash.h"

int main() {
    std::string file_name{"Day_6_input.txt"};
    //std::string file_name{"Day_6_test_input.txt"};
    std::ifstream file{file_name};
    std::vector<std::int64_t> add_vec;
    std::vector<std::int64_t> mul_vec;
    std::vector<std::string> symbol_vec;
    std::string line;
    while (std::getline(file, line)) {
        if (symbol_line(line)) { // bottom line which contains symbols + *
            update_symbol_vec(line, symbol_vec);
        }
        else {
            update_num_vecs(line, add_vec, mul_vec);
        }
    }
    //print_vec<std::string>(symbol_vec);
    //print_vec<std::int64_t>(add_vec);
    //print_vec<std::int64_t>(mul_vec);
    std::vector<std::int64_t> results = get_results(symbol_vec,
                                                    add_vec,
                                                    mul_vec);
    //print_vec<std::int64_t>(results);
    std::int64_t grand_total = get_total(results);
    std::cout << "grand total = " << grand_total << std::endl;
    return 0;
}