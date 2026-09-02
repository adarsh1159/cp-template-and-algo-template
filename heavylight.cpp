#include<bits/stdc++.h>
using namespace std;

class HLD {
public:
    int n,timer;
    vector<vector<int>> adj;
    vector<int> parent,depth,sz,heavy,head,pos;
    vector<int> seg;

    HLD(int n):n(n)
    {
        adj.resize(n);
        parent.resize(n);
        depth.resize(n);
        sz.resize(n);
        heavy.assign(n,-1);
        head.resize(n);
        pos.resize(n);
        seg.resize(4*n);
        timer=0;
    }

    void addEdge(int u,int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dfs(int u,int p)
    {
        parent[u]=p;
        sz[u]=1;

        int mx=0;

        for(int v:adj[u])
        {
            if(v==p) continue;

            depth[v]=depth[u]+1;

            int sub=dfs(v,u);
            sz[u]+=sub;

            if(sub>mx)
            {
                mx=sub;
                heavy[u]=v;
            }
        }

        return sz[u];
    }

    void decompose(int u,int h)
    {
        head[u]=h;
        pos[u]=timer++;

        if(heavy[u]!=-1)
            decompose(heavy[u],h);

        for(int v:adj[u])
        {
            if(v==parent[u] || v==heavy[u]) continue;
            decompose(v,v);
        }
    }

    void build(int node,int l,int r,vector<int>&a)
    {
        if(l==r)
        {
            seg[node]=a[l];
            return;
        }

        int mid=(l+r)/2;

        build(2*node,l,mid,a);
        build(2*node+1,mid+1,r,a);

        seg[node]=seg[2*node]+seg[2*node+1];
    }

    void update(int node,int l,int r,int idx,int val)
    {
        if(l==r)
        {
            seg[node]=val;
            return;
        }

        int mid=(l+r)/2;

        if(idx<=mid)
            update(2*node,l,mid,idx,val);
        else
            update(2*node+1,mid+1,r,idx,val);

        seg[node]=seg[2*node]+seg[2*node+1];
    }

    int query(int node,int l,int r,int ql,int qr)
    {
        if(qr<l || r<ql)
            return 0;

        if(ql<=l && r<=qr)
            return seg[node];

        int mid=(l+r)/2;

        return query(2*node,l,mid,ql,qr)+
               query(2*node+1,mid+1,r,ql,qr);
    }

    int queryPath(int u,int v)
    {
        int ans=0;

        while(head[u]!=head[v])
        {
            if(depth[head[u]]<depth[head[v]])
                swap(u,v);

            ans+=query(1,0,n-1,pos[head[u]],pos[u]);

            u=parent[head[u]];
        }

        if(depth[u]>depth[v])
            swap(u,v);

        ans+=query(1,0,n-1,pos[u],pos[v]);

        return ans;
    }

    void updateNode(int u,int val)
    {
        update(1,0,n-1,pos[u],val);
    }

    void build(vector<int>&a)
    {
        dfs(0,-1);
        decompose(0,0);
        build(1,0,n-1,a);
    }
};