// -------------------- BELLMAN FORD --------------------
// Single Source Shortest Path
// Handles Negative Edge Weights
// Detects Negative Cycles
//
// TC: O(V * E)
// SC: O(V + E)
#include<bits/stdc++.h>
using namespace std;


struct Edge {
    int u, v;
    long long wt;
};

pair<vector<long long>, bool>
bellmanFord(int n, vector<Edge>& edges, int src) {

    const long long INF = 4e18;

    vector<long long> dist(n, INF);
    dist[src] = 0;

    // Relax all edges n-1 times
    for (int i = 1; i < n; i++) {

        bool updated = false;

        for (Edge edge : edges) {

            int u = edge.u;
            int v = edge.v;
            long long wt = edge.wt;

            if (dist[u] != INF &&
                dist[u] + wt < dist[v]) {

                dist[v] = dist[u] + wt;
                updated = true;
            }
        }

        // No relaxation means shortest paths are found
        if (!updated)
            break;
    }

    // Check for negative cycle
    bool negativeCycle = false;

    for (Edge edge : edges) {

        int u = edge.u;
        int v = edge.v;
        long long wt = edge.wt;

        if (dist[u] != INF &&
            dist[u] + wt < dist[v]) {

            negativeCycle = true;
            break;
        }
    }

    return {dist, negativeCycle};
}