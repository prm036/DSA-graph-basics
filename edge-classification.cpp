#include <iostream>
#include <vector>
using namespace std;

const int WHITE = 0, GRAY = 1, BLACK = 2;

vector<vector<int>> adj;
vector<int> color, discovery, finish;
int timeCounter = 0;

void dfsVisit(int u) {
    color[u] = GRAY;
    discovery[u] = ++timeCounter;

    for (int v : adj[u]) {
        if (color[v] == WHITE) {
            cout << "Tree Edge: " << u << " -> " << v << "\n";
            dfsVisit(v);
        } else if (color[v] == GRAY) {
            cout << "Back Edge: " << u << " -> " << v << "\n";
        } else if (color[v] == BLACK) {
            if (discovery[u] < discovery[v])
                cout << "Forward Edge: " << u << " -> " << v << "\n";
            else
                cout << "Cross Edge: " << u << " -> " << v << "\n";
        }
    }

    color[u] = BLACK;
    finish[u] = ++timeCounter;
}

void dfs(int n) {
    color.assign(n, WHITE);
    discovery.assign(n, 0);
    finish.assign(n, 0);
    timeCounter = 0;

    for (int u = 0; u < n; ++u) {
        if (color[u] == WHITE)
            dfsVisit(u);
    }
}

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    adj.assign(n, vector<int>());

    cout << "Enter directed edges (u v):\n";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); // Directed edge u -> v
    }

    cout << "\nEdge Classification:\n";
    dfs(n);

    return 0;
}
