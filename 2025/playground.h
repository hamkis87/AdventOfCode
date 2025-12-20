#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

struct Position {
    int x;
    int y;
    int z;

    bool operator<(const Position& other) const;
    float distance(const Position& other) const;
    void print() const;
};

struct CompareBySecond {
    bool operator()(
        const std::pair<std::pair<Position, Position>, float>& a,
        const std::pair<std::pair<Position, Position>, float>& b) const;
};

using Positions = std::vector<Position>;
using PriorityQueue = std::priority_queue<
        std::pair<std::pair<Position, Position>, float>,
        std::vector<std::pair<std::pair<Position, Position>, float>>,
        CompareBySecond>;
using Circuit = std::set<Position>;
using Circuits = std::vector<Circuit>;

void get_data(std::ifstream& file, Positions& positions);
void sort_data(PriorityQueue& pq, const Positions& positions);
void print_closest_points(PriorityQueue pq, int k);
void connect_pairs(PriorityQueue& pq, Circuits& circuits, int number_of_pairs);
size_t get_circuit_id(const Position& p, const Circuits& circuits);
void merge_two_circuits(Circuits& circuits, size_t min_id, size_t max_id);
void print_circuits_info(const Circuits& circuits);
void sort_circuits(Circuits& circuits);
size_t get_result(const Circuits& circuits);
