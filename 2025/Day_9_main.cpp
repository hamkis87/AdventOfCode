#include <iostream>
#include <string>
#include "theater.h"

int main() {
    std::string file_name{"Day_9_input.txt"};
    //std::string file_name{"Day_9_test.txt"};
    std::ifstream file{file_name};
    Locations locations;
    get_data(file, locations);
    Rectangles rectangles;
    get_rectangles(locations, rectangles);
    Rectangle largest_rec = get_largest_rectangle(rectangles);
    std::cout << "Largest rectangle is: ";
    largest_rec.print();
    std::cout << std::endl;
    std::cout << "has area = ";
    std::cout << largest_rec.area() << std::endl;   
    return 0;
}