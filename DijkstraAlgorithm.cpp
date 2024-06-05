#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> Pair; // A pair to represent edges (node, weight)
typedef vector<vector<Pair>> Graph; // A graph represented as an adjacency list

// Dijkstra's algorithm to find the shortest path from start to end
void dijkstra(const Graph &graph, int start, int end) {
    vector<int> distances(graph.size(), INT_MAX); // Initialize distances to all nodes as infinity
    distances[start] = 0; // Distance to the start node is 0

    priority_queue<Pair, vector<Pair>, greater<Pair>> pq; // Min-heap priority queue
    pq.push({0, start}); // Push the start node into the priority queue

    while (!pq.empty()) {
        int distance = pq.top().first; // Current shortest distance
        int node = pq.top().second; // Current node
        pq.pop();

        // If we reached the end node, print the shortest path
        if (node == end) {
            cout << "Shortest path from " << start << " to " << end << " is " << distance << endl;
            return;
        }

        // Explore the neighbors of the current node
        for (const Pair &neighbor : graph[node]) {
            int next_node = neighbor.first; // Neighbor node
            int next_distance = neighbor.second; // Distance to the neighbor

            // Relaxation step: Update the distance to the neighbor if a shorter path is found
            if (distances[node] + next_distance < distances[next_node]) {
                distances[next_node] = distances[node] + next_distance;
                pq.push({distances[next_node], next_node}); // Push the updated distance and neighbor into the priority queue
            }
        }
    }

    // If no path is found, indicate so
    cout << "No path from " << start << " to " << end << endl;
}

int main() {
    // Example graph with 8 nodes labeled 0 to 7
    Graph graph(8);
    graph[0] = {{1, 10}, {3, 12}, {6, 11}, {7, 4}};
    graph[1] = {{0, 10}, {3, 8}, {7, 20}};
    graph[2] = {{3, 17}, {4, 8}, {6, 13}, {7, 10}};
    graph[3] = {{0, 12}, {1, 8}, {2, 17}, {5, 16}, {6, 24}, {7, 14}};
    graph[4] = {{2, 8}, {5, 8}, {6, 11}, {7, 5}};
    graph[5] = {{3, 16}, {4, 8}, {6, 18}, {7, 21}};
    graph[6] = {{0, 11}, {2, 13}, {3, 24}, {4, 11}, {5, 18}, {7, 30}};
    graph[7] = {{0, 4}, {1, 20}, {2, 10}, {3, 14}, {4, 5}, {5, 21}, {6, 30}};

    int start = 0; // Starting node
    int end = 5; // Ending node
    dijkstra(graph, start, end); // Run Dijkstra's algorithm

    return 0;
}
