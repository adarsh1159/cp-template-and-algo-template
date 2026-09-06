// Digit DP
// TC: O(D * STATES * 10)
// SC: O(D * STATES)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long dp[20][2][2][100];
    bool vis[20][2][2][100];

    string s;

    long long solve(int pos, int tight, int started, int state) {

        if(pos == s.size())
            return 1;

        if(vis[pos][tight][started][state])
            return dp[pos][tight][started][state];

        vis[pos][tight][started][state] = true;

        long long ans = 0;

        int limit = tight ? s[pos] - '0' : 9;

        for(int digit = 0; digit <= limit; digit++) {

            int newTight =
                tight && (digit == s[pos] - '0');

            int newStarted =
                started || (digit != 0);

            int newState = state;

            // Update state

            ans += solve(
                pos + 1,
                newTight,
                newStarted,
                newState
            );
        }

        return dp[pos][tight][started][state] = ans;
    }

    long long count(long long x) {

        if(x < 0)
            return 0;

        s = to_string(x);

        memset(vis, false, sizeof(vis));

        return solve(0, 1, 0, 0);
    }

    long long rangeCount(long long L, long long R) {
        return count(R) - count(L - 1);
    }
};