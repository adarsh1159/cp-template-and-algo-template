// Profile DP
// TC: O(N * STATES * TRANSITIONS)
// SC: O(N * STATES)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, m;

    int dp[105][1 << 10];

    int solve(int row, int mask) {

        // All rows processed
        if(row == n)
            return 0;

        if(dp[row][mask] != -1)
            return dp[row][mask];

        int ans = 0;

        // Try every possible profile of current row
        for(int newMask = 0; newMask < (1 << m); newMask++) {

            // Check whether current mask and newMask
            // satisfy the problem's constraints
            bool valid = true;

            if(!valid)
                continue;

            int cost = 0;  // problem-specific transition cost

            ans = max(ans, cost + solve(row + 1, newMask));
        }

        return dp[row][mask] = ans;
    }

    int solveDP() {
        memset(dp, -1, sizeof(dp));

        return solve(0, 0);
    }
};