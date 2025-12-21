#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

struct Location {
    size_t x;
    size_t y;

    bool operator<(const Location& other) const;
    void print() const;
};

struct Rectangle {
    Location corner1;
    Location corner2;

    //bool operator<(const Location& other) const;
    Rectangle(const Location& c1, const Location& c2);
    size_t area() const;
    void print() const;
};

struct CompareByArea {
    bool operator()(const Rectangle& a, const Rectangle& b) const;
};

using Locations = std::vector<Location>;
using Rectangles = std::vector<Rectangle>;
using PriorityQueue = std::priority_queue<Rectangle,
                                          Rectangles,
                                          CompareByArea>;

void get_data(std::ifstream& file, Locations& locations);
void get_rectangles(const Locations& locations, Rectangles& rectangles);
Rectangle get_largest_rectangle(const Rectangles& rectangles);
