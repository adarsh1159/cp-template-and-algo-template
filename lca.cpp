#include <bits/stdc++.h>
using namespace std;

/*
Binary Lifting

up[node][j] = 2^j-th ancestor of node

up[node][0] = parent
up[node][1] = 2nd ancestor
up[node][2] = 4th ancestor
up[node][3] = 8th ancestor

Build:
up[node][j] = up[up[node][j-1]][j-1]

To find kth ancestor:
Check bits of k.
If j-th bit is set, move node to up[node][j].

TC:
Preprocessing = O(N log N)
Query = O(log N)

SC:
O(N log N)
*/

class BinaryLifting {
public:
    int LOG;
    vector<vector<int>> up;

    BinaryLifting(int n, vector<int>& parent) {
        LOG=1;

        while((1<<LOG)<=n)
            LOG++;

        up.assign(n,vector<int>(LOG,-1));

        for(int i=0;i<n;i++)
            up[i][0]=parent[i];

        for(int j=1;j<LOG;j++)
        {
            for(int i=0;i<n;i++)
            {
                if(up[i][j-1]!=-1)
                    up[i][j]=up[up[i][j-1]][j-1];
            }
        }
    }

    int getKthAncestor(int node,int k) {
        for(int j=0;j<LOG;j++)
        {
            if(k&(1<<j))
            {
                node=up[node][j];

                if(node==-1)
                    return -1;
            }
        }

        return node;
    }
};