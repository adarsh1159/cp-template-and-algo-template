// ============================================================
// DSU / UNION FIND
//
// Supports:
// 1. Find parent
// 2. Union two components
// 3. Check if two nodes belong to same component
// 4. Component size
// 5. Number of components
//
// Optimizations:
// - Path Compression
// - Union by Size
//
// TC:
// find  -> O(alpha(N)) amortized
// union -> O(alpha(N)) amortized
//
// SC: O(N)
// ============================================================
#include<bits/stdc++.h>
using namespace std;

struct DSU {

    vector<int> parent;
    vector<int> sz;
    int components;

    // Constructor
    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);

        components = n;

        iota(parent.begin(), parent.end(), 0);
    }

    // Find representative of component
    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    // Union two components
    // Returns true if merged, false if already connected
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        // Union by size
        if (sz[a] < sz[b])
            swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        components--;

        return true;
    }

    // Are a and b in the same component?
    bool same(int a, int b) {
        return find(a) == find(b);
    }

    // Size of component containing x
    int size(int x) {
        return sz[find(x)];
    }

    // Number of connected components
    int count() {
        return components;
    }
};
