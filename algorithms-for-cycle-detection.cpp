// UNDIRECTED GRAPH


// 1. DFS with Parent


bool dfs(int u, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfs(v, u, adj, visited)) return true;
        } else if (v != parent) {
            return true; // back edge found
        }
    }
    return false;
}

bool hasCycleDFS(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (dfs(i, -1, adj, visited)) return true;
        }
    }
    return false;
}


// 2. Union-Find (Disjoint Set)


vector<int> parent;

int find(int u) {
    if (parent[u] != u)
        parent[u] = find(parent[u]);
    return parent[u];
}

bool unionSets(int u, int v) {
    int pu = find(u), pv = find(v);
    if (pu == pv) return true; // cycle detected
    parent[pu] = pv;
    return false;
}

bool hasCycleUnionFind(int n, vector<pair<int, int>>& edges) {
    parent.resize(n);
    for (int i = 0; i < n; ++i) parent[i] = i;

    for (auto [u, v] : edges) {
        if (unionSets(u, v)) return true;
    }
    return false;
}

// DIRECTED GRAPH


// 1. DFS + Recursion Stack

bool dfs(int u, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& recStack) {
    visited[u] = recStack[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfs(v, adj, visited, recStack)) return true;
        } else if (recStack[v]) {
            return true; // back edge
        }
    }
    recStack[u] = false;
    return false;
}

bool hasCycleDirectedDFS(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false), recStack(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (dfs(i, adj, visited, recStack)) return true;
        }
    }
    return false;
}


// 2. Kahn’s Algorithm (BFS Topo Sort)

bool hasCycleKahn(int n, vector<vector<int>>& adj) {
    vector<int> inDegree(n, 0);
    for (auto& list : adj) {
        for (int v : list) inDegree[v]++;
    }

    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (inDegree[i] == 0)
            q.push(i);

    int count = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        count++;
        for (int v : adj[u]) {
            if (--inDegree[v] == 0)
                q.push(v);
        }
    }

    return count != n; // if not all nodes are processed, there's a cycle
}


// 3. Tarjan’s Algorithm (Detect SCCs)

int timer = 0;
vector<int> disc, low;
stack<int> stk;
vector<bool> inStack;
vector<vector<int>> sccs;

void tarjanDFS(int u, vector<vector<int>>& adj) {
    disc[u] = low[u] = timer++;
    stk.push(u); inStack[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            tarjanDFS(v, adj);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (disc[u] == low[u]) {
        vector<int> scc;
        int v;
        do {
            v = stk.top(); stk.pop();
            inStack[v] = false;
            scc.push_back(v);
        } while (v != u);
        sccs.push_back(scc); // each SCC
    }
}

void tarjan(int n, vector<vector<int>>& adj) {
    disc.assign(n, -1);
    low.assign(n, -1);
    inStack.assign(n, false);
    timer = 0;

    for (int i = 0; i < n; ++i)
        if (disc[i] == -1)
            tarjanDFS(i, adj);
}
Cycle detection using Tarjan:

bool hasCycleTarjan(int n, vector<vector<int>>& adj) {
    tarjan(n, adj);
    for (auto& scc : sccs) {
        if (scc.size() > 1) return true;
    }
    return false;
}






