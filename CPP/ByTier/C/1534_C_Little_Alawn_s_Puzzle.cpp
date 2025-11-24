// Problem: CF 1534 C - Little Alawn's Puzzle
// https://codeforces.com/contest/1534/problem/C

/*
C. Little Alawn's Puzzle
Purpose: Given a 2×n grid where each row is a permutation of numbers 1 to n,
         count the number of distinct solved configurations achievable by swapping
         elements within columns only.

Algorithms/Techniques:
- Graph traversal using DFS to find connected components
- Each connected component contributes a factor of 2 to the result (swap or not)
- Time Complexity: O(n) per test case, amortized across all test cases
- Space Complexity: O(n)

*/

#include <cstdio>
#include <vector>
#include <utility>

void dfs(long node, const std::vector<std::vector<long>> &g,
         std::vector<bool> &vis) {
  if (vis[node]) {
    return;
  }
  vis[node] = true;
  for (long p = 0; p < g[node].size(); p++) {
    dfs(g[node][p], g, vis);
  }
  return;
}

int main() {
  const long long MOD = 1e9 + 7;
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::pair<long, long>> v(n); // Store pairs of corresponding elements from rows
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p].first);
    }
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p].second);
    }
    std::vector<std::vector<long>> g(n + 1); // Build graph between elements
    for (long p = 0; p < n; p++) {
      g[v[p].first].push_back(v[p].second);
      g[v[p].second].push_back(v[p].first);
    }
    long long cnt(1);
    std::vector<bool> vis(n + 1, 0);
    for (long p = 1; p <= n; p++) {
      if (vis[p]) {
        continue;
      }
      dfs(p, g, vis); // Find connected component
      cnt *= 2;       // Each component contributes a factor of 2 (swap or not)
      cnt %= MOD;
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/