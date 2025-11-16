// Problem: CF 1799 H - Tree Cutting
// https://codeforces.com/contest/1799/problem/H

/*
Algorithm/Technique: Dynamic Programming on Trees, Bitmask DP, DFS
Time Complexity: O(n * 2^k * k), where n is the number of nodes and k is the number of operations.
Space Complexity: O(n * 2^k), for memoization and DP tables.

This code solves the problem of counting the number of ways to perform k operations on a tree such that 
the sizes of remaining components match given sequence a[0], a[1], ..., a[k]. Each operation involves:
1. Choosing an edge and removing it.
2. Deleting one of the two resulting components.
3. Writing the number of vertices in the remaining component.

The algorithm uses a tree DP approach where for each node, we maintain a DP table f[x][mask] representing the 
number of ways to get a certain configuration of component sizes using the subtree rooted at x.
*/

#include <algorithm>
#include <iostream>
#include <vector>

#define int long long
using namespace std;
const int mod = 998244353, M = 128, N = 5005;
int n, k, u, vv, lim, a[M], b[M], f[N][M], f1[M], siz[N];
vector<int> v[N];
int lw(int x) { return x & (-x); }

// Depth-first search to compute DP values for each subtree
void dfs(int x, int fa) {
  f[x][0] = siz[x] = 1; // Base case: leaf node contributes 1 to count and size 1
  for (auto dq : v[x])
    if (dq != fa) {
      dfs(dq, x), siz[x] += siz[dq]; // Recursively compute dp for child
      // Copy current DP values to f1 for combination
      for (int i = 0; i <= lim; i++)
        f1[i] = f[x][i], f[x][i] = 0;
      // Combine values from current node and child node using bitmask DP
      for (int i = 0; i < (1 << k); i++)
        for (int j = i;; j = i & (j - 1)) {
          f[x][i] = (f[x][i] + f1[j] * f[dq][i - j]) % mod;
          if (!j)
            break;
        }
      // Handle cases where both components need to be considered
      for (int i = (1 << k); i < lim; i++)
        for (int j = (lim ^ i), k = (j -= (1 << __lg(j)));; k = (j & (k - 1))) {
          f[x][i + k] =
              (f[x][i + k] + f1[i] * f[dq][k] + f1[k] * f[dq][i]) % mod;
          if (!k)
            break;
        }
    }
  // Update DP values based on size of current subtree
  for (int i = 0; i <= lim; i++)
    f1[i] = f[x][i];
  for (int i = 1; i <= lim; i++)
    if (siz[x] == b[i])
      f[x][i] = (f[x][i] + f1[i - (1 << __lg(i))]) % mod;
  for (int i = (1 << k); i < lim; i++) {
    int dq = i + (1 << __lg(i ^ lim));
    if (siz[x] == b[dq])
      f[x][dq] = (f[x][dq] + f1[i]) % mod;
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin >> n, a[0] = n; // Read number of nodes and initial size
  for (int i = 1; i < n; i++)
    cin >> u >> vv, v[u].push_back(vv), v[vv].push_back(u); // Read edges
  cin >> k, lim = (1 << (k + 1)) - 1; // Calculate limit for mask
  for (int i = 1; i <= k; i++)
    cin >> a[i], a[i - 1] -= a[i]; // Compute differences to build b array
  for (int i = 1; i <= lim; i++)
    b[i] = b[i - lw(i)] + a[__lg(lw(i))]; // Precompute bit counts for efficiency
  dfs(1, 0), cout << f[1][lim]; // Run DFS from root and output result
  return 0;
}


// https://github.com/VaHiX/CodeForces/