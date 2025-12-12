#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <map>

using Grid = std::vector<std::string>;
using Position = std::pair<size_t, size_t>;

void print_grid(const Grid& grid);
std::map<Position, std::vector<Position>> get_neighbours(const Grid& grid);
size_t count_accessible_rolls(const Grid& grid, 
    const std::map<Position, std::vector<Position>>& position_neighbours_map);
void print_neighbors_map(const std::map<Position, std::vector<Position>>& neighbors_map);


int main() {
    std::string file_name{"Day_4_Printing_Department.txt"};
    std::ifstream file{file_name};
    std::string line;
    Grid grid;
    while (std::getline(file, line)) {
        grid.push_back(line);
    }
    //print_grid(grid);
    std::map<Position, std::vector<Position>> neighbours_map = get_neighbours(grid);
    std::cout << count_accessible_rolls(grid, neighbours_map) << std::endl;
    //print_neighbors_map(neighbours_map);
    return 0;
}

void print_grid(const Grid& grid) {
    for (const auto& line : grid) {
        std::cout << line << std::endl;
    }
}

std::map<Position, std::vector<Position>> get_neighbours(const Grid& grid) {
    auto number_of_rows = grid.size();
    auto number_of_columns = grid.at(0).size();
    std::map<Position, std::vector<Position>> position_neighbours_map;
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

size_t count_accessible_rolls(const Grid& grid, 
    const std::map<Position, std::vector<Position>>& position_neighbours_map) {
    size_t total_accessible_rolls{0};
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
                    ++total_accessible_rolls;
                }
            }
        }        
    }
    return total_accessible_rolls;
}

void print_neighbors_map(const std::map<Position, std::vector<Position>>& neighbors_map) {
    for (auto [key, neighbours] : neighbors_map) {
        std::cout << "(" << key.first << "," << key.second << ") : ";
        for (auto v : neighbours) {
            std::cout << "(" << v.first << "," << v.second << ") ";
        }
        std::cout << std::endl;
    }
}