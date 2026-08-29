/*
Prim's Algorithm

tc = O(E log V)
sc = O(V + E)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int prim(int n, vector<vector<pair<int,int>>>& adj) {

        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > pq;

        vector<bool> vis(n, false);

        pq.push({0, 0});

        int mstWeight = 0;

        while(!pq.empty()) {
            pair<int,int> p = pq.top();
            pq.pop();

            int wt = p.first;
            int u = p.second;

            if(vis[u])
                continue;

            vis[u] = true;
            mstWeight += wt;

            for(int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].first;
                int weight = adj[u][i].second;

                if(!vis[v])
                    pq.push({weight, v});
            }
        }

        return mstWeight;
    }
};