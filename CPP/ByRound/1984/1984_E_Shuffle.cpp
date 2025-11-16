// Problem: CF 1984 E - Shuffle
// https://codeforces.com/contest/1984/problem/E

/*
 * Problem: E. Shuffle
 * 
 * Purpose: To find the maximum number of leaves possible in a tree after exactly one shuffle operation.
 * 
 * Approach:
 * - The shuffle process involves selecting a root node and recursively processing each subtree.
 * - A DFS is performed on each node that has degree > 1 to compute the maximum number of leaves achievable.
 * - The DP state tracks different configurations for sub-trees to determine optimal leaf count.
 * 
 * Time Complexity: O(n) per test case, where n is the number of nodes in the tree.
 * Space Complexity: O(n) for storing the tree structure and DP states.
 * 
 * Algorithms/Techniques: 
 *   - Tree DFS with Dynamic Programming
 *   - Degree-based traversal to identify suitable root candidates
 */
#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int MAXN = 2e5 + 10;
const int mod1 = 1e9 + 7;
const int mod2 = 998244353;
const int inf_int = 0x7f7f7f7f;
const long long inf_long = 0x7f7f7f7f7f7f7f7f;
const double eps = 1e-9;
char Buf[1 << 23], *P1 = Buf, *P2 = Buf;
#define getchar()                                                              \
  (P1 == P2 && (P2 = (P1 = Buf) + fread(Buf, 1, 1 << 23, stdin), P1 == P2)     \
       ? EOF                                                                   \
       : *P1++)
template <typename type> inline void read(type &x) {
  x = 0;
  bool f = false;
  char ch = getchar();
  while (ch < '0' || ch > '9')
    f |= ch == '-', ch = getchar();
  while (ch >= '0' && ch <= '9')
    x = x * 10 + (ch ^ 48), ch = getchar();
  if (f)
    x = -x;
}
template <typename type, typename... args>
inline void read(type &x, args &...y) {
  read(x), read(y...);
}
int t, n, k, head[MAXN], dp[MAXN][2][2], d[MAXN];
bool vis[MAXN];
struct node {
  int to, next;
} edge[MAXN << 1];
void build(int u, int v) {
  edge[++k].to = v;
  edge[k].next = head[u];
  head[u] = k;
}
void dfs(int u) {
  vis[u] = true;
  if (d[u] == 1)
    dp[u][0][1] = 0; // If leaf, no more children to contribute to dp
  dp[u][0][0] = 0;
  dp[u][1][0] = 1; // Root considered as a leaf if not connected to a child
  for (int i = head[u]; i; i = edge[i].next) {
    int v = edge[i].to;
    if (vis[v])
      continue;
    dfs(v);
    // Update dp values based on children's maximum leaves
    dp[u][0][1] = max(dp[u][0][0] + max(dp[v][0][1], dp[v][1][1]),
                      dp[u][0][1] + max(max(dp[v][0][0], dp[v][0][1]),
                                        max(dp[v][1][0], dp[v][1][1])));
    dp[u][0][0] += max(dp[v][0][0], dp[v][1][0]);
    dp[u][1][1] = max(dp[u][1][0] + dp[v][0][1],
                      dp[u][1][1] + max(dp[v][0][0], dp[v][0][1]));
    dp[u][1][0] += dp[v][0][0];
  }
}
signed main() {
  read(t);
  while (t--) {
    read(n);
    k = 0;
    for (int i = 1; i <= n; i++)
      head[i] = d[i] = 0;
    for (int i = 1; i < n; i++) {
      int u, v;
      read(u, v);
      build(u, v);
      build(v, u);
      d[u]++;
      d[v]++;
    }
    if (n == 2) {
      cout << 2 << '\n';
      continue;
    }
    for (int i = 1; i <= n; i++)
      vis[i] = false;
    for (int i = 1; i <= n; i++)
      dp[i][0][0] = dp[i][0][1] = dp[i][1][0] = dp[i][1][1] = -1e6;
    for (int i = 1; i <= n; i++) {
      if (d[i] > 1) { // Only process nodes with degree > 1
        dfs(i);
        // Compute maximum number of leaves for current root
        cout << max(max(dp[i][0][0], dp[i][0][1] + 1),
                    max(dp[i][1][0], dp[i][1][1] + 1))
             << '\n';
        break;
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/