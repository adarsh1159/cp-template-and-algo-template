// **************** DFS ****************
// TC: O(V + E)
// SC: O(V)

#include<bits/stdc++.h>
using namespace std;

void dfs(int node, vector<vector<int>>& adj,
         vector<int>& vis, vector<int>& ans) {
    
    vis[node] = 1;
    ans.push_back(node);

    for (int nei : adj[node]) {
        if (!vis[nei]) {
            dfs(nei, adj, vis, ans);
        }
    }
}