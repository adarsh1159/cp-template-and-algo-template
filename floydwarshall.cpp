// Floyd-Warshall Algorithm
// Finds shortest paths between ALL pairs of vertices.
//
// TC: O(V^3)
// SC: O(V^2)

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

vector<vector<long long>> floydWarshall(
    int n,
    vector<vector<long long>>& edges
) {
    vector<vector<long long>> dist(n, vector<long long>(n, INF));

    // Distance from a node to itself
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    // Add edges
    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        long long wt = edge[2];

        dist[u][v] = min(dist[u][v], wt);

        // Uncomment for undirected graph
        // dist[v][u] = min(dist[v][u], wt);
    }

    // Floyd-Warshall
    for (int via = 0; via < n; via++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {

                if (dist[u][via] == INF ||
                    dist[via][v] == INF)
                    continue;

                dist[u][v] = min(
                    dist[u][v],
                    dist[u][via] + dist[via][v]
                );
            }
        }
    }

    return dist;
}