#ifndef ROLLS_H
#define ROLLS_H
#include <string>
#include <vector>
#include <map>

using Grid = std::vector<std::string>;
using Position = std::pair<size_t, size_t>;
using PositionsVev = std::vector<Position>;
using PositionsMap = std::map<Position, PositionsVev>;

void print_grid(const Grid& grid);
PositionsMap get_neighbours(const Grid& grid);
std::pair<size_t, PositionsVev>  find_accessible_rolls(const Grid& grid, 
    const PositionsMap& position_neighbours_map);
void print_neighbors_map(const PositionsMap& neighbors_map);
void remove_rolls(Grid& grid, const PositionsVev& positions);

#endif