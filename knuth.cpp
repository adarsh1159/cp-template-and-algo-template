#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = 4e18;

/*
    Knuth Optimization

    Interval DP:

        dp[l][r] =
            min(dp[l][k] + dp[k][r] + cost(l,r))

    with:

        opt[l][r-1] <= opt[l][r] <= opt[l+1][r]

    Complexity:

        Normal:   O(N^3)
        Knuth:    O(N^2)

    Typical problems:
        - Matrix / interval merging
        - Optimal BST
        - Stone merging variants
*/

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    for (auto &x : a)
        cin >> x;

    // Prefix sum if cost depends on range sum
    vector<ll> pref(n + 1);

    for (int i = 0; i < n; i++)
        pref[i + 1] = pref[i] + a[i];

    auto cost = [&](int l, int r) -> ll {
        // Example cost of [l, r)
        return pref[r] - pref[l];
    };

    vector<vector<ll>> dp(n + 1,
                           vector<ll>(n + 1, 0));

    vector<vector<int>> opt(n + 1,
                            vector<int>(n + 1));

    // Base cases
    for (int i = 0; i <= n; i++)
        opt[i][i] = i;

    /*
        Process intervals by increasing length.
    */
    for (int len = 2; len <= n; len++) {

        for (int l = 0; l + len <= n; l++) {

            int r = l + len;

            dp[l][r] = INF;

            /*
                Knuth property:

                    opt[l][r-1]
                    <= k
                    <= opt[l+1][r]
            */
            int start = opt[l][r - 1];
            int end = opt[l + 1][r];

            for (int k = start; k <= end; k++) {

                ll val =
                    dp[l][k] +
                    dp[k][r] +
                    cost(l, r);

                if (val < dp[l][r]) {

                    dp[l][r] = val;
                    opt[l][r] = k;
                }
            }
        }
    }

    cout << dp[0][n] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}