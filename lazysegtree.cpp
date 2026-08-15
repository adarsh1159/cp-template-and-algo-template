# include<bits/stdc++.h>
using namespace std;

class LazySegTree {
public:

    int n;

    vector<long long> tree;
    vector<long long> lazy;

    // CHANGE THIS
    long long merge(long long a, long long b) {
        return a + b;
    }

    // Identity for query
    long long identity() {
        return 0;
    }

    LazySegTree(vector<long long>& a) {

        n = a.size();

        tree.resize(4 * n);
        lazy.assign(4 * n, 0);

        build(1, 0, n - 1, a);
    }

    void build(int node, int l, int r,
               vector<long long>& a) {

        if(l == r) {
            tree[node] = a[l];
            return;
        }

        int mid = (l + r) / 2;

        build(2 * node, l, mid, a);

        build(2 * node + 1,
              mid + 1, r, a);

        tree[node] =
            merge(tree[2 * node],
                  tree[2 * node + 1]);
    }

    void apply(int node, int l, int r,
               long long val) {

        // CHANGE according to query
        tree[node] +=
            val * (r - l + 1);

        lazy[node] += val;
    }

    void push(int node, int l, int r) {

        if(lazy[node] == 0)
            return;

        int mid = (l + r) / 2;

        apply(2 * node, l, mid,
              lazy[node]);

        apply(2 * node + 1,
              mid + 1, r,
              lazy[node]);

        lazy[node] = 0;
    }

    void update(int node, int l, int r,
                int ql, int qr,
                long long val) {

        if(qr < l || r < ql)
            return;

        if(ql <= l && r <= qr) {

            apply(node, l, r, val);

            return;
        }

        push(node, l, r);

        int mid = (l + r) / 2;

        update(2 * node, l, mid,
               ql, qr, val);

        update(2 * node + 1,
               mid + 1, r,
               ql, qr, val);

        tree[node] =
            merge(tree[2 * node],
                  tree[2 * node + 1]);
    }

    long long query(int node, int l, int r,
                    int ql, int qr) {

        if(qr < l || r < ql)
            return identity();

        if(ql <= l && r <= qr)
            return tree[node];

        push(node, l, r);

        int mid = (l + r) / 2;

        return merge(
            query(2 * node, l, mid,
                  ql, qr),

            query(2 * node + 1,
                  mid + 1, r,
                  ql, qr)
        );
    }
};