// Bitmask DP
// TC: O(N * 2^N)
// SC: O(2^N)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    vector<int> dp;

    int solve(int mask) {

        // All elements are selected
        if(mask == (1 << n) - 1)
            return 0;

        if(dp[mask] != -1)
            return dp[mask];

        int ans = INT_MAX;

        for(int i = 0; i < n; i++) {

            // i is not selected
            if(!(mask & (1 << i))) {

                int newMask = mask | (1 << i);

                // Add problem-specific cost
                int cost = 0;

                ans = min(ans, cost + solve(newMask));
            }
        }

        return dp[mask] = ans;
    }

    int solveDP() {

        dp.assign(1 << n, -1);

        return solve(0);
    }
};