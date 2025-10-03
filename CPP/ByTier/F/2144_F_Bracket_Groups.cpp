// Problem: CF 2144 F - Bracket Groups
// https://codeforces.com/contest/2144/problem/F

/*
F. Bracket Groups
Algorithms/Techniques: Aho-Corasick automaton, dynamic programming, string matching.
Time Complexity: O(n * k^2 + k^3), where n is number of strings and k is the length of target regular bracket sequence.
Space Complexity: O(k^2), for the trie and DP table storage.

The problem asks to partition n bracket sequences into minimum groups such that each group can be associated with a valid
regular bracket sequence of length k (k is even). Each string in a group must NOT be a substring of the associated regular bracket sequence.

Approach:
1. Build an Aho-Corasick automaton using all given strings to find forbidden substrings efficiently.
2. Use dynamic programming on the automaton states to determine which combinations of bracket sequences can be placed together
   under the constraint that there exists a valid k-length regular bracket sequence not containing any of them.
3. If a valid combination is found, output one group with constructed regular sequence and indices.
4. Otherwise, partition into two groups using known regular sequences like (())...() or ()()...(), which are guaranteed to work.

*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;
struct Trie {
  int ch[2];
  int fail, ed;
} t[2500];
string s[50];
int tot;
void ins(string &s) {
  int u = 1;
  for (int i = 0; i < s.length(); i += 1) {
    int &v = t[u].ch[s[i] == ')']; // Map '(' to 0, ')' to 1
    if (v == 0)
      v = ++tot;
    u = v;
  }
  t[u].ed = 1; // Mark end of a pattern string
}
void build() {
  t[0].ch[0] = t[0].ch[1] = 1;
  queue<int> q;
  q.push(1);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 2; i++) {
      int &v = t[u].ch[i];
      if (v == 0) {
        v = t[t[u].fail].ch[i]; // Set failure link to parent's child (if not exist)
      } else {
        t[v].fail = t[t[u].fail].ch[i]; // Set failure link of child
        t[v].ed |= t[t[v].fail].ed;     // Propagate pattern match from fail state
        q.push(v);                      // Continue BFS to build further fail links
      }
    }
  }
}
int n, K;
int dp[51][2500][26];
pair<int, int> p[51][2500][26];
bool include(string &a, string &b) {
  for (int i = 0; i <= a.length() - b.length(); i++) {
    if (a.substr(i, b.length()) == b)
      return true;
  }
  return false;
}
void solve() {
  cin >> n >> K;
  tot = 1;
  for (int i = 0; i < n; i++) {
    cin >> s[i];
    // Special case check if input is singleton strings like "()", "(", ")"
    if (s[i] == "()" || s[i] == "(" || s[i] == ")") {
      printf("-1\n");
      return;
    }
    ins(s[i]); // Insert string into trie
  }
  build();   // Build failure links for Aho-Corasick

  dp[0][1][0] = 1; // Base case: at beginning, state=1, imbalance=0
  for (int i = 0; i < K; i++) {
    for (int u = 1; u <= tot; u++) {
      for (int j = 0; j <= K >> 1; j++) { // j is depth of balance (imbalance in brackets)
        if (!dp[i][u][j])
          continue;
        for (int k = 0; k < 2; k++) {
          int &v = t[u].ch[k];      // Next node in transition
          if (t[v].ed)               // Skip if we hit a forbidden pattern
            continue;
          int nxt = j + (k ? -1 : 1); // Adjust balance when inserting bracket
          if (nxt < 0 || nxt > K >> 1)
            continue; // Balance overflow
          dp[i + 1][v][nxt] = 1;
          p[i + 1][v][nxt] = {u, k}; // Store backtracking info
        }
      }
    }
  }

  char ans[55] = "";
  for (int i = 1; i <= tot; i++) {
    if (dp[K][i][0]) { // If we end up at balance zero and use full K positions
      int u = i, d = 0;
      for (int i = K - 1; i >= 0; i--) { // Backtrack to generate actual valid sequence
        auto [la, k] = p[i + 1][u][d];
        ans[i] = "()"[k];
        u = la;
        d -= (k ? -1 : 1);
      }
      printf("1\n%s\n%d\n", ans, n);
      for (int i = 1; i <= n; i++) {
        printf("%d%c", i, " \n"[i == n]);
      }
      return;
    }
  }

  // Fall back: Try to use known constructions.
  string s1, s2;
  vector<int> ans1, ans2;
  for (int i = 0; i < K >> 1; i++) {
    s1 += '(';   // e.g., "(("
    s2 += "()";  // e.g., "()"
  }
  for (int i = 0; i < K >> 1; i++) {
    s1 += ')';
  }

  for (int i = 0; i < n; i++) {
    if (include(s1, s[i])) { // If pattern matches one of those prefixes
      ans2.push_back(i + 1);
    } else
      ans1.push_back(i + 1);
  }
  
  cout << 2 << "\n";
  cout << s1 << "\n";            // First group regular sequence
  cout << ans1.size() << "\n";   // Size of first group
  for (int i : ans1) {           // Indices in first group
    cout << i << " \n"[i == ans1.back()];
  }
  cout << s2 << "\n";            // Second group regular sequence
  cout << ans2.size() << "\n";   // Size of second group
  for (int i : ans2) {           // Indices in second group
    cout << i << " \n"[i == ans2.back()];
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/