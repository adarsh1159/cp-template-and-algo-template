// **************** BFS ****************
// TC: O(V + E)
// SC: O(V)

#include<bits/stdc++.h>
using namespace std;

vector<int> bfs(int start, vector<vector<int>>& adj) {
    int n = adj.size();

    vector<int> vis(n, 0);
    vector<int> ans;

    queue<int> q;

    q.push(start);
    vis[start] = 1;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        ans.push_back(node);

        for (int nei : adj[node]) {
            if (!vis[nei]) {
                vis[nei] = 1;
                q.push(nei);
            }
        }
    }

    return ans;
}