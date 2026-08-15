# include<bits/stdc++.h>
using namespace std;

/* Requirement	merge()	identity()
Sum	a+b	0
Min	min(a,b)	INF
Max	max(a,b)	-INF
GCD	gcd(a,b)	0
XOR	a^b	0
AND	a&b	ALL_BITS_SET
OR	`a	b`
*/
class SegmentTree {
public:

    int n;
    vector<long long> tree;

    // CHANGE THIS
    long long merge(long long a, long long b) {
        return a + b;
    }

    // CHANGE THIS
    long long identity() {
        return 0;
    }

    SegmentTree(vector<long long>& a) {

        n = a.size();

        tree.resize(4 * n);

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

        build(2 * node + 1, mid + 1, r, a);

        tree[node] =
            merge(tree[2 * node],
                  tree[2 * node + 1]);
    }

    long long query(int node, int l, int r,
                    int ql, int qr) {

        // No overlap
        if(qr < l || r < ql)
            return identity();

        // Complete overlap
        if(ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) / 2;

        long long left =
            query(2 * node, l, mid, ql, qr);

        long long right =
            query(2 * node + 1,
                  mid + 1, r,
                  ql, qr);

        return merge(left, right);
    }

    void update(int node, int l, int r,
                int idx, long long val) {

        if(l == r) {
            tree[node] = val;
            return;
        }

        int mid = (l + r) / 2;

        if(idx <= mid)
            update(2 * node, l, mid, idx, val);
        else
            update(2 * node + 1,
                   mid + 1, r,
                   idx, val);

        tree[node] =
            merge(tree[2 * node],
                  tree[2 * node + 1]);
    }
};