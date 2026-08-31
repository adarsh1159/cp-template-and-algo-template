// Strongly Connected Components (Tarjan)
// TC: O(V + E)
// SC: O(V)

#include <bits/stdc++.h>
using namespace std;

class SCC {
public:
    int timer = 0;

    void dfs(int node, vector<vector<int>>& adj,
             vector<int>& tin, vector<int>& low,
             vector<int>& inStack, stack<int>& st,
             vector<vector<int>>& sccs) {

        tin[node] = low[node] = timer++;
        st.push(node);
        inStack[node] = 1;

        for (int nei : adj[node]) {

            // Back edge to a node currently in stack
            if (inStack[nei]) {
                low[node] = min(low[node], tin[nei]);
            }

            // Unvisited node
            else if (tin[nei] == -1) {
                dfs(nei, adj, tin, low, inStack, st, sccs);

                low[node] = min(low[node], low[nei]);
            }
        }

        // node is the root of an SCC
        if (low[node] == tin[node]) {
            vector<int> component;

            while (true) {
                int curr = st.top();
                st.pop();
                inStack[curr] = 0;

                component.push_back(curr);

                if (curr == node)
                    break;
            }

            sccs.push_back(component);
        }
    }

    vector<vector<int>> findSCC(int V, vector<vector<int>>& adj) {

        vector<int> tin(V, -1);
        vector<int> low(V, -1);
        vector<int> inStack(V, 0);

        stack<int> st;
        vector<vector<int>> sccs;

        for (int i = 0; i < V; i++) {
            if (tin[i] == -1)
                dfs(i, adj, tin, low, inStack, st, sccs);
        }

        return sccs;
    }
};