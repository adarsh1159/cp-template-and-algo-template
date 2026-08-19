#include<bits/stdc++.h>
using namespace std;

// ============================================================
// FENWICK TREE / BIT
// Point Update + Range Query
// 0-indexed
// TC: O(log N) update/query
// SC: O(N)
// ============================================================

template <typename T>
struct Fenwick {
    int n;
    vector<T> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    Fenwick(const vector<T>& a) : n(a.size()), bit(n + 1, 0) {
        for (int i = 0; i < n; i++)
            add(i, a[i]);
    }

    // a[idx] += val
    void add(int idx, T val) {
        for (++idx; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    // sum [0 ... idx]
    T prefixSum(int idx) const {
        T res = 0;

        for (++idx; idx > 0; idx -= idx & -idx)
            res += bit[idx];

        return res;
    }

    // sum [l ... r]
    T rangeSum(int l, int r) const {
        if (l > r)
            return 0;

        return prefixSum(r) -
               (l ? prefixSum(l - 1) : 0);
    }

    // sum [0 ... n-1]
    T totalSum() const {
        return prefixSum(n - 1);
    }
};