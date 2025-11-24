// Problem: CF 1740 G - Dangerous Laser Power
// https://codeforces.com/contest/1740/problem/G

/*
 * Problem: G. Dangerous Laser Power
 *
 * Purpose:
 * This code solves the problem of assigning types (0 or 1) to portals in a grid
 * such that the number of "good" portals is maximized. A portal is good if
 * the total energy consumed by it modulo 2 equals its type setting.
 *
 * Approach:
 * - Use Union-Find (Disjoint Set Union) data structure to manage connectivity
 *   of laser paths through portals
 * - Process portals in increasing order of strength to determine optimal type settings
 * - For each portal, compute the XOR of all energies consumed by entering lasers
 *   from different faces, and assign type based on this value
 * - The key insight is to maintain the parity of consumed energy for each portal
 *   and use union-find to propagate type decisions along laser paths
 *
 * Time Complexity: O(nm log(nm) + nm alpha(nm)) where alpha is the inverse Ackermann function
 * Space Complexity: O(nm)
 */

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

int n, m, s[2001][2001], t[2001][2001];
int f[5000001], cnt[5000001], g[5000001];

// Union-Find find operation with path compression
int find(int x) { return f[x] ? f[x] = find(f[x]) : x; }

// Union-Find merge operation
void merge(int u, int v) {
  u = find(u), v = find(v);
  if (u != v) {
    f[u] = v;
    cnt[v] += cnt[u];
    g[v] ^= g[u];
  }
}

// Hash function to uniquely map (k, i, j) to an index
int hash(int k, int i, int j) {
  return k * (n + 2) * (m + 2) + i * (m + 2) + j;
}

// Vector to store portals sorted by strength
std::vector<std::pair<int, std::pair<int, int>>> vec;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &s[i][j]);
      vec.push_back(std::make_pair(s[i][j], std::make_pair(i, j)));
      // Initialize cnt and g for all 4 faces of this portal
      for (int k = 0; k < 4; ++k)
        cnt[hash(k, i, j)] = 1, g[hash(k, i, j)] = 1;
    }
  // Sort portals by strength
  std::sort(vec.begin(), vec.end());
  for (auto v : vec) {
    int x = v.second.first, y = v.second.second;
    int total = 0;
    // Compute total energy consumption for this portal based on all entering lasers
    for (int k = 0; k < 4; ++k)
      total ^= g[hash(k, x, y)] ^ ((1ll * cnt[hash(k, x, y)] * s[x][y]) & 1);
    // Assign the type to this portal
    t[x][y] = total;
    for (int k = 0; k < 4; ++k) {
      int T = (k + 2 + total) % 4; // Determine which face this laser exits through
      g[hash(k, x, y)] = ((1ll * cnt[hash(k, x, y)] * s[x][y]) & 1); // Update energy parity
      // Merge with neighbor based on exit face
      if (T == 0)
        merge(hash(k, x, y), hash(2, x - 1, y));
      if (T == 1)
        merge(hash(k, x, y), hash(3, x, y + 1));
      if (T == 2)
        merge(hash(k, x, y), hash(0, x + 1, y));
      if (T == 3)
        merge(hash(k, x, y), hash(1, x, y - 1));
    }
  }
  // Print the result
  for (int i = 1; i <= n; ++i, putchar('\n'))
    for (int j = 1; j <= m; ++j)
      printf("%d", t[i][j]);
}


// https://github.com/VaHiX/CodeForces/