#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
    static const int ALPH = 26;

    struct Node {
        int nxt[ALPH];
        int link;
        vector<int> out;

        Node() {
            memset(nxt, -1, sizeof(nxt));
            link = 0;
        }
    };

    vector<Node> trie;

    AhoCorasick() {
        trie.push_back(Node());
    }

    // Insert a pattern
    void insert(string s, int id) {
        int node = 0;

        for (char c : s) {
            int x = c - 'a';

            if (trie[node].nxt[x] == -1) {
                trie[node].nxt[x] = trie.size();
                trie.push_back(Node());
            }

            node = trie[node].nxt[x];
        }

        trie[node].out.push_back(id);
    }

    // Build failure links
    void build() {
        queue<int> q;

        for (int c = 0; c < ALPH; c++) {
            int child = trie[0].nxt[c];

            if (child != -1) {
                trie[child].link = 0;
                q.push(child);
            } else {
                trie[0].nxt[c] = 0;
            }
        }

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int c = 0; c < ALPH; c++) {
                int child = trie[node].nxt[c];

                if (child != -1) {
                    trie[child].link =
                        trie[trie[node].link].nxt[c];

                    // Patterns ending at failure node
                    for (int id : trie[trie[child].link].out)
                        trie[child].out.push_back(id);

                    q.push(child);
                } else {
                    trie[node].nxt[c] =
                        trie[trie[node].link].nxt[c];
                }
            }
        }
    }

    // Search text
    vector<pair<int, int>> search(string text) {
        vector<pair<int, int>> ans;

        int node = 0;

        for (int i = 0; i < text.size(); i++) {
            node = trie[node].nxt[text[i] - 'a'];

            for (int id : trie[node].out) {
                ans.push_back({i, id});
            }
        }

        return ans;
    }
};