// Method 1: DFS-Based Topo Sort
// Run DFS
// After visiting all descendants of a node, push it to a stack
// Reverse the stack (or pop from top) to get the topological order

void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v]) dfs(v, adj, visited, st);
    st.push(u);
}

vector<int> topoSortDFS(int V, vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    stack<int> st;
    for (int i = 0; i < V; ++i)
        if (!visited[i]) dfs(i, adj, visited, st);
    
    vector<int> order;
    while (!st.empty()) {
        order.push_back(st.top());
        st.pop();
    }
    return order;
}


// Method 2: Kahn’s Algorithm (BFS-based)
// Compute in-degrees of all nodes.
// Add all 0 in-degree nodes to a queue.
// While queue not empty:
// Pop a node, add to result
// Decrease in-degree of neighbors
// If neighbor becomes 0 in-degree, push to queue

vector<int> topoSortKahn(int V, vector<vector<int>>& adj) {
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; ++u)
        for (int v : adj[u]) indegree[v]++;

    queue<int> q;
    for (int i = 0; i < V; ++i)
        if (indegree[i] == 0) q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u])
            if (--indegree[v] == 0) q.push(v);
    }

    if (order.size() < V) {
        // Cycle detected
        return {}; // or throw error
    }

    return order;
}
