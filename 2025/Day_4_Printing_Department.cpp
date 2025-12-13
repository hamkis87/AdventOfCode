#include <iostream>
#include <fstream>
#include "rolls.h"

int main() {
    std::string file_name{"Day_4_Printing_Department.txt"};
    std::ifstream file{file_name};
    std::string line;
    Grid grid;
    while (std::getline(file, line)) {
        grid.push_back(line);
    }
    PositionsMap neighbours_map = get_neighbours(grid);
    size_t total_removed_rolls{0};
    while (true) {
        auto [removed_rolls, positions] = find_accessible_rolls(grid, neighbours_map);
        if (removed_rolls == 0) {
            break;
        }
        total_removed_rolls += removed_rolls;
        remove_rolls(grid, positions);        
    }
    std::cout << "total removed rolls = " << total_removed_rolls << std::endl;

    return 0;
}