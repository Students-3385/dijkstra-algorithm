#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm> // For reverse()

using namespace std;

// Structure for storing edges
struct Edge {
    string destination;
    int weight;
};

// Dijkstra's Algorithm function
void dijkstra(unordered_map<string, vector<Edge>>& graph, const string& start, const string& end) {
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    unordered_map<string, int> distance;
    unordered_map<string, string> parent;

    // Initialize distances to infinity
    for (const auto& node : graph) {
        distance[node.first] = numeric_limits<int>::max();
    }

    // Start node distance is 0
    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        string current = pq.top().second;
        int currentDist = pq.top().first;
        pq.pop();

        if (current == end) break;

        for (const auto& edge : graph[current]) {
            string neighbor = edge.destination;
            int newDist = currentDist + edge.weight;

            if (newDist < distance[neighbor]) {
                distance[neighbor] = newDist;
                parent[neighbor] = current;
                pq.push({newDist, neighbor});
            }
        }
    }

    // Print shortest path cost
    if (distance[end] == numeric_limits<int>::max()) {
        cout << "No path found from " << start << " to " << end << endl;
        return;
    }

    cout << "Shortest path cost from " << start << " to " << end << ": " << distance[end] << endl;

    // Print shortest path route
    vector<string> path;
    for (string at = end; at != ""; at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    cout << "Path taken: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

// Main function to take user input
int main() {
    unordered_map<string, vector<Edge>> graph;
    int edges;

    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter edges in format (source destination weight):" << endl;
    for (int i = 0; i < edges; i++) {
        string src, dest;
        int weight;
        cin >> src >> dest >> weight;

        // Only add the edge if weight is greater than 0 (optimization)
        if (weight > 0) {
            graph[src].push_back({dest, weight});
            graph[dest].push_back({src, weight}); // Remove this line if the graph is directed
        }
    }

    string start, end;
    cout << "Enter the starting node: ";
    cin >> start;
    cout << "Enter the ending node: ";
    cin >> end;

    dijkstra(graph, start, end);

    return 0;
}
