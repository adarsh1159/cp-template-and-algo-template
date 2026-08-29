/*
Kruskal's Algorithm

tc = O(E log E)
sc = O(V)
*/

#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if(parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    bool unite(int u, int v) {
        u = find(u);
        v = find(v);

        if(u == v)
            return false;

        if(rank[u] < rank[v])
            swap(u, v);

        parent[v] = u;

        if(rank[u] == rank[v])
            rank[u]++;

        return true;
    }
};

class Solution {
public:
    int kruskal(int n, vector<vector<int>>& edges) {
        // edges[i] = {u, v, wt}

        sort(edges.begin(), edges.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[2] < b[2];
             });

        DSU dsu(n);

        int mstWeight = 0;
        int edgesUsed = 0;

        for(auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            if(dsu.unite(u, v)) {
                mstWeight += wt;
                edgesUsed++;

                if(edgesUsed == n - 1)
                    break;
            }
        }

        return mstWeight;
    }
};