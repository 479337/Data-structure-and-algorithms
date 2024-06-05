#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

typedef pair<int, int> Pair;
typedef vector<vector<Pair>> Graph;

struct Node {
    int vertex;
    int g;
    int h;
    int f;

    bool operator>(const Node &other) const {
        return f > other.f;
    }
};

int heuristic(int a, int b) {
    return abs(a - b);
}

void astar(const Graph &graph, int start, int end) {
    vector<int> g_costs(graph.size(), INT_MAX);
    g_costs[start] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({start, 0, heuristic(start, end), heuristic(start, end)});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.vertex == end) {
            cout << "Shortest path from " << start << " to " << end << " is " << current.g << endl;
            return;
        }

        for (const Pair &neighbor : graph[current.vertex]) {
            int next_node = neighbor.first;
            int next_g = current.g + neighbor.second;
            int next_h = heuristic(next_node, end);

            if (next_g < g_costs[next_node]) {
                g_costs[next_node] = next_g;
                pq.push({next_node, next_g, next_h, next_g + next_h});
            }
        }
    }

    cout << "No path from " << start << " to " << end << endl;
}

int main() {
    Graph graph(8);
    graph[0] = {{1, 10}, {3, 12}, {6, 11}, {7, 4}};
    graph[1] = {{0, 10}, {3, 8}, {7, 20}};
    graph[2] = {{3, 17}, {4, 8}, {6, 13}, {7, 10}};
    graph[3] = {{0, 12}, {1, 8}, {2, 17}, {5, 16}, {6, 24}, {7, 14}};
    graph[4] = {{2, 8}, {5, 8}, {6, 11}, {7, 5}};
    graph[5] = {{3, 16}, {4, 8}, {6, 18}, {7, 21}};
    graph[6] = {{0, 11}, {2, 13}, {3, 24}, {4, 11}, {5, 18}, {7, 30}};
    graph[7] = {{0, 4}, {1, 20}, {2, 10}, {3, 14}, {4, 5}, {5, 21}, {6, 30}};

    int start = 0;
    int end = 5;
    astar(graph, start, end);

    return 0;
}
