#ifndef TACHYON_MANIFOLD
#define TACHYON_MANIFOLD
#include <string>
#include <vector>
#include <set>
#include <map>

using Location = std::pair<size_t, size_t>;
using Timelines = std::map<Location, size_t>;

class TachyonManifold {
public:
    TachyonManifold(std::string file_name);
    void run_process();
    
private:
    void initialize();
    bool move();
    void print();
    void print_info() const;
    void update_diagram();
    size_t count_time_lines();
    std::vector<std::string> diagram;
    std::set<Location> beams_locations;
    size_t split_count{0};
    size_t current_row{0};
    size_t num_of_rows;
    size_t num_of_columns;
    Timelines time_lines;
    std::string out_file_name{"Day_7_output.txt"};
};

#endif