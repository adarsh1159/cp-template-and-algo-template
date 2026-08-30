// Tarjan's Algorithm
// TC: O(V + E)
// SC: O(V + E)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> tin, low;
    vector<bool> isArticulation;
    int timer = 0;

    void dfs(int node, int parent, vector<vector<int>>& adj) {
        tin[node] = low[node] = timer++;

        int children = 0;

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

                // For non-root node
                if (parent != -1 && low[nei] >= tin[node])
                    isArticulation[node] = true;

                children++;
            }
        }

        // Root condition
        if (parent == -1 && children > 1)
            isArticulation[node] = true;
    }

    vector<int> findArticulationPoints(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        tin.assign(n, -1);
        low.assign(n, -1);
        isArticulation.assign(n, false);

        for (int i = 0; i < n; i++) {
            if (tin[i] == -1)
                dfs(i, -1, adj);
        }

        vector<int> ans;

        for (int i = 0; i < n; i++) {
            if (isArticulation[i])
                ans.push_back(i);
        }

        return ans;
    }
};