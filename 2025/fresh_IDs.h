#ifndef FRESH_IDS_H
#define FRESH_IDS_H
#include <set>
#include <vector>

using IDs = std::set<size_t>;
using ID_Ranges = std::vector<std::pair<size_t, size_t>>;

void add_fresh_IDs(size_t start, size_t end, ID_Ranges& fresh_ID_ranges);
void sort_ID_ranges(ID_Ranges& fresh_ID_ranges);
void print_ID_ranges(const ID_Ranges& fresh_ID_ranges);
ID_Ranges compute_merged_ID_ranges(const ID_Ranges& fresh_ID_ranges);
size_t compute_fresh_IDs_total(const ID_Ranges& id_ranges);

#endif