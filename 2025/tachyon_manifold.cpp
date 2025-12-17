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
    time_lines = {{beam_location, size_t{1}}};
    std::ofstream out_file{out_file_name};
    out_file << "Diagram of the tachyon manifold:" << std::endl;
    for (const auto& line : diagram) {
        out_file << line << std::endl; 
    }
}

void TachyonManifold::run_process() {
    while (move()) {
        update_diagram();
        print();
    }
    std::cout << "the beam is split " << split_count << " times." << std::endl;
    std::cout << "number of time lines " << count_time_lines() << std::endl;    

}

bool TachyonManifold::move() {
    if (current_row >= num_of_rows - 1) {
        return false;
    }
    std::set<Location> new_beams_locations;
    Timelines updated_time_lines;    
    for (const auto & [x, y] : beams_locations) {
        char downward_object = diagram.at(x + 1).at(y);
        Location upward_beam_location = {x,y};
        size_t upward_beam_count = time_lines.at(upward_beam_location);
        if (downward_object == '.') {
            Location downward_beam_location = {x + 1, y};
            new_beams_locations.insert(downward_beam_location);
            size_t downward_beam_count = upward_beam_count;
            if (updated_time_lines.count(downward_beam_location) > 0) {
                updated_time_lines.at(downward_beam_location) += downward_beam_count;
            }
            else {
                updated_time_lines[downward_beam_location] = downward_beam_count;
            }
        }
        else if (downward_object == '^') {
            Location downward_beam_location1 = {x + 1, y - 1};
            Location downward_beam_location2 = {x + 1, y + 1};
            if (y > 0) {
                new_beams_locations.insert(downward_beam_location1);
                size_t downward_beam_count = upward_beam_count;
                if (updated_time_lines.count(downward_beam_location1) > 0) {
                    updated_time_lines.at(downward_beam_location1) += downward_beam_count;
                }
                else {
                    updated_time_lines[downward_beam_location1] = downward_beam_count;
                }
            }
            if (y < num_of_columns - 1) {
                new_beams_locations.insert(downward_beam_location2);
                size_t downward_beam_count = upward_beam_count;
                if (updated_time_lines.count(downward_beam_location2) > 0) {
                    updated_time_lines.at(downward_beam_location2) += downward_beam_count;
                }
                else {
                    updated_time_lines[downward_beam_location2] = downward_beam_count;
                }
            }
            ++split_count;                        
        }  
    }
    ++current_row;
    beams_locations = new_beams_locations;
    time_lines = updated_time_lines;
    return true;
}

void TachyonManifold::update_diagram() {
    for (const auto& [x, y] : beams_locations) {
        diagram.at(x).at(y) = '|';
    }
}

size_t TachyonManifold::count_time_lines() {
    size_t total{size_t{0}};
    for (const auto & [_ , v] : time_lines) {
        total += v;
    }
    return total;
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