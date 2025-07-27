// This variable will store the global maximum diameter found during DFS
int global_max_diameter = 0;
// Visited array for DFS
std::vector<bool> visited;

// Recursive DFS function for the single traversal DP approach.
// Returns the height of the subtree rooted at 'u' (max depth from 'u' downwards).
// The 'parent' parameter is removed, relying entirely on 'visited'.
int dfs_recursive_dp_no_parent_check(int u) {
    visited[u] = true; // Mark current node as visited

    int max_height1 = 0;
    int max_height2 = 0;

    for (int v : adj[u]) {
        // If 'v' has not been visited, it means it's a child in the current DFS tree
        // or a node in another component not yet explored.
        if (!visited[v]) {
            int child_height = dfs_recursive_dp_no_parent_check(v);
            
            // +1 for the edge connecting u to v
            if (child_height + 1 >= max_height1) {
                max_height2 = max_height1;
                max_height1 = child_height + 1;
            } else if (child_height + 1 > max_height2) {
                max_height2 = child_height + 1;
            }
        }
        // If 'v' IS visited, and it's not the 'parent' (which is handled by visited[]),
        // it means we've encountered a back-edge in a cycle.
        // Since we are promised an acyclic graph (tree/forest), this case won't occur.
    }

    int current_node_diameter = max_height1 + max_height2;
    global_max_diameter = std::max(global_max_diameter, current_node_diameter);

    return max_height1;
}

int longest_path_single_dfs_no_parent_check() {
    if (V == 0) {
        return 0;
    }

    global_max_diameter = 0; // Reset global variable
    visited.assign(V, false); // Initialize visited array for this traversal

    // Iterate through all nodes to handle forests (disconnected components)
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            dfs_recursive_dp_no_parent_check(i); // No parent argument needed here
        }
    }

    return global_max_diameter;
}
