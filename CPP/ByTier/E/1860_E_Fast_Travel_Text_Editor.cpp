// Problem: CF 1860 E - Fast Travel Text Editor
// https://codeforces.com/contest/1860/problem/E

/*
Code Purpose:
This program solves the problem of finding the minimum number of operations to move a cursor between two positions in a string,
with specific move rules:
1. Move cursor one position left or right.
2. Jump to any position between two adjacent letters that match the current left and right cursor neighbors.

Algorithms/Techniques:
- Preprocessing: For each pair of adjacent characters, we create a unique identifier (a*26 + b).
- BFS: For each unique character pair, we perform BFS to compute minimum distances from all positions with that pair to other positions.
- Optimization: We use a hybrid of direct distance and BFS-computed distances to efficiently answer queries.

Time Complexity:
- Preprocessing: O(n), where n is the length of the string.
- BFS for each of the 26*26 possible character pairs: O(n) in total across all pairs.
- Query processing: O(m), where m is the number of queries.
- Overall Time Complexity: O(n + m)

Space Complexity:
- The space used is O(n + 26*26) for storing adjacency lists, distance arrays, and input data.
- Overall Space Complexity: O(n)
*/

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using pii = pair<int, int>;
const int N = 5e4;
const int K = 26 * 26;
const int INF = 1e9;
int dist[N + K];
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  string s;
  cin >> s;
  int n = s.size();
  int par[n]; // Stores the unique identifier for each pair of adjacent characters
  vector<int> adj[26 * 26]; // Adjacency list for character pairs
  for (int i = 1; i < n; i++) {
    int a = s[i - 1] - 'a'; // Convert character to index (0-25)
    int b = s[i] - 'a';
    int k = a * 26 + b; // Unique identifier for adjacent character pair
    par[i] = k;
    adj[k].push_back(i); // Store position of character pair
  }
  int m;
  cin >> m;
  vector<pii> query(m);
  vector<int> ans(m);
  for (int i = 0; i < m; i++) {
    int f, t;
    cin >> f >> t;
    query[i] = {f, t};
    ans[i] = abs(t - f); // Initial guess as direct distance (without teleportation)
  }
  for (int i = 0; i < K; i++) {
    if (!adj[i].size()) continue;
    fill(dist, dist + N + K, INF); // Reset distances for BFS
    int d = 0;
    vector<int> cur, nxt;
    auto prop = [&](int alt, int v) {
      if (alt < dist[v]) {
        dist[v] = alt;
        (alt == d ? cur : nxt).push_back(v); // Add to current or next level based on distance
      }
    };
    dist[N + i] = 0; // Initialize BFS from the character pair
    nxt.push_back(N + i);
    while (nxt.size()) {
      swap(cur, nxt);
      while (cur.size()) {
        int u = cur.back();
        cur.pop_back();
        if (u < N) {
          // u is a string position, process left/right moves and teleportation
          if (u > 1)
            prop(d + 1, u - 1);
          if (u < n - 1)
            prop(d + 1, u + 1);
          prop(d, par[u] + N); // Jump to character pair nodes
        } else {
          // u is a character pair node, move to all positions with that pair
          for (int v : adj[u - N])
            prop(d + 1, v);
        }
      }
      d++;
    }
    for (int i = 0; i < m; i++) {
      auto [f, t] = query[i];
      ans[i] = min(ans[i], dist[f] + dist[t] - 1); // Combine distances from both positions
    }
  }
  for (int i = 0; i < m; i++) {
    cout << ans[i] << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/