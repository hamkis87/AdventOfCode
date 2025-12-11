#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

struct DialStructue {
  int position;
  int distance;
  int at_zero_count;
  int crossed_zero_count;
  char direction;
};

void rotate_dial(DialStructue& dial);

int main() {
    std::string file_name{"Day_1_Secret_Entrance.txt"};
    std::ifstream input_file{file_name};
    std::string line;
    int line_count{0};
    DialStructue dial{};
    dial.position = 50;
    int position_0_count{0};
    while (std::getline(input_file, line)) {
        std::stringstream line_stream{line};
        if (line_stream >> dial.direction >> dial.distance) {
            rotate_dial(dial);
            ++line_count;
        }
        else {
            std::cout << "Incorrect input at line " << 1 + line_count;
            std::cout << std::endl;
            std::exit(EXIT_FAILURE);
        }   //std::cout << line << std::endl;
    }
    position_0_count = dial.at_zero_count + dial.crossed_zero_count;
    std::cout << "Dial has been " << dial.at_zero_count 
        << " times at position 0." << std::endl;
    std::cout << "Dial has crossed 0 a number of " << dial.crossed_zero_count
        << " times." << std::endl;
    std::cout << "Result is " << position_0_count
        << " times." << std::endl;
}

void rotate_dial(DialStructue& dial) {
    int next_position{0};
    bool was_at_zero = dial.position == 0;
    bool flag = false;
    if (dial.direction == 'L') {
        next_position = dial.position - dial.distance;
        flag = next_position < 0;
        while (next_position < 0) {
            next_position += 100;
            ++dial.crossed_zero_count;
        }
        if (flag && was_at_zero) {
            --dial.crossed_zero_count;
        }
    }
    else if (dial.direction == 'R') {
        //next_position = (dial.position + dial.distance) % 100;
        next_position = dial.position + dial.distance;
        while (next_position > 100) {
            next_position -= 100;
            ++dial.crossed_zero_count;
        }
        if (next_position == 100) {
            next_position = 0;
        }
    }
    else {
        std::cout << "Incorrect direction." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    dial.position = next_position;
    if (dial.position == 0) {
        ++dial.at_zero_count;
    }
}