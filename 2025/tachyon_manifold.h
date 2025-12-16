#ifndef TACHYON_MANIFOLD
#define TACHYON_MANIFOLD
#include <string>
#include <vector>
#include <set>

using Location = std::pair<size_t, size_t>;

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
    std::vector<std::string> diagram;
    std::set<Location> beams_locations;
    size_t split_count{0};
    size_t current_row{0};
    size_t num_of_rows;
    size_t num_of_columns;
    std::string out_file_name{"Day_7_output.txt"};
};

#endif