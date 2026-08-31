// Strongly Connected Components (Kosaraju)
// TC: O(V + E)
// SC: O(V + E)

#include <bits/stdc++.h>
using namespace std;

class SCC {
public:
    void dfs1(int node, vector<vector<int>>& adj, vector<int>& vis,
              stack<int>& st) {
        vis[node] = 1;

        for (int nei : adj[node]) {
            if (!vis[nei])
                dfs1(nei, adj, vis, st);
        }

        st.push(node);
    }

    void dfs2(int node, vector<vector<int>>& rev,
              vector<int>& vis, vector<int>& component) {
        vis[node] = 1;
        component.push_back(node);

        for (int nei : rev[node]) {
            if (!vis[nei])
                dfs2(nei, rev, vis, component);
        }
    }

    vector<vector<int>> findSCC(int V, vector<vector<int>>& adj) {
        vector<int> vis(V, 0);
        stack<int> st;

        // Step 1: Get finishing order
        for (int i = 0; i < V; i++) {
            if (!vis[i])
                dfs1(i, adj, vis, st);
        }

        // Step 2: Reverse graph
        vector<vector<int>> rev(V);

        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                rev[v].push_back(u);
            }
        }

        // Step 3: DFS in finishing order on reversed graph
        fill(vis.begin(), vis.end(), 0);

        vector<vector<int>> sccs;

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (!vis[node]) {
                vector<int> component;
                dfs2(node, rev, vis, component);
                sccs.push_back(component);
            }
        }

        return sccs;
    }
};