// ***** DIJKSTRA'S ALGORITHM *****
// TC: O((V + E) * log V)
// SC: O(V + E)
#include<bits/stdc++.h>
using namespace std;


vector<long long> dijkstra(
    int n,
    int src,
    vector<vector<pair<int, int>>>& adj
)
{
    const long long INF = 1e18;

    vector<long long> dist(n, INF);

    // {distance, node}
    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>
    > pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty())
    {
        pair<long long, int> top = pq.top();

        long long currDist = top.first;
        int node = top.second;

        pq.pop();

        // Ignore outdated entries
        if (currDist > dist[node])
            continue;

        for (auto edge : adj[node])
        {
            int nextNode = edge.first;
            int weight = edge.second;

            if (dist[node] + weight < dist[nextNode])
            {
                dist[nextNode] = dist[node] + weight;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    return dist;
}