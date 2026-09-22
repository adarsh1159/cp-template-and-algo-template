#include <bits/stdc++.h>
using namespace std;

// Rabin-Karp String Matching
// TC: O(n + m) average, O(n * m) worst case
// SC: O(1)

vector<int> rabinKarp(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();

    vector<int> ans;
    if (m > n) return ans;

    const long long BASE = 256;
    const long long MOD = 1e9 + 7;

    long long patHash = 0;
    long long textHash = 0;
    long long power = 1;

    // BASE^(m-1)
    for (int i = 0; i < m - 1; i++)
        power = (power * BASE) % MOD;

    // Initial window hash
    for (int i = 0; i < m; i++) {
        patHash = (patHash * BASE + pattern[i]) % MOD;
        textHash = (textHash * BASE + text[i]) % MOD;
    }

    for (int i = 0; i <= n - m; i++) {

        // Hash match -> verify characters
        if (patHash == textHash) {
            bool ok = true;

            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    ok = false;
                    break;
                }
            }

            if (ok)
                ans.push_back(i);
        }

        // Rolling hash: remove old + add new
        if (i < n - m) {
            textHash = (textHash - text[i] * power) % MOD;
            if (textHash < 0)
                textHash += MOD;

            textHash = (textHash * BASE + text[i + m]) % MOD;
        }
    }

    return ans;
}