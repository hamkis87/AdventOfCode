#ifndef TRASH_H
#define TRASH_H
#include <vector>
#include <string>
#include <cstdint>

bool symbol_line(const std::string& line);
void update_symbol_vec(const std::string& line,
                       std::vector<std::string>& symbol_vec);
void update_num_vecs(const std::string& line, 
                     std::vector<std::int64_t>& add_vec,
                     std::vector<std::int64_t>& mul_vec);
std::vector<std::int64_t> get_results(
                          const std::vector<std::string>& symbol_vec,
                          const std::vector<std::int64_t>& add_vec,
                          const std::vector<std::int64_t>& mul_vec);
std::int64_t get_total(const std::vector<std::int64_t>& vec);

template <typename T>
void print_vec(const std::vector<T>& vec);

#endif