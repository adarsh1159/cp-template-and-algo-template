#include <bits/stdc++.h>
using namespace std;

vector<int> lps(string &p)
{
    int n = p.size();
    vector<int> lps(n);

    int len = 0;
    int i = 1;

    while(i < n)
    {
        if(p[i] == p[len])
        {
            lps[i] = len + 1;
            len++;
            i++;
        }
        else
        {
            if(len != 0)
                len = lps[len - 1];
            else
                i++;
        }
    }

    return lps;
}

vector<int> kmp(string &s, string &p)
{
    vector<int> l = lps(p);
    vector<int> ans;

    int i = 0, j = 0;

    while(i < s.size())
    {
        if(s[i] == p[j])
        {
            i++;
            j++;
        }

        if(j == p.size())
        {
            ans.push_back(i - j);
            j = l[j - 1];
        }
        else if(i < s.size() && s[i] != p[j])
        {
            if(j != 0)
                j = l[j - 1];
            else
                i++;
        }
    }

    return ans;
}