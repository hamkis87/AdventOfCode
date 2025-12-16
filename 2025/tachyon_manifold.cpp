#include "tachyon_manifold.h"
#include <iostream>
#include <fstream>
#include <cassert>

TachyonManifold::TachyonManifold(std::string file_name) {
    std::ifstream file{file_name};
    std::string line;
    while (file >> line) {
        diagram.push_back(line);
    }
    num_of_rows = diagram.size();
    num_of_columns = diagram.at(0).size();
    for (const auto& line : diagram) {
        assert(num_of_columns == line.size());
    }
    initialize();
}

void TachyonManifold::initialize() {
    size_t beam_entry_pos = diagram.at(0).find('S');
    if (beam_entry_pos == std::string::npos) {
        throw std::runtime_error("No beam entry");
    }
    Location beam_location = {current_row, beam_entry_pos};
    beams_locations = {beam_location};
    std::ofstream out_file{out_file_name};
    out_file << "Diagram of the tachyon manifold:" << std::endl;
    for (const auto& line : diagram) {
        out_file << line << std::endl; 
    }
    print_info();
}

void TachyonManifold::run_process() {
    while (move()) {
        update_diagram();
        print();
    }
    std::cout << "the beam is split " << split_count << " times." << std::endl;
}

bool TachyonManifold::move() {
    if (current_row >= num_of_rows - 1) {
        return false;
    }
    std::set<Location> new_beams_locations;    
    for (const auto & [x, y] : beams_locations) {
        char downward_object = diagram.at(x + 1).at(y);
        if (downward_object == '.') {
            Location downward_beam_location = {x + 1, y};
            new_beams_locations.insert(downward_beam_location);
        }
        else if (downward_object == '^') {
            Location downward_beam_location1 = {x + 1, y - 1};
            Location downward_beam_location2 = {x + 1, y + 1};
            if (y > 0) {
                new_beams_locations.insert(downward_beam_location1);
            }
            if (y < num_of_columns - 1) {
                new_beams_locations.insert(downward_beam_location2);
            }
            ++split_count;                        
        }  
    }
    ++current_row;
    beams_locations = new_beams_locations;
    return true;
}

void TachyonManifold::update_diagram() {
    for (const auto& [x, y] : beams_locations) {
        diagram.at(x).at(y) = '|';
    }
}

void TachyonManifold::print_info() const {
    std::cout << "current row = " << current_row << std::endl;
    std::cout << "Beam locations :" << std::endl;
    std::cout << "*******************************" << std::endl;
    for (const auto& [x,y] : beams_locations) {
        std::cout << "(" << x << ", " << y << ")" << std::endl; 
    }
    std::cout << "*******************************" << std::endl;
}

void TachyonManifold::print() {
    std::ofstream out_file;
    out_file.open(out_file_name, std::ios::app);
    if (!out_file) {
        throw std::runtime_error("output file not opened");
    }
    out_file << "Diagram of the tachyon manifold:" << std::endl;
    for (const auto& line : diagram) {
        out_file << line << std::endl; 
    }
}