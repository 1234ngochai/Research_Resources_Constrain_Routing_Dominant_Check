#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Struct for storing Node/Customer information
struct Node {
    string name;
    double x, y;    // coordinates
    double q;       // demand on vehicle capacity
    double a, b;    // time window opening and closing
    double s;       // duration for unloading
    double penalty; // waiting/penalty time
};

// Struct for storing edge information
struct Edge {
    Node* from;
    Node* to;
    double distance;
    double cost;
};

class Graph {
private:
    vector<Node> nodes;
    vector<vector<Edge>> edges;  // edge list, size should be the same as nodes
    double vehicleCapacity;

public:
    Graph(double vc) : vehicleCapacity(vc) {}


    // Function to compute Euclidean distance between two nodes
    double computeDistance(Node* node1, Node* node2) {
        return ceil(sqrt(pow(node1->x - node2->x, 2) + pow(node1->y - node2->y, 2)));
    }

    // Function to compute cost for an edge
    //cost_j = cost_i + distance_ij - dual_j
    double computeCost(double cost_i, double distance_ij, Node* node_j) {
        return cost_i + distance_ij - node_j->penalty;
    }

    // Function to compute load for an edge
    double computeLoad(double load_i, Node* node_i) {
        return load_i + node_i->q;
    }

    // Function to compute time for an edge
    double computeTime(double time_i, Node* node_i, double travel_ij) {
        return max(time_i + node_i->s + travel_ij, node_i->a);
    }

    void readFromFile(const string& filename) {
        ifstream file(filename);
        string line;

        // Skip the first 4 lines
        getline(file, line);
        getline(file, line);
        getline(file, line);
        getline(file, line);

        // Read the nodes
        while (getline(file, line)) {
            stringstream ss(line);
            string name;
            double x, y, q, a, b, s, penalty;
            ss >> name >> x >> y >> q >> a >> b >> s >> penalty;

            nodes.push_back({ name, x, y, q, a, b, s, penalty });
        }
    }

    void readPenaltiesFromFile(const string& filename) {
        ifstream file(filename);
        string line;

        nodes[0].penalty = 0;
        int index = 1;

        // Read the penalties
        while (std::getline(file, line)) {
            // Parse penalty from the line
            double penalty = stod(line);  // stod converts string to double

            // Check if index is within range
            if (index < nodes.size()) {
                nodes[index].penalty = penalty;
                index++;
            }
            else {
                // More penalties than nodes - exit or handle error appropriately
                break;
            }
        }
        // Initialize the edges
        edges.resize(nodes.size());

        // Compute the edges between each pair of nodes
        for (int i = 0; i < nodes.size(); ++i) {
            for (int j = 0; j < nodes.size(); ++j) {
                if (i != j) {

                    //calculating the distance for each edges.
                    double distance = computeDistance(&nodes[i], &nodes[j]);

                    double cost = computeCost(0.0, distance, &nodes[j]);  // assuming cost_i is 0.0 for all i

                    edges[i].push_back({ &nodes[i], &nodes[j], distance, cost });
                }
                else {
                    edges[i].push_back({ &nodes[i], &nodes[j], 0, 0 });
                }
            }
        }
    }


    void printNodes() const {
        for (const Node& node : nodes) {
            cout << "Name: " << node.name << endl;
            cout << "Coordinates: (" << node.x << ", " << node.y << ")" << endl;
            cout << "Demand on vehicle capacity: " << node.q << endl;
            cout << "Time window opening: " << node.a << endl;
            cout << "Time window closing: " << node.b << endl;
            cout << "Duration for unloading: " << node.s << endl;
            cout << "Penalty: " << node.penalty << endl;
            cout << "----------------------" << endl;
        }
        for (int i = 0; i < nodes.size(); ++i) {
            cout << "Node: " << nodes[i].name << "\n";
            cout << "Coordinates: (" << nodes[i].x << ", " << nodes[i].y << ")\n";
            cout << "Demand on vehicle capacity: " << nodes[i].q << "\n";
            cout << "Time window opening: " << nodes[i].a << "\n";
            cout << "Time window closing: " << nodes[i].b << "\n";
            cout << "Duration for unloading: " << nodes[i].s << "\n";
            cout << "Penalty: " << nodes[i].penalty << "\n";
            cout << "Edges:\n";
            for (int j = 0; j < edges[i].size(); ++j) {
                cout << "  to Node: " << edges[i][j].to->name << ", cost: " << edges[i][j].cost << ", distance: " << edges[i][j].distance << "\n";
            }
            cout << "----------------------\n";
        }
    }


    // Method to find the index of a node in the nodes vector given a Node pointer
    int findNodeIndex(Node* node) {
        for (int i = 0; i < nodes.size(); ++i) {
            if (&nodes[i] == node)
                return i;
        }
        return -1;  // Node not found
    }


    void DFS(int startNode, vector<bool>& visited, vector<int>& path, int& iterationCount, double currentTime) {
        iterationCount++;
        if (iterationCount % 10000 == 0) {
            cout << "Iteration: " << iterationCount << "\n";
        }

        visited[startNode] = true;
        path.push_back(startNode);

        //for (int i = 0; i < path.size(); i++) {
        //    cout << nodes[path[i]].name << " ";
        //}
        //cout << "\n";


        int rdIndex = 0;
        double timeToRD = computeDistance(&nodes[startNode], &nodes[rdIndex]);


        // If current node is not RD and it's possible to return to RD within time constraint
        if (startNode != rdIndex && currentTime + timeToRD <= nodes[rdIndex].b) {
            path.push_back(rdIndex);
            for (int i = 0; i < path.size(); i++) {
                cout << nodes[path[i]].name << " ";
            }
            cout << "\n";
            path.pop_back();
        }




        for (Edge& edge : edges[startNode]) {
            int neighborIndex = findNodeIndex(edge.to);
            double arrivalTime = currentTime + edge.distance;

            double returnTime = arrivalTime + computeDistance(&nodes[neighborIndex], &nodes[rdIndex]);

            // Check whether it's possible to return to RD within time constraint after visiting the neighbor node
            if (returnTime > nodes[rdIndex].b) {
                continue;
            }

            if (path.size() > 1) {
                path.pop_back();
                visited[startNode] = false;
                return;
            }
          
            //}
            //else if (!visited[neighborIndex] && arrivalTime >= nodes[neighborIndex].a && arrivalTime <= nodes[neighborIndex].b) {
            //    DFS(neighborIndex, visited, path, iterationCount,arrivalTime);
            //}

           
            if (!visited[neighborIndex] && arrivalTime >= nodes[neighborIndex].a && arrivalTime <= nodes[neighborIndex].b) {
                DFS(neighborIndex, visited, path, iterationCount, arrivalTime);
            }


            //else if (!visited[neighborIndex]){
            //    DFS(neighborIndex, visited, path, iterationCount, arrivalTime);
            //}
        }

        // Backtrack
        visited[startNode] = false;
        path.pop_back();
    }



    void startDFS(Node* startNode) {
        int iterationCount = 0;
        vector<bool> visited(nodes.size(), false);
        vector<int> path;
        DFS(findNodeIndex(startNode), visited, path, iterationCount,0);
    }

    Node* getNodeByIndex(int index) {
        if (index < 0 || index >= nodes.size()) {
            cout << "Invalid index. Index must be between 0 and " << nodes.size() - 1 << "." << endl;
            return nullptr;
        }
        return &nodes[index];
    }

};
