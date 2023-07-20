#pragma once
#ifndef DOMINANT_CHECK_3_H  // header guard to prevent multiple inclusions
#define DOMINANT_CHECK_3_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm> 
#include <random>
#include <set>
#include <chrono>
#include <list>
using namespace std;

struct Node {
    double cost;
    int time;
    int load;
    bool visited[100];


};
bool valid_path(const Node& node, const Node& node2) {
    int trueCountNode = std::count(std::begin(node.visited), std::end(node.visited), true);
    int trueCountNode2 = std::count(std::begin(node2.visited), std::end(node2.visited), true);

    if (trueCountNode <= trueCountNode2) {
        for (int i = 0; i != 100; ++i) {
            if (i == 87) {
                continue;
            }
            if (node.visited[i] && node2.visited[i]) {
                return true;
            }
        }
    }

    return false;
}
bool randomBool() {
    return rand() > (RAND_MAX / 2);
}
void removeNodes(vector<Node>& node_vector, const set<int>& to_erase) {
    for (auto it = to_erase.rbegin(); it != to_erase.rend(); ++it) {
        node_vector.erase(node_vector.begin() + *it);
    }
}
Node createCustomNode(double cost, int time, int load, const std::array<bool, 100>& visited) {
    Node node;
    node.cost = cost;
    node.time = time;
    node.load = load;
    std::copy(visited.begin(), visited.end(), node.visited);
    return node;
}

std::vector<Node> createNodes(size_t numNodes, default_random_engine& gen, int node_number) {
    std::vector<Node> nodes;
    nodes.reserve(numNodes);

    for (size_t i = 0; i < numNodes; ++i) {
        Node node;
        for (int j = 0; j < 100; j++) {
            node.visited[j] = randomBool();
        }

        uniform_real_distribution<double> rand_cost(0.0, 1000.0);
        uniform_int_distribution<int> rand_time(0, 1000);
        uniform_int_distribution<int> rand_load(0, 1000);

        node.cost = rand_cost(gen);
        node.load = rand_load(gen);
        node.time = rand_time(gen);

        if (!node.visited[node_number])
        {
            node.visited[node_number] = true;
        }

        nodes.push_back(node);
    }

    std::array<bool, 100> visited = { false };  // Initialize all elements to false
    Node node = createCustomNode(999.9, 999, 999, visited);
    nodes.push_back(node);

    std::array<bool, 100> visited2;  // Initialize all elements to false
    visited2.fill(true);
    Node node2 = createCustomNode(0.0, 0, 0, visited2);
    nodes.push_back(node2);





    return nodes;
}

pair<std::vector<Node>, std::vector<Node>> unsorted_array_dominant_check(std::vector<Node> nodes) {
    std::vector<Node> node_vector;
    set<int> to_erase;

    std::vector<Node> node_vector_removed_list;

    for (const Node& node : nodes) {
        bool shouldInsert = true;
        for (const auto& existingNode : node_vector) {
            if (node.time >= existingNode.time && node.load >= existingNode.load && node.cost >= existingNode.cost && valid_path(existingNode, node)) {
                shouldInsert = false;
                break;
            }
        }
        if (shouldInsert) {
            node_vector.push_back(node);
            for (auto it = node_vector.begin(); it != node_vector.end() - 1; ++it) {
                if (node.time <= it->time && node.load <= it->load && node.cost <= it->cost && valid_path(node, *it)) {
                    to_erase.insert(std::distance(node_vector.begin(), it));
                    //node_vector_removed_list.push_back(*it);
                }
            }
        }
        removeNodes(node_vector, to_erase);
        to_erase.clear(); //
    }
    return std::make_pair(node_vector, node_vector_removed_list);
}

pair<std::vector<Node>, std::vector<Node>> sorted_array_dominant_check1(const std::vector<Node>& nodes) {
    std::vector<Node> node_vector;
    std::set<int> to_erase;
    std::vector<Node> node_vector_removed_list;

    for (const Node& node : nodes) {
        auto it = node_vector.begin();
        bool shouldInsert = true;

         //Iterate until condition is met or we reach the end
        while (it != node_vector.end() && (*it).time <= node.time) {
            if (node.cost >= it->cost && node.load >= it->load && node.time >= it->time && valid_path(*it, node)) {
                shouldInsert = false;
                //node_vector_removed_list.push_back(node);
                break;
            }
            ++it;
        }



        // If no dominating node found, insert the current node at the determined position
        if (shouldInsert) {
            auto it = std::lower_bound(node_vector.begin(), node_vector.end(), node, [](const Node& a, const Node& b) {
                return a.time < b.time;
                });
            it = node_vector.insert(it, node);
            for (auto it2 = it + 1; it2 != node_vector.end(); ++it2) {
                if ((*it).time <= (*it2).time && (*it).load <= (*it2).load && (*it).cost <= (*it2).cost && valid_path(*it, *it2)) {
                    to_erase.insert(std::distance(node_vector.begin(), it2));
                    //node_vector_removed_list.push_back(*it2);
                }
            }
        }
        removeNodes(node_vector, to_erase);
        to_erase.clear();
    }

    return std::make_pair(node_vector, node_vector_removed_list);
}

std::list<Node> dominant_check(const std::vector<Node>& nodes) {
    std::list<Node> node_list;
    std::vector<Node> node_vector_removed_list;
    for (const Node& node : nodes) {
        bool shouldInsert = true;
        for (auto it = node_list.begin(); it != node_list.end(); ++it) {
            if (node.cost >= it->cost && node.load >= it->load && node.time >= it->time && valid_path(*it, node)) {
                shouldInsert = false;
                break;
            }
        }
        if (shouldInsert) {
            node_list.push_back(node);
            for (auto it = node_list.begin();  next(it) != node_list.end(); /* no increment in here */) {
                if (node.time <= it->time && node.load <= it->load && node.cost <= it->cost && valid_path(node, *it)) {
                    it = node_list.erase(it);  // erase returns next iterator
                }
                else {
                    ++it;
                }
            }
        }
    }

    return node_list;
}







#endif  // DOMINANT_CHECK_H