bool dfs(int u, vector<bool>& visited, vector<vector<int>>& adj, int v, vector<int>& path) {
    visited[u] = true;
    path.push_back(u);  // add current node to path

    if (u == v) return true;  // reached destination

    for (auto x : adj[u]) {
        if (!visited[x]) {
            if (dfs(x, visited, adj, v, path))
                return true;  // path found via x
        }
    }

    path.pop_back();  // backtrack if path not found
    return false;
}
