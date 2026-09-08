#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = 4e18;

/*
    Divide & Conquer DP Optimization

    DP:

        dp[g][i] =
            min over j < i:
            dp[g-1][j] + cost(j, i)

    If optimal j is monotonic:

        opt[g][i] <= opt[g][i+1]

    Complexity:

        Normal DP: O(K * N^2)

        Optimized: O(K * N * log N)
*/

int n, K;

vector<ll> prev_dp, cur_dp;

/*
    Cost of taking segment [j, i).

    Modify this according to the problem.
*/
ll cost(int j, int i) {
    // return ...
    return 0;
}

/*
    Calculate cur_dp[l ... r]

    optL = minimum possible optimal j
    optR = maximum possible optimal j
*/
void compute(int l, int r, int optL, int optR) {

    if (l > r)
        return;

    int mid = (l + r) / 2;

    pair<ll, int> best = {INF, -1};

    int start = optL;
    int end = min(mid, optR);

    for (int j = start; j <= end; j++) {

        ll val = prev_dp[j] + cost(j, mid);

        if (val < best.first) {
            best = {val, j};
        }
    }

    cur_dp[mid] = best.first;

    int opt = best.second;

    // Left side
    compute(l, mid - 1, optL, opt);

    // Right side
    compute(mid + 1, r, opt, optR);
}

void solve() {
    cin >> n >> K;

    prev_dp.assign(n + 1, INF);
    cur_dp.assign(n + 1, INF);

    prev_dp[0] = 0;

    for (int g = 1; g <= K; g++) {

        fill(cur_dp.begin(), cur_dp.end(), INF);

        compute(1, n, 0, n);

        prev_dp.swap(cur_dp);
    }

    cout << prev_dp[n] << '\n';
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