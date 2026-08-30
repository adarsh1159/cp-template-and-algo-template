// Tarjan's Algorithm
// TC: O(V + E)
// SC: O(V + E)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> bridges;
    vector<int> tin, low;
    int timer = 0;

    void dfs(int node, int parent, vector<vector<int>>& adj) {
        tin[node] = low[node] = timer++;

        for (int nei : adj[node]) {
            if (nei == parent)
                continue;

            if (tin[nei] != -1) {
                // Back edge
                low[node] = min(low[node], tin[nei]);
            } 
            else {
                dfs(nei, node, adj);

                low[node] = min(low[node], low[nei]);

                // No back edge from subtree of nei to node/ancestor
                if (low[nei] > tin[node])
                    bridges.push_back({node, nei});
            }
        }
    }

    vector<vector<int>> findBridges(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        tin.assign(n, -1);
        low.assign(n, -1);

        for (int i = 0; i < n; i++) {
            if (tin[i] == -1)
                dfs(i, -1, adj);
        }

        return bridges;
    }
};