// ***** 0-1 BFS *****
// TC: O(V + E)
// SC: O(V + E)
#include<bits/stdc++.h>
using namespace std;

vector<int> zeroOneBFS(
    int n,
    int src,
    vector<vector<pair<int, int>>>& adj
)
{
    const int INF = 1e9;

    vector<int> dist(n, INF);
    deque<int> dq;

    dist[src] = 0;
    dq.push_front(src);

    while (!dq.empty())
    {
        int node = dq.front();
        dq.pop_front();

        for (pair<int, int> edge : adj[node])
        {
            int nextNode = edge.first;
            int weight = edge.second;

            if (dist[node] + weight < dist[nextNode])
            {
                dist[nextNode] = dist[node] + weight;

                if (weight == 0)
                {
                    dq.push_front(nextNode);
                }
                else
                {
                    dq.push_back(nextNode);
                }
            }
        }
    }

    return dist;
}