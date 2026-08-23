// ============================================================
// COORDINATE COMPRESSION
// ============================================================
// Compress large values into [0 ... m-1]
// Time: O(n log n)
// Space: O(n)
//
// Example:
// a = {100000, 5, 100000, 50}
// compressed = {2, 0, 2, 1}
// ============================================================
#include<bits/stdc++.h>
using namespace std;
vector<int> coordinateCompress(vector<int> a) {

    vector<int> vals = a;

    sort(vals.begin(), vals.end());

    vals.erase(
        unique(vals.begin(), vals.end()),
        vals.end()
    );

    for (int &x : a) {
        x = lower_bound(
            vals.begin(),
            vals.end(),
            x
        ) - vals.begin();
    }

    return a;
}