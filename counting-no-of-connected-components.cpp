class Solution {
public:
    void dfs(int source, vector<bool>& visited, vector<vector<int>>  adj){
        visited[source] = true;
        for(auto v: adj[source]){
            if(!visited[v]){
                dfs(v, visited, adj);
            }
        }
    }
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        vector<bool> visited(n);
        for(const auto& edge: edges){
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        int ans = 0;
        for(int i=0; i<n ; i++){
            if(!visited[i]){
                vector<bool> cloned_visited(visited);
                dfs(i, visited, adj);
                int nedges = 0, nver = 0;
                for(int k=0; k<n; k++){
                    if(cloned_visited[k] != visited[k]){
                        nver+=1;
                        nedges+=adj[k].size();
                    }
                }
                // cout << nver << " " << nedges << endl;
                if(nedges/2 == (nver*(nver-1))/2) {
                    ans+=1;
                }
            }
        }
        return ans;
    }
};
