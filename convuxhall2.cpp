#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
    LI CHAO TREE
    ------------

    Maintains lines:

        y = mx + c

    Supports:

        addLine(m, c)
        query(x)

    Unlike normal CHT:

        Slopes do NOT need to be sorted.

        Queries x do NOT need to be sorted.

    Therefore:

        Arbitrary slopes
        Arbitrary queries

    Complexity:

        addLine -> O(log X)
        query   -> O(log X)

    This version performs MIN queries.
*/

struct LiChao {

    static const ll INF = 4e18;

    /*
        Change these according to problem.

        Example:
            x belongs to [0, 1e6]

        If x can be negative:

            MIN_X = -1e6
            MAX_X =  1e6
    */
    static const int MIN_X = 0;
    static const int MAX_X = 1000000;

    struct Line {

        ll m, c;

        /*
            Calculate:

                y = mx + c
        */
        ll value(ll x) const {
            return m * x + c;
        }
    };

    /*
        Segment tree storing one useful line
        at every node.
    */
    vector<Line> tree;

    /*
        Tells whether a node actually contains
        a line.
    */
    vector<bool> used;

    LiChao() {

        tree.resize(4 * (MAX_X + 1));

        used.resize(4 * (MAX_X + 1), false);
    }

    /*
        Insert a line into the Li Chao Tree.
    */
    void addLine(Line nw, int node, int l, int r) {

        /*
            If node has no line,
            simply put the new line here.
        */
        if (!used[node]) {

            tree[node] = nw;

            used[node] = true;

            return;
        }

        int mid = l + (r - l) / 2;

        /*
            Compare which line is better
            at the left endpoint.
        */
        bool leftBetter =
            nw.value(l) < tree[node].value(l);

        /*
            Compare which line is better
            at the middle.
        */
        bool midBetter =
            nw.value(mid) < tree[node].value(mid);

        /*
            If new line is better at middle,
            keep new line at this node.

            The old line may still be useful
            on one side, so continue with it.
        */
        if (midBetter) {

            swap(tree[node], nw);
        }

        /*
            Leaf node.
        */
        if (l == r)
            return;

        /*
            If the line we didn't keep at the node
            is better on the left side,
            send it to left child.

            Otherwise send it to right child.
        */
        if (leftBetter != midBetter) {

            addLine(nw, node * 2, l, mid);

        } else {

            addLine(nw, node * 2 + 1, mid + 1, r);
        }
    }

    /*
        Public function:

            addLine(m, c)
    */
    void addLine(ll m, ll c) {

        addLine({m, c}, 1, MIN_X, MAX_X);
    }

    /*
        Query minimum value at x.
    */
    ll query(ll x, int node, int l, int r) {

        /*
            Current node's line is one candidate.
        */
        ll ans = used[node]
               ? tree[node].value(x)
               : INF;

        /*
            Leaf.
        */
        if (l == r)
            return ans;

        int mid = l + (r - l) / 2;

        /*
            Only one child can contain x.
        */
        if (x <= mid) {

            ans = min(
                ans,
                query(x, node * 2, l, mid)
            );

        } else {

            ans = min(
                ans,
                query(x, node * 2 + 1, mid + 1, r)
            );
        }

        return ans;
    }

    /*
        Public query.
    */
    ll query(ll x) {

        return query(x, 1, MIN_X, MAX_X);
    }
};