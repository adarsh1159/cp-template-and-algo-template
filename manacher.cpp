#include <bits/stdc++.h>
using namespace std;

// Name: Manacher's Algorithm
// TC: O(n)
// SC: O(n)

class Solution {
public:
    string longestPalindrome(string s) {
        string t = "^";

        for(char c : s) {
            t += "#";
            t += c;
        }

        t += "#$";

        int n = t.size();
        vector<int> p(n);

        int l = 0, r = 0;

        for(int i = 1; i < n - 1; i++) {
            int mir = l + r - i;

            if(i < r)
                p[i] = min(r - i, p[mir]);

            while(t[i + 1 + p[i]] == t[i - 1 - p[i]])
                p[i]++;

            if(i + p[i] > r) {
                l = i - p[i];
                r = i + p[i];
            }
        }

        int len = 0, center = 0;

        for(int i = 1; i < n - 1; i++) {
            if(p[i] > len) {
                len = p[i];
                center = i;
            }
        }

        int start = (center - len) / 2;

        return s.substr(start, len);
    }
};