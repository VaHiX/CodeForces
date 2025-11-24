// Problem: CF 1424 M - Ancient Language
// https://codeforces.com/contest/1424/problem/M

/*
M. Ancient Language
Purpose: Reconstruct the lexicographically ordered alphabet from a set of words in an ancient dictionary.
Techniques:
  - Topological sorting to determine ordering of characters.
  - Floyd-Warshall algorithm to detect cycles and transitive relations.
  - Graph representation using adjacency matrix.
Time Complexity: O(26^3 + N*K) where N is number of pages, K is words per page (max 10^3).
Space Complexity: O(26^2 + N*K) for storing character comparisons and input strings.

Algorithms Used:
1. Pairwise comparison of adjacent strings to build ordering constraints.
2. Floyd-Warshall to compute transitive closure of character ordering.
3. Topological sorting via greedy selection of characters with no incoming edges.
*/

#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
int n, k;
char s[1000005][105];
int f[26][26]; // Adjacency matrix for character ordering

void cpr(char *s, char *t) {
  int n = strlen(s), m = strlen(t);
  for (int i = 0; i < min(n, m); i++) {
    if (s[i] != t[i]) {
      f[s[i] - 'a'][t[i] - 'a'] = 1; // Mark that s[i] comes before t[i]
      return;
    }
  }
  if (n < m) { // If prefix of s is same as t, but s is shorter, invalid
    cout << "IMPOSSIBLE";
    exit(0);
  }
}

bool vis[27]; // Tracks which characters are present in input
bool flg;     // Detects if there's a cycle (self-loop in graph)
int cnt;      // Count of unique characters
bool sk[27];  // Tracks visited characters for topological sort
char ans[27]; // Resulting ordered alphabet

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    int p;
    cin >> p;
    for (int j = p * k + 1; j <= (p + 1) * k; j++) {
      cin >> s[j];
      int len = strlen(s[j]);
      for (int aa = 0; aa < len; aa++)
        vis[s[j][aa] - 'a'] = 1; // Mark characters as present
    }
  }
  
  // Compare each adjacent pair of words and build constraints
  for (int i = 2; i <= n * k; i++) {
    cpr(s[i], s[i - 1]);
  }
  
  // Floyd-Warshall to find transitive relations (i.e., if a < b and b < c, then a < c)
  for (int k = 0; k < 26; k++)
    for (int i = 0; i < 26; i++)
      for (int j = 0; j < 26; j++)
        f[i][j] |= f[i][k] & f[k][j];
  
  // Check for cycles (self-loops)
  for (int i = 0; i < 26; i++)
    flg |= f[i][i];
  
  if (flg) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  
  // Count number of unique characters
  for (int i = 0; i < 26; i++)
    cnt += vis[i];
  
  // Topological sort: find character with no incoming edges and mark it as visited
  for (int i = 1; i <= cnt; i++) {
    char c;
    for (int j = 0; j < 26; j++) {
      if (vis[j] and !sk[j]) {
        int p = 0;
        for (int k = 0; k < 26; k++) {
          p |= (!sk[k] and f[j][k]); // Check if any unvisited node has an edge to this node
        }
        if (!p) { // No unvisited nodes point to this one => can be selected
          c = j + 'a';
          break;
        }
      }
    }
    sk[c - 'a'] = 1; // Mark as added to result
    ans[i - 1] = c;
  }
  
  cout << ans;
}


// https://github.com/VaHiX/codeForces/