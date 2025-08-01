#include <iostream>
#include <vector>
#include <set>
#include <stack>
using namespace std;

const int INF = 1e9;
typedef pair<int, int> pii;

void printPath(int v, const vector<int>& parent) {
    stack<int> path;
    while (v != -1) {
        path.push(v);
        v = parent[v];
    }
    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }
    cout << "\n";
}

void dijkstra(int n, int source, vector<vector<pii>>& adj) {
    vector<int> dist(n, INF);
    vector<int> parent(n, -1);
    set<pii> s;  // (distance, vertex)

    dist[source] = 0;
    s.insert({0, source});

    while (!s.empty()) {
        int u = s.begin()->second;
        s.erase(s.begin());

        for (auto [v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                // If v already in set with worse distance, erase it
                if (dist[v] != INF)
                    s.erase({dist[v], v});

                dist[v] = dist[u] + weight;
                parent[v] = u;
                s.insert({dist[v], v});
            }
        }
    }

    // Output distances and paths
    cout << "\nShortest paths from node " << source << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "To node " << i << ": ";
        if (dist[i] == INF) {
            cout << "Unreachable\n";
        } else {
            cout << "Distance = " << dist[i] << ", Path = ";
            printPath(i, parent);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pii>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);  // undirected
    }

    int source;
    cin >> source;

    dijkstra(n, source, adj);
    return 0;
}
