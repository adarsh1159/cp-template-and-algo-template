#include<bits/stdc++.h>
using namespace std;

// ============================================================
// SPARSE TABLE - RANGE MINIMUM QUERY
// 0-indexed
//
// Build: O(N log N)
// Query: O(1)
// Space: O(N log N)
// ============================================================

struct SparseTable {
    int n, LOG;
    vector<vector<int>> st;

    SparseTable(vector<int>& a) {
        n = a.size();

        LOG = 1;
        while ((1 << LOG) <= n)
            LOG++;

        st.assign(LOG, vector<int>(n));

        st[0] = a;

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = min(
                    st[j - 1][i],
                    st[j - 1][i + (1 << (j - 1))]
                );
            }
        }
    }

    int query(int l, int r) {
        int len = r - l + 1;

        int j = 31 - __builtin_clz(len);

        return min(
            st[j][l],
            st[j][r - (1 << j) + 1]
        );
    }
};
