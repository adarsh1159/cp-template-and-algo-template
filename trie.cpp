// ============================================================
// TRIE
// Supports:
// 1. Insert word
// 2. Search exact word
// 3. Search prefix
// 4. Erase word
// 5. Count words / prefixes
//
// Alphabet: lowercase English letters
//
// Insert:       O(L)
// Search:       O(L)
// Prefix:       O(L)
// Erase:        O(L)
// Space:        O(N * L)
// ============================================================
#include<bits/stdc++.h>
using namespace std;

struct Trie {

    struct Node {
        Node* child[26];
        int prefixCnt;
        int wordCnt;

        Node() {
            memset(child, 0, sizeof(child));
            prefixCnt = 0;
            wordCnt = 0;
        }
    };

    Node* root;

    Trie() {
        root = new Node();
    }

    // Insert a word
    void insert(const string& word) {
        Node* curr = root;

        for (char ch : word) {
            int idx = ch - 'a';

            if (!curr->child[idx])
                curr->child[idx] = new Node();

            curr = curr->child[idx];
            curr->prefixCnt++;
        }

        curr->wordCnt++;
    }

    // Search exact word
    bool search(const string& word) {
        Node* curr = root;

        for (char ch : word) {
            int idx = ch - 'a';

            if (!curr->child[idx])
                return false;

            curr = curr->child[idx];
        }

        return curr->wordCnt > 0;
    }

    // Does any word start with prefix?
    bool startsWith(const string& prefix) {
        Node* curr = root;

        for (char ch : prefix) {
            int idx = ch - 'a';

            if (!curr->child[idx])
                return false;

            curr = curr->child[idx];
        }

        return true;
    }

    // Number of words having this prefix
    int countPrefix(const string& prefix) {
        Node* curr = root;

        for (char ch : prefix) {
            int idx = ch - 'a';

            if (!curr->child[idx])
                return 0;

            curr = curr->child[idx];
        }

        return curr->prefixCnt;
    }

    // Number of times this exact word was inserted
    int countWord(const string& word) {
        Node* curr = root;

        for (char ch : word) {
            int idx = ch - 'a';

            if (!curr->child[idx])
                return 0;

            curr = curr->child[idx];
        }

        return curr->wordCnt;
    }

    // Erase one occurrence
    void erase(const string& word) {
        if (!search(word))
            return;

        Node* curr = root;

        for (char ch : word) {
            int idx = ch - 'a';

            curr = curr->child[idx];
            curr->prefixCnt--;
        }

        curr->wordCnt--;
    }
};