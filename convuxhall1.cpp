#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
    CONVEX HULL TRICK
    ------------------
    
    Maintains lines:
        y = mx + c

    Supports:
        addLine(m, c)
        query(x)

    This version is for:
        1. Slopes added in monotonic order
        2. Queries x in monotonic order

    Example DP:
        dp[i] = min(dp[j] + m[j] * x[i] + c[j]);

    We insert:
        y = m[j] * x + c[j]

    Then:
        dp[i] = query(x[i]);

    Time:
        addLine -> O(1) amortized
        query   -> O(1) amortized

    Total:
        O(N)

    IMPORTANT:
        This template is for MIN queries.
*/

struct Line {
    ll m, c;

    ll value(ll x) {
        return m * x + c;
    }
};

struct CHT {

    vector<Line> hull;

    // Pointer used because x queries are monotonic
    int ptr = 0;

    /*
        Check whether l2 becomes useless.

        Suppose we have:

            l1
            l2
            l3

        If l2 will NEVER be the minimum,
        remove it.

        __int128 is used to avoid overflow
        during multiplication.
    */
    bool bad(Line l1, Line l2, Line l3) {

        /*
            Intersection(l1,l2) >= Intersection(l2,l3)

            Therefore l2 is unnecessary.
        */

        return (__int128)(l2.c - l1.c) * (l2.m - l3.m)
             >= (__int128)(l3.c - l2.c) * (l1.m - l2.m);
    }

    /*
        Add line:

            y = mx + c

        REQUIREMENT:
            Slopes must be added monotonically.

        Example:

            addLine(1, 5);
            addLine(3, 2);
            addLine(7, -4);

        increasing slopes -> valid
    */
    void addLine(ll m, ll c) {

        Line nw = {m, c};

        while (hull.size() >= 2 &&
               bad(hull[hull.size() - 2],
                   hull[hull.size() - 1],
                   nw)) {

            hull.pop_back();
        }

        hull.push_back(nw);

        // Keep pointer valid after removing lines
        ptr = min(ptr, (int)hull.size() - 1);
    }

    /*
        Query minimum value at x.

        REQUIREMENT:
            x values must be monotonic.

        Example:

            query(1);
            query(5);
            query(10);
            query(20);

        increasing x -> valid
    */
    ll query(ll x) {

        /*
            Move forward while next line
            gives a smaller/equal value.
        */
        while (ptr + 1 < hull.size() &&
               hull[ptr + 1].value(x) <= hull[ptr].value(x)) {

            ptr++;
        }

        return hull[ptr].value(x);
    }
};