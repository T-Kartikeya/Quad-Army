#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Graph {
    unordered_map<int, vector<int>> adj;

public:
    void addEdge(int u, int v) {
        adj[u].push_back(v); // For BFS tree behavior
    }

    void BFS(int start) {
        unordered_map<int, bool> visited;
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Graph g;
    vector<int> nodes;
    char choice;
    int data;

    // Input loop
    do {
        cout << "Enter data => ";
        cin >> data;
        nodes.push_back(data);
        cout << "Do you want to insert one more node? (y/n) ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    // Connect nodes like a binary tree
    for (int i = 0; i < nodes.size(); ++i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < nodes.size()) {
            g.addEdge(nodes[i], nodes[left]);
        }
        if (right < nodes.size()) {
            g.addEdge(nodes[i], nodes[right]);
        }
    }

    cout << "\nBFS Traversal:\n";
    if (!nodes.empty())
        g.BFS(nodes[0]);

    return 0;
}