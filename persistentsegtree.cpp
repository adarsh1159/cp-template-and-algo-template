# include<bits/stdc++.h>
using namespace std;

class PersistentSegTree {
public:

    struct Node {

        int left = 0;
        int right = 0;

        long long val = 0;
    };

    vector<Node> tree;

    PersistentSegTree() {
        tree.push_back(Node());
    }

    // CHANGE THIS
    long long merge(long long a, long long b) {
        return a + b;
    }

    int update(int prev,
               int l, int r,
               int idx,
               long long val) {

        int cur = tree.size();

        tree.push_back(tree[prev]);

        if(l == r) {

            tree[cur].val += val;

            return cur;
        }

        int mid = (l + r) / 2;

        if(idx <= mid) {

            tree[cur].left =
                update(tree[prev].left,
                       l, mid,
                       idx, val);

        }
        else {

            tree[cur].right =
                update(tree[prev].right,
                       mid + 1, r,
                       idx, val);
        }

        tree[cur].val =
            merge(
                tree[tree[cur].left].val,
                tree[tree[cur].right].val
            );

        return cur;
    }

    long long query(int node,
                    int l, int r,
                    int ql, int qr) {

        if(node == 0 ||
           qr < l ||
           r < ql)
            return 0;

        if(ql <= l && r <= qr)
            return tree[node].val;

        int mid = (l + r) / 2;

        return merge(
            query(tree[node].left,
                  l, mid,
                  ql, qr),

            query(tree[node].right,
                  mid + 1, r,
                  ql, qr)
        );
    }
};