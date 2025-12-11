#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <set>
#include <map>
#include <vector>
#include <numeric>
#include <cstdint>


using NumType = std::uint64_t;
using FactorsMap = std::map<NumType, std::vector<NumType>>;

FactorsMap compute_factors();
void check_invalid_ids(NumType min_id, 
                       NumType max_id,
                       std::set<NumType>& ids,
                       const FactorsMap& factors_map);
bool is_invalid_id(const std::string& num_as_str, 
                   const FactorsMap& factors_map);

int main() {
    FactorsMap factors_map = compute_factors();
    std::string file_name{"Day_2_Invalid_IDs.txt"};
    std::ifstream file{file_name};
    std::string id_range;
    std::set<NumType> invalid_ids;
    while (std::getline(file, id_range, ',')) {
        std::stringstream id_range_s{id_range};
        NumType min_id{0}; 
        NumType max_id{0};
        char dash;
        if (id_range_s >> min_id >> dash >> max_id) {
            check_invalid_ids(min_id, max_id, invalid_ids, factors_map);
        }
        else {
            std::cout << "Parse Error." << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    NumType invalid_ids_sum = std::accumulate(invalid_ids.begin(), invalid_ids.end(), 0ULL);
    std::cout << "total sum is " << invalid_ids_sum << std::endl;
    return 0;
}

void check_invalid_ids(NumType min_id, NumType max_id,
                       std::set<NumType>& ids, const FactorsMap& factors_map) {
    for (NumType i{min_id}; i <= max_id; ++i) {
        std::stringstream ss;
        std::string num_as_str;
        if (ss << i && ss >> num_as_str) {
            if (is_invalid_id(num_as_str, factors_map)) {
                ids.insert(i);
                //std::cout << i << std::endl;                
            }
        }
        else {
            std::cout << "Parse Error." << std::endl;
            std::exit(EXIT_FAILURE);            
        }     
    }
}

FactorsMap compute_factors() {
    FactorsMap result;
    NumType max_length_of_num = 15;
    for (NumType key{2ULL}; key < max_length_of_num; ++key) {
        NumType key_half = key / 2;
        std::vector<NumType> values;
        for (NumType value{1ULL}; value <= key_half; ++value) {
            if (key % value == 0) {
                values.push_back(value);
            }
        }
        result.emplace(key, values);
    }
    return result;
}

bool is_invalid_id(const std::string& num_as_str, 
                   const FactorsMap& factors_map) {
    size_t length = num_as_str.length();
    if (length < 2) {
        return false;
    }
    auto factors = factors_map.at(static_cast<NumType>(length));
    for (const auto& factor : factors) {
        bool result{true};
        size_t n = static_cast<size_t>(factor);
        auto num_as_str_partition = num_as_str.substr(0, n);
        for (size_t i{n}; i <= length - n; i += n) {
            auto next_partition = num_as_str.substr(i, n);
            if (num_as_str_partition != next_partition) {
                result = false;
                break;
            }
        }
        if (result) {
            return true;
        }       
    } 
    return false;
}
