// https://leetcode.com/problems/detect-cycles-in-2d-grid/description
class Solution {
    vector<vector<pair<int,int>>> parent;
    vector<vector<int>> rank;
public:
    bool containsCycle(vector<vector<char>>& grid) {
        int nr = grid.size(), nc = grid[0].size();
        parent.resize(nr, vector<pair<int, int>>(nc, {-1, -1}));
        rank.resize(nr, vector<int>(nc, 0));


        for(int i=0; i<nr; i++){
            for(int j=0; j<nc; j++){
                parent[i][j] = {i,j};
            }
        }

        for(int i=0; i<nr; i++){
            for(int j=0; j<nc; j++){
                if(i+1<nr && grid[i][j] == grid[i+1][j]){
                    if(union1({i+1,j}, {i,j})){
                        return true;
                    }
                }
                if(j+1<nc && grid[i][j] == grid[i][j+1]){
                    if(union1({i,j+1}, {i,j})){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    pair<int,int> find(pair<int,int> u){
        if(parent[u.first][u.second] == u){
            return u;
        }
        return parent[u.first][u.second] = find(parent[u.first][u.second]);
    }

    bool union1(pair<int,int> u, pair<int,int> v){
        pair<int,int> x = find(u), y = find(v);
        if(x == y) return true;
        if(rank[x.first][x.second] == rank[y.first][y.second]){
            parent[y.first][y.second] = x;
            rank[x.first][x.second]+=1;
        }else if(rank[x.first][x.second] > rank[y.first][y.second]){
            parent[y.first][y.second] = x;
        }else{
            parent[x.first][x.second] = y;
        }
        return false;
    }
};
