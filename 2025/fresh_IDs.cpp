#include "fresh_IDs.h"
#include <iostream>
#include <algorithm>


void sort_ID_ranges(ID_Ranges& fresh_ID_ranges) {
    std::sort(fresh_ID_ranges.begin(), 
              fresh_ID_ranges.end(), 
              [](auto a, auto b) {
                                   return a.first < b.first;
                                  });
}

void print_ID_ranges(const ID_Ranges& fresh_ID_ranges) {
    for (const auto& [x, y]: fresh_ID_ranges) {
        std::cout << "(" << x << ", " << y << ") ";
    }
    std::cout << std::endl;
}

ID_Ranges compute_merged_ID_ranges(const ID_Ranges& fresh_ID_ranges) {
    ID_Ranges merged_ID_ranges;
    merged_ID_ranges.push_back(fresh_ID_ranges.at(0));
    size_t i{1};
    size_t j{0};
    
    while (i < fresh_ID_ranges.size()) {
        auto p = merged_ID_ranges.at(j);
        auto r = fresh_ID_ranges.at(i);
        auto [x1, y1] = p;
        auto [x2, y2] = r;
        if (y1 < x2) {
            merged_ID_ranges.push_back(r);
            ++i;
            ++j;
        }
        else if (y1 == x2) {
            merged_ID_ranges.pop_back();
            merged_ID_ranges.push_back(std::make_pair(x1, y2));
            ++i;
        }
        else { // when y1 > x2
            if (y1 <= y2) {
                merged_ID_ranges.pop_back();
                merged_ID_ranges.push_back(std::make_pair(x1, y2));
                ++i;
            }
            else { // when y1 > y2
                ++i;
            }
        }      
    }
    return merged_ID_ranges;
}

size_t compute_fresh_IDs_total(const ID_Ranges& id_ranges) {
    size_t total{0};
    for (const auto& [x, y] : id_ranges) {
        total += 1 + y - x;
    }
    return total;
}