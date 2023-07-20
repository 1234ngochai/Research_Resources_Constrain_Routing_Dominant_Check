#pragma once
#include <vector>
#include <memory>
#include <bitset>
#include <stdexcept>

#ifndef TREE_DOMINANT_CHECK_H
#define TREE_DOMINANT_CHECK_H

class Node2 {
public:
    Node2() : children(16, nullptr) {}  // Initialize all child nodes to nullptr

    double cost;
    int time;
    int load;
    bool visited[100];

    // Children nodes
    std::vector<std::shared_ptr<Node2>> children;

    //bool valid_path_tree(const Node2& node2) const;

    void insertNode(std::shared_ptr<Node2> newNode) {
        //std::bitset<4> conditions;
        //conditions[0] = cost >= newNode->cost;
        //conditions[1] = time >= newNode->time;
        //conditions[2] = load >= newNode->load;
        //conditions[3] = valid_path_tree(*newNode);


        vector<double> corp;
        corp.push_back(newNode->cost);
        corp.push_back(newNode->time);
        corp.push_back(newNode->load);
        vector<double> corq;
        corq.push_back(newNode->cost);
        corq.push_back(newNode->time);
        corq.push_back(newNode->load);
        int N = 104;
        double sum = 0;
        for (int i = 0; i < N; ++i) {
            sum += pow(corp[i] - corq[i], 2);
            sqrt(sum);
        }

        //std::cout << "Comparisons:\n";
        //std::cout << "Cost: " << cost << " >= " << newNode->cost << ": " << conditions[0] << "\n";
        //std::cout << "Time: " << time << " >= " << newNode->time << ": " << conditions[1] << "\n";
        //std::cout << "Load: " << load << " >= " << newNode->load << ": " << conditions[2] << "\n";
        //std::cout << "Condition 4: " << conditions[3] << "\n";
        // Print bitset value
        //std::cout << "Bitset value: " << conditions.to_string() << "\n";
        //// If all conditions are satisfied, replace current node with the new node
        //if (conditions.to_ulong() == 7) {  // 15 in decimal is equivalent to 1111 in binary
        //    std::cout << "Cost: " << cost << " >= " << newNode->cost << ": " << conditions[0] << "\n";
        //    std::cout << "Time: " << time << " >= " << newNode->time << ": " << conditions[1] << "\n";
        //    std::cout << "Load: " << load << " >= " << newNode->load << ": " << conditions[2] << "\n";
        //
        //    cost = newNode->cost;
        //    time = newNode->time;
        //    load = newNode->load;
        //    std::copy(std::begin(newNode->visited), std::end(newNode->visited), std::begin(visited));
        //    //std::cout << "Comparisons:\n";
        //    //std::cout << "Cost: " << cost << " >= " << newNode->cost << ": " << conditions[0] << "\n";
        //    //std::cout << "Time: " << time << " >= " << newNode->time << ": " << conditions[1] << "\n";
        //    //std::cout << "Load: " << load << " >= " << newNode->load << ": " << conditions[2] << "\n";
        //    //std::cout << "Condition 4: " << conditions[3] << "\n";
        //}
        //// Otherwise, insert new node into children list based on conditions
        //
        //else if (conditions.to_ulong() == 0) {
        //}
        //
        //else {
        //    // Convert conditions to decimal
        //    int index = conditions.to_ulong();
        //
        //    // Make sure index is in valid range
        //    if (index < 0 || index >= children.size()) {
        //        throw std::out_of_range("Index out of range");
        //    }
        //
        //    // If a child already exists at this index, insert the new node into this child
        //    if (children[index] != nullptr) {
        //        children[index]->insertNode(newNode);
        //    }
        //    // Otherwise, insert the new node as a child at this index
        //    else {
        //        children[index] = newNode;
        //    }
        //}
                    // Convert conditions to decimal
        //if (conditions.to_ulong() != 0) {

        //    int index = conditions.to_ulong();

        //    // Make sure index is in valid range
        //    if (index < 0 || index >= children.size()) {
        //        throw std::out_of_range("Index out of range");
        //    }

        //    // If a child already exists at this index, insert the new node into this child
        //    if (children[index] != nullptr) {
        //        children[index]->insertNode(newNode);
        //    }
        //    // Otherwise, insert the new node as a child at this index
        //    else {
        //        children[index] = newNode;
        //    }
        //}
        //else {
        //    std::cout << "Cost: " << cost << " >= " << newNode->cost << ": " << conditions[0] << "\n";
        //    std::cout << "Time: " << time << " >= " << newNode->time << ": " << conditions[1] << "\n";
        //    std::cout << "Load: " << load << " >= " << newNode->load << ": " << conditions[2] << "\n";
        //    std::cout << "Condition 4: " << conditions[3] << "\n";
        //}
    }

    bool valid_path_tree(const Node2& node2) const {
        int trueCountNode = std::count(std::begin(visited), std::end(visited), true);
        int trueCountNode2 = std::count(std::begin(node2.visited), std::end(node2.visited), true);

        if (trueCountNode >= trueCountNode2) {
            for (int i = 0; i != 100; ++i) {
                if (i == 87) {
                    continue;
                }
                if (visited[i] && node2.visited[i]) {
                    return true;
                }
            }
        }

        return false;
    }

    void printTree(int level = 0) const {
        // Print current node
        for (int i = 0; i < level; ++i) {
            std::cout << "  "; // Indent based on the level
        }
        std::cout << "Cost: " << cost << ", Time: " << time << ", Load: " << load << "\n";

        // Print child nodes recursively
        for (const auto& child : children) {
            if (child != nullptr) {
                child->printTree(level + 1); // Pass the updated level
            }
        }
    }
};



#endif // TREE_DOMINANT_CHECK_H
