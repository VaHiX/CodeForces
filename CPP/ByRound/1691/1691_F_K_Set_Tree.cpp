// Problem: CF 1691 F - K-Set Tree
// https://codeforces.com/contest/1691/problem/F

/*
 * Problem: F. K-Set Tree
 * 
 * Purpose: Given a tree with n vertices and an integer k, compute the sum of f(r, S) 
 *          over all possible distinct combinations of vertex r and subset S of size k,
 *          where f(r, S) is the size of the smallest rooted subtree containing all vertices in S
 *          when the tree is rooted at r.
 *
 * Algorithms/Techniques:
 * - Tree Dynamic Programming (DFS-based)
 * - Combination precomputation using modular inverse
 * - Use of centroid decomposition idea to calculate contributions efficiently
 *
 * Time Complexity: O(n log n) due to combination calculations and DFS traversal
 * Space Complexity: O(n) for storing the tree and auxiliary arrays
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

#define int long long
using namespace std;
constexpr int N = 2e5 + 5, mod = 1e9 + 7;
int n, m, jc[N], nc[N], siz[N], ans;
vector<int> v[N];

// Fast exponentiation to compute modular inverse
int P(int x, int y) {
  int ans = 1;
  while (y) {
    if (y & 1)
      ans = ans * x % mod;
    x = x * x % mod, y >>= 1;
  }
  return ans;
}

// Compute combination C(x, y) using precomputed factorials and modular inverse
int C(int x, int y) {
  if (y > x)
    return 0;
  return jc[x] * nc[y] % mod * nc[x - y] % mod;
}

// DFS-based solution to calculate contribution of each node
void solve(int x, int f) {
  vector<int> a;
  siz[x] = 1;
  // Traverse children
  for (int i : v[x])
    if (i != f)
      solve(i, x), siz[x] += siz[i], a.push_back(siz[i]);
  
  // Add the size of the remaining part (the parent subtree)
  a.push_back(n - siz[x]);
  
  // Compute sum of C(size, m) for all subtrees including current node
  int S = 0;
  for (int i : a)
    S = (S + C(i, m)) % mod;
  
  // Add contribution of this node to the answer
  ans = (ans + n * ((C(n, m) - S) % mod + mod)) % mod;
  
  // Add contribution from each subtree to the answer
  for (int i : a)
    ans = (ans + ((C(n - i, m) - (S - C(i, m))) % mod + mod) % mod * i % mod *
                     (n - i)) %
          mod;
}

signed main() {
  scanf("%lld%lld", &n, &m);
  jc[0] = nc[0] = 1;
  
  // Precompute factorials and their modular inverses
  for (int i = 1; i <= n; i++)
    jc[i] = jc[i - 1] * i % mod, nc[i] = P(jc[i], mod - 2);
  
  // Read edges and build adjacency list
  for (int i = 1, x, y; i < n; i++)
    scanf("%lld%lld", &x, &y), v[x].push_back(y), v[y].push_back(x);
  
  // Start DFS from root (node 1)
  solve(1, 0);
  printf("%lld\n", ans);
}


// https://github.com/VaHiX/CodeForces/