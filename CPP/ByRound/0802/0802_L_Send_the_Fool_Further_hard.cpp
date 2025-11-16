// Problem: CF 802 L - Send the Fool Further! (hard)
// https://codeforces.com/contest/802/problem/L

/*
 * Problem: L. Send the Fool Further! (hard)
 * Algorithms/Techniques: Tree DFS, Probability expectation, Modular arithmetic
 *
 * Time Complexity: O(n), where n is the number of nodes in the tree
 * Space Complexity: O(n), for storing the tree structure and auxiliary arrays
 *
 * Approach:
 * - Build an undirected tree from input edges.
 * - Use DFS to compute expected cost for each node.
 * - For each node, if it's a leaf, the expected cost is 0.
 * - For non-leaf nodes, compute the expected cost using the formula:
 *   E[X] = (sum of costs to neighbors) / (number of neighbors)
 * - Use modular inverse for division in modular arithmetic.
 * - Root the tree at node 1, and process all nodes in a bottom-up manner.
 *
 * Key Concepts:
 * - Expected value calculation using linearity of expectation.
 * - Modular multiplicative inverse to perform division in modular arithmetic.
 * - Tree DFS traversal to accumulate costs from children to parent.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define ll long long
#define ld long double
#define ull unsigned ll
#define db double
#define pint pair<int, int>
#define mk make_pair
#define pb push_back
#define eb emplace_back
#define ins insert
#define fi first
#define se second
#define Rep(x, y, z) for (int x = y; x <= z; x++)
#define Red(x, y, z) for (int x = y; x >= z; x--)
using namespace std;
const int Mod = 1e9 + 7, MAXN = 1e5 + 5;
char buf[1 << 12], *pp1 = buf, *pp2 = buf, nc;
int ny;
inline char gc() {
  return pp1 == pp2 &&
                 (pp2 = (pp1 = buf) + fread(buf, 1, 1 << 12, stdin), pp1 == pp2)
             ? EOF
             : *pp1++;
}
inline int read() {
  int x = 0;
  for (ny = 1; nc = gc(), (nc < 48 || nc > 57) && nc != EOF;)
    if (nc == 45)
      ny = -1;
  if (nc < 0)
    return nc;
  for (x = nc - 48; nc = gc(), 47 < nc && nc < 58 && nc != EOF;
       x = (x << 3) + (x << 1) + (nc ^ 48))
    ;
  return x * ny;
}
int n, sum[MAXN], k[MAXN], b[MAXN]; // sum: total edge cost for each node, k: number of children, b: expected cost
vector<int> G[MAXN]; // adjacency list for tree
inline int Fp(int x, int k) { // Fast power for modular inverse
  int ans = 1;
  for (; k; k >>= 1, x = 1ll * x * x % Mod)
    if (k & 1)
      ans = 1ll * ans * x % Mod;
  return ans;
}
inline void add(int &x, int y) { x += y, x >= Mod ? x -= Mod : 0; } // Modular addition
inline void sub(int &x, int y) { x -= y, x < 0 ? x += Mod : 0; } // Modular subtraction
void dfs(int x, int fa) {
  if (G[x].size() == 1) { // Leaf node, no further travel possible
    k[x] = 0, b[x] = 0;
    return;
  }
  k[x] = G[x].size(), b[x] = sum[x]; // k[x] = number of neighbors, b[x] = total cost to neighbors
  for (auto y : G[x])
    if (y != fa) // traverse children
      dfs(y, x), sub(k[x], k[y]), add(b[x], b[y]); // accumulate contributions from children
  k[x] = Fp(k[x], Mod - 2), b[x] = 1ll * b[x] * k[x] % Mod; // k[x] is now the modular inverse of number of neighbors, b[x] is expected cost
}
int main() {
  n = read();
  Rep(i, 1, n - 1) {
    int x = read() + 1, y = read() + 1, w = read(); // read and adjust node indices to 1-based
    G[x].pb(y), G[y].pb(x), add(sum[x], w), add(sum[y], w); // build adjacency list and accumulate sums
  }
  dfs(1, 0), cout << b[1] << '\n'; // start DFS from root 1
  return 0;
}


// https://github.com/VaHiX/CodeForces/