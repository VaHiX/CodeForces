// Problem: CF 1161 B - Chladni Figure
// https://codeforces.com/contest/1161/problem/B

/*
B. Chladni Figure
Purpose: Determines if a set of line segments on a circular disc is rotationally symmetrical.
Techniques:
- Graph representation of segments.
- Rotational symmetry check using cyclic shifts and comparison.
Time Complexity: O(n * sqrt(n) + m * log(n))
Space Complexity: O(n^2)
*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<std::vector<long>> g(n); // Adjacency list storing relative distances
  for (long p = 0; p < m; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    --x;
    --y;
    // Store the distance from x to y in a cyclic manner (normalized)
    g[x].push_back((n + y - x) % n);
    g[y].push_back((n + x - y) % n);
  }
  // Sort distances for each node
  for (long p = 0; p < n; p++) {
    sort(g[p].begin(), g[p].end());
  }
  // Find all divisors of n
  std::vector<long> div;
  for (long p = 1; p < n; p++) {
    if (n % p == 0) {
      div.push_back(p);
    }
  }
  bool possible(false);
  // Check each possible symmetry rotation (divisor of n)
  for (long p = 0; (!possible) && (p < div.size()); p++) {
    long d = div[p];
    bool res(true);
    // For each node u, compare its adjacency list with (u + d) % n
    for (long u = 0; res && (u < n); u++) {
      if (g[u].size() != g[(u + d) % n].size()) {
        res = false;
        break;
      }
      for (long v = 0; v < g[u].size(); v++) {
        if ((g[u][v] != g[(u + d) % n][v])) {
          res = false;
          break;
        }
      }
    }
    if (res) {
      possible = true;
    }
  }
  puts(possible ? "Yes" : "No");
  return 0;
}


// https://github.com/VaHiX/codeForces/