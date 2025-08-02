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

// Note on why     `if (u == v) return true` shouldn' be placed inside `if (!visited[x]) {`
// 0 → 1 → 4  
//  \       ↑  
//   → 2 → 3 
// If 4 is visited from a different path and appears again, your modified version skips checking it again because visited[4] == true, even though you're at a node directly pointing to it.

