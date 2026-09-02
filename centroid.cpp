#include<bits/stdc++.h>
using namespace std;

class CentroidDecomposition {
public:
    int n;
    vector<vector<int>> adj;
    vector<int> sz,par;
    vector<bool> removed;

    CentroidDecomposition(int n):n(n)
    {
        adj.resize(n);
        sz.resize(n);
        par.assign(n,-1);
        removed.assign(n,false);
    }

    void addEdge(int u,int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfsSize(int u,int p)
    {
        sz[u]=1;

        for(int v:adj[u])
        {
            if(v==p || removed[v]) continue;

            dfsSize(v,u);
            sz[u]+=sz[v];
        }
    }

    int getCentroid(int u,int p,int total)
    {
        for(int v:adj[u])
        {
            if(v==p || removed[v]) continue;

            if(sz[v]>total/2)
                return getCentroid(v,u,total);
        }

        return u;
    }

    void decompose(int entry,int p)
    {
        dfsSize(entry,-1);

        int centroid=getCentroid(entry,-1,sz[entry]);

        par[centroid]=p;
        removed[centroid]=true;

        for(int v:adj[centroid])
        {
            if(removed[v]) continue;

            decompose(v,centroid);
        }
    }

    void build()
    {
        decompose(0,-1);
    }
};