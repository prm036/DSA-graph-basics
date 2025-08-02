class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int nr = heights.size(), nc = heights[0].size();
        vector<vector<bool>> visited(nr, vector<bool>(nc, false));
        queue<pair<int,int>> q;
        for(int i=0; i<nr; i++){
            q.push({i,0});
            visited[i][0] = true;
        }
        for(int j=1; j<nc; j++){
            q.push({0,j});
            visited[0][j] = true;
        }

        while(!q.empty()){
            auto [row, column] = q.front(); q.pop();
            vector<pair<int,int>> disPositions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
            for(pair<int,int> dispos: disPositions){
                int irow = row+dispos.first;
                int icol = column+dispos.second;
                if(irow<0 || irow>=nr || icol<0 || icol>=nc) continue;
                if(visited[irow][icol]) continue;
                if(heights[irow][icol]>=heights[row][column]){
                    visited[irow][icol] = true;
                    q.push({irow, icol});
                }
            }
        }
        
        vector<vector<bool>> visited1(nr, vector<bool>(nc, false));
        queue<pair<int,int>> q1;
        for(int i=nr-1; i>=0; i--){
            q1.push({i,nc-1});
            visited1[i][nc-1] = true;
        }
        for(int j=0; j<nc-1; j++){
            q1.push({nr-1,j});
            visited1[nr-1][j] = true;
        }


        while(!q1.empty()){
            auto [row, column] = q1.front(); q1.pop();
            vector<pair<int,int>> disPositions1 = {{0,1}, {0,-1}, {1,0}, {-1,0}};
            for(auto dispos: disPositions1){
                int irow = row+dispos.first;
                int icol = column+dispos.second;
                if(irow<0 || irow>=nr || icol<0 || icol>=nc) continue;
                if(visited1[irow][icol]) continue;
                if(heights[irow][icol]>=heights[row][column]){
                    visited1[irow][icol] = true;
                    q1.push({irow, icol});
                }
            }
        }
        vector<vector<int>> x;
        for(int i=0; i<nr; i++){
            for(int j=0; j<nc; j++){
                if(visited[i][j] && visited1[i][j]){
                    x.push_back(vector<int>{i,j});
                }
            } 
        } 
        return x;
    }
};
