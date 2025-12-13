#include "rolls.h"
#include <iostream>

void print_grid(const Grid& grid) {
    for (const auto& line : grid) {
        std::cout << line << std::endl;
    }
}

PositionsMap get_neighbours(const Grid& grid) {
    auto number_of_rows = grid.size();
    auto number_of_columns = grid.at(0).size();
    PositionsMap position_neighbours_map;
    // corners
    position_neighbours_map[{0,0}] = {{0,1}, {1,0}, {1,1}};
    position_neighbours_map[{0,number_of_columns-1}] = 
            {{0,number_of_columns-2}, {1,number_of_columns-1}, {1,number_of_columns-2}};
    position_neighbours_map[{number_of_rows-1,0}] = 
            {{number_of_rows-1,1}, {number_of_rows-2,0}, {number_of_rows-2,1}};
    position_neighbours_map[{number_of_rows-1,number_of_columns-1}] = 
            {{number_of_rows-1,number_of_columns-2}, 
             {number_of_rows-2,number_of_columns-1},
             {number_of_rows-2,number_of_columns-2}};
    // first row except corners
    for (auto j{1}; j < number_of_columns - 1; ++j) {
        auto key = std::make_pair(0, j);
        std::vector<Position> value;
        value.push_back(std::make_pair(0, j-1));
        value.push_back(std::make_pair(0, j+1));
        value.push_back(std::make_pair(1, j-1));
        value.push_back(std::make_pair(1, j));
        value.push_back(std::make_pair(1, j+1));
        position_neighbours_map.emplace(key, value);
    }
    // positions in the middle
    for (auto i{1}; i < number_of_rows - 1; ++i) {
        for (auto j{1}; j < number_of_columns - 1; ++j) {
            auto key = std::make_pair(i, j);
            std::vector<Position> value;
            // neighbours of row above
            value.push_back(std::make_pair(i-1, j-1));
            value.push_back(std::make_pair(i-1, j));
            value.push_back(std::make_pair(i-1, j+1));
            // neighbours on the same row
            value.push_back(std::make_pair(i, j-1));
            value.push_back(std::make_pair(i, j+1));
            // neighbours of row below
            value.push_back(std::make_pair(i+1, j-1));
            value.push_back(std::make_pair(i+1, j));
            value.push_back(std::make_pair(i+1, j+1));

            position_neighbours_map.emplace(key, value);            
        }
    }
    // last row except corners
    for (auto j{1}; j < number_of_columns - 1; ++j) {
        auto key = std::make_pair(number_of_rows - 1, j);
        std::vector<Position> value;
        value.push_back(std::make_pair(number_of_rows - 1, j-1));
        value.push_back(std::make_pair(number_of_rows - 1, j+1));
        value.push_back(std::make_pair(number_of_rows - 2, j-1));
        value.push_back(std::make_pair(number_of_rows - 2, j));
        value.push_back(std::make_pair(number_of_rows - 2, j+1));
        position_neighbours_map.emplace(key, value);
    }
    // first column except corners
    for (auto i{1}; i < number_of_rows - 1; ++i) {
        auto key = std::make_pair(i, 0);
        std::vector<Position> value;
        value.push_back(std::make_pair(i, 1));
        value.push_back(std::make_pair(i-1, 0));
        value.push_back(std::make_pair(i-1, 1));
        value.push_back(std::make_pair(i+1, 0));
        value.push_back(std::make_pair(i+1, 1));
        position_neighbours_map.emplace(key, value);
    }
    // last column except corners
    for (auto i{1}; i < number_of_rows - 1; ++i) {
        auto key = std::make_pair(i, number_of_columns - 1);
        std::vector<Position> value;
        value.push_back(std::make_pair(i, number_of_columns - 2));
        value.push_back(std::make_pair(i-1, number_of_columns - 1));
        value.push_back(std::make_pair(i-1, number_of_columns - 2));
        value.push_back(std::make_pair(i+1, number_of_columns - 1));
        value.push_back(std::make_pair(i+1, number_of_columns - 2));
        position_neighbours_map.emplace(key, value);
    }
    return position_neighbours_map;
}

std::pair<size_t, PositionsVev> find_accessible_rolls(const Grid& grid, 
    const PositionsMap& position_neighbours_map) {
    size_t total_accessible_rolls{0};
    PositionsVev positions_for_removal;
    size_t number_of_rows = grid.size();
    size_t number_of_columns = grid.at(0).size();
    for (size_t i{0}; i < number_of_rows; ++i) {
        for (size_t j{0}; j < number_of_columns; ++j) {
            auto key = std::make_pair(i,j);
            if (grid[i].at(j) == '@') {
                size_t number_of_neighbour_rolls{0};
                auto neighbors = position_neighbours_map.at(key);
                for (const auto & [x,y] : neighbors) {
                    if (grid[x].at(y) == '@') {
                        ++number_of_neighbour_rolls;                    
                    }                
                }
                if (number_of_neighbour_rolls < 4) {
                    positions_for_removal.push_back(key);
                    ++total_accessible_rolls;
                }
            }
        }        
    }
    return std::make_pair(total_accessible_rolls, positions_for_removal);
}

void print_neighbors_map(const PositionsMap& neighbors_map) {
    for (auto [key, neighbours] : neighbors_map) {
        std::cout << "(" << key.first << "," << key.second << ") : ";
        for (auto v : neighbours) {
            std::cout << "(" << v.first << "," << v.second << ") ";
        }
        std::cout << std::endl;
    }
}

void remove_rolls(Grid& grid, const PositionsVev& positions) {
    for (const auto& [x,y] : positions) {
        grid[x][y] = 'x';
    }
}