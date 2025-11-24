// Problem: CF 1901 E - Compressed Tree
// https://codeforces.com/contest/1901/problem/E

/*
 * Problem: E. Compressed Tree
 * Algorithm: Tree Dynamic Programming (DFS)
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * The problem involves maximizing the sum of node values after
 * performing operations on a tree:
 * 1. Remove leaf nodes (degree <= 1)
 * 2. Compress the tree by removing nodes with degree 2 and connecting their neighbors
 *
 * This solution uses DFS with dynamic programming on the tree:
 * f[u][1] = max sum starting from u, going down one edge
 * f[u][2] = max sum starting from u, going down two edges (u -> v -> w)
 * f[u][3] = max sum in subtree rooted at u that includes u as a middle node
 * 
 * Key insight: At each node, decide whether to include it, or use one of the
 * child paths (or combinations) to maximize the final result.
 */

#include <cstdio>
#include <algorithm>

const int rSiz = 1 << 21;
char rBuf[rSiz], *p1 = rBuf, *p2 = rBuf;
#define gc()                                                                   \
  (p1 == p2 && (p2 = (p1 = rBuf) + fread(rBuf, 1, rSiz, stdin), p1 == p2)      \
       ? EOF                                                                   \
       : *p1++)
template <class T> void rd(T &x) {
  char ch = gc();
  bool op = 0;
  for (; ch < '0' || ch > '9'; ch = gc())
    if (ch == '-')
      op = 1;
  for (x = 0; ch >= '0' && ch <= '9'; ch = gc())
    x = (x << 1) + (x << 3) + (ch ^ 48);
  if (op)
    x = -x;
}
#include <vector>

const int _ = 5e5 + 5;
int n, a[_];
std::vector<int> g[_];
long long f[_][4], ans;
void dfs(int u, int fa) {
  f[u][1] = f[u][2] = f[u][3] = -1e18;
  for (int v : g[u]) {
    if (v == fa)
      continue;
    dfs(v, u);
    long long val =
        std::max(0ll + a[v],
                 std::max(f[v][1] - a[v], std::max(f[v][2] + a[v], f[v][3])));
    f[u][3] = std::max(f[u][3], std::max(f[u][2] + val, f[u][3] + val));
    f[u][2] = std::max(f[u][2], f[u][1] + val);
    f[u][1] = std::max(f[u][1], val);
  }
  f[u][1] += a[u], f[u][3] += a[u];
  ans = std::max(
      ans, std::max(0ll + a[u], std::max(f[u][1], std::max(f[u][2], f[u][3]))));
}
void solve() {
  rd(n);
  for (int i = 1; i <= n; i++)
    rd(a[i]), g[i].clear();
  for (int i = 1, u, v; i < n; i++) {
    rd(u), rd(v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  ans = 0;
  dfs(1, 0);
  printf("%lld\n", ans);
}
int main() {
  int T;
  rd(T);
  for (; T; T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/