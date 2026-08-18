// ============================================================
// MERGE SORT TREE - ALL COMMON VARIATIONS
// ============================================================
// Build  : O(n log n)
// Query  : O(log^2 n)
// Memory : O(n log n)
//
// Supports:
// 1. Count < x
// 2. Count <= x
// 3. Count > x
// 4. Count >= x
// 5. Minimum element >= x
// 6. Maximum element <= x
// 7. Minimum element in range
// 8. Maximum element in range
//
// NOTE:
// This is a STATIC data structure.
// For updates, use Segment Tree / Fenwick / advanced MST.
// ============================================================
#include<bits/stdc++.h>
using namespace std;
class MergeSortTree {
    int n;
    vector<vector<int>> tree;

    void build(int node, int l, int r,
               const vector<int>& a) {

        if (l == r) {
            tree[node] = {a[l]};
            return;
        }

        int mid = l + (r - l) / 2;

        build(node * 2, l, mid, a);
        build(node * 2 + 1, mid + 1, r, a);

        tree[node].resize(
            tree[node * 2].size() +
            tree[node * 2 + 1].size()
        );

        merge(
            tree[node * 2].begin(),
            tree[node * 2].end(),
            tree[node * 2 + 1].begin(),
            tree[node * 2 + 1].end(),
            tree[node].begin()
        );
    }

    // --------------------------------------------------------
    // Count elements satisfying condition in [ql, qr]
    // --------------------------------------------------------

    int countLess(int node, int l, int r,
                  int ql, int qr, int x) {

        if (r < ql || qr < l)
            return 0;

        if (ql <= l && r <= qr) {
            return lower_bound(
                tree[node].begin(),
                tree[node].end(),
                x
            ) - tree[node].begin();
        }

        int mid = l + (r - l) / 2;

        return countLess(node * 2, l, mid,
                         ql, qr, x)
             + countLess(node * 2 + 1, mid + 1, r,
                         ql, qr, x);
    }

    int countLE(int node, int l, int r,
                int ql, int qr, int x) {

        if (r < ql || qr < l)
            return 0;

        if (ql <= l && r <= qr) {
            return upper_bound(
                tree[node].begin(),
                tree[node].end(),
                x
            ) - tree[node].begin();
        }

        int mid = l + (r - l) / 2;

        return countLE(node * 2, l, mid,
                       ql, qr, x)
             + countLE(node * 2 + 1, mid + 1, r,
                       ql, qr, x);
    }

    // --------------------------------------------------------
    // Minimum element >= x
    // --------------------------------------------------------

    int minGE(int node, int l, int r,
              int ql, int qr, int x) {

        if (r < ql || qr < l)
            return INT_MAX;

        if (ql <= l && r <= qr) {

            auto it = lower_bound(
                tree[node].begin(),
                tree[node].end(),
                x
            );

            if (it == tree[node].end())
                return INT_MAX;

            return *it;
        }

        int mid = l + (r - l) / 2;

        return min(
            minGE(node * 2, l, mid,
                  ql, qr, x),

            minGE(node * 2 + 1, mid + 1, r,
                  ql, qr, x)
        );
    }

    // --------------------------------------------------------
    // Maximum element <= x
    // --------------------------------------------------------

    int maxLE(int node, int l, int r,
              int ql, int qr, int x) {

        if (r < ql || qr < l)
            return INT_MIN;

        if (ql <= l && r <= qr) {

            auto it = upper_bound(
                tree[node].begin(),
                tree[node].end(),
                x
            );

            if (it == tree[node].begin())
                return INT_MIN;

            --it;
            return *it;
        }

        int mid = l + (r - l) / 2;

        return max(
            maxLE(node * 2, l, mid,
                  ql, qr, x),

            maxLE(node * 2 + 1, mid + 1, r,
                  ql, qr, x)
        );
    }

    // --------------------------------------------------------
    // Minimum value in [ql, qr]
    // --------------------------------------------------------

    int rangeMin(int node, int l, int r,
                 int ql, int qr) {

        if (r < ql || qr < l)
            return INT_MAX;

        if (ql <= l && r <= qr)
            return tree[node][0];

        int mid = l + (r - l) / 2;

        return min(
            rangeMin(node * 2, l, mid,
                     ql, qr),

            rangeMin(node * 2 + 1, mid + 1, r,
                     ql, qr)
        );
    }

    // --------------------------------------------------------
    // Maximum value in [ql, qr]
    // --------------------------------------------------------

    int rangeMax(int node, int l, int r,
                 int ql, int qr) {

        if (r < ql || qr < l)
            return INT_MIN;

        if (ql <= l && r <= qr)
            return tree[node].back();

        int mid = l + (r - l) / 2;

        return max(
            rangeMax(node * 2, l, mid,
                     ql, qr),

            rangeMax(node * 2 + 1, mid + 1, r,
                     ql, qr)
        );
    }

public:

    MergeSortTree(const vector<int>& a) {

        n = a.size();

        tree.resize(4 * n);

        build(1, 0, n - 1, a);
    }

    // ========================================================
    // PUBLIC FUNCTIONS
    // ========================================================

    // Count < x
    int countLess(int l, int r, int x) {
        return countLess(1, 0, n - 1,
                         l, r, x);
    }

    // Count <= x
    int countLE(int l, int r, int x) {
        return countLE(1, 0, n - 1,
                       l, r, x);
    }

    // Count > x
    int countGreater(int l, int r, int x) {

        return (r - l + 1)
             - countLE(l, r, x);
    }

    // Count >= x
    int countGE(int l, int r, int x) {

        return (r - l + 1)
             - countLess(l, r, x);
    }

    // Minimum element >= x
    int minGreaterEqual(int l, int r, int x) {

        return minGE(1, 0, n - 1,
                     l, r, x);
    }

    // Maximum element <= x
    int maxLessEqual(int l, int r, int x) {

        return maxLE(1, 0, n - 1,
                     l, r, x);
    }

    // Minimum element in range
    int rangeMinimum(int l, int r) {

        return rangeMin(1, 0, n - 1,
                        l, r);
    }

    // Maximum element in range
    int rangeMaximum(int l, int r) {

        return rangeMax(1, 0, n - 1,
                        l, r);
    }
};