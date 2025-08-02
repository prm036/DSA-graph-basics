/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(node == NULL) return NULL;
        map<Node*, Node*> visited;
        return dfs(node, visited);
    }

    Node* dfs(Node* node, map<Node*, Node*>& visited){
        Node* cnode = new Node();
        cnode->val = node->val;
        visited[node] = cnode;
        for(const auto& neighbor: node->neighbors){
            if(visited.find(neighbor)==visited.end()){
                Node* cneighbour = dfs(neighbor, visited);
                cnode->neighbors.push_back(cneighbour);
            }else{
                Node* cneighbour = visited[neighbor];
                cnode->neighbors.push_back(cneighbour);
            }
        }
        return cnode;
    }
};
