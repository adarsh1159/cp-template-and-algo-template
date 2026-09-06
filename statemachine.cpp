// State Machine DP
// TC: O(N * STATES)
// SC: O(N * STATES)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    vector<vector<int>> dp;

    int solve(int i, int state) {

        if(i == n)
            return 0;

        if(dp[i][state] != -1)
            return dp[i][state];

        int ans = INT_MIN;

        // Action 1
        {
            int newState = state;
            int value = 0;

            ans = max(ans, value + solve(i + 1, newState));
        }

        // Action 2
        {
            int newState = state;
            int value = 0;

            ans = max(ans, value + solve(i + 1, newState));
        }

        return dp[i][state] = ans;
    }

    int solveDP(int N, int STATES) {

        n = N;

        dp.assign(n, vector<int>(STATES, -1));

        return solve(0, 0);
    }
};