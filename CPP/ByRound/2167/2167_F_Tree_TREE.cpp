// Problem: CF 2167 F - Tree, TREE!!!
// https://codeforces.com/contest/2167/problem/F

/*
 * Problem: F. Tree, TREE!!!
 * Purpose: Calculate the kawaiiness of a tree, which is the sum of distinct LCA nodes
 *          over all possible root choices when selecting k distinct nodes.
 *
 * Algorithms/Techniques:
 * - Tree DFS traversal to compute subtree sizes
 * - For each edge, determine how many times that edge contributes to the total count
 * - Use inclusion-exclusion principle by subtracting invalid cases where subtree size < k
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the tree and auxiliary arrays
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
#define fst first
#define snd second
#define mp make_pair
#define debug(...) fprintf(stderr, __VA_ARGS__)
typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;
template <typename T> inline T squ(T x) { return x * x; }
template <typename T> inline bool chkmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}
template <typename T> inline bool chkmin(T &a, const T &b) {
  return a > b ? a = b, 1 : 0;
}
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
template <typename T> inline T read() {
  T sum = 0, fg = 1;
  char c = getchar();
  for (; !isdigit(c); c = getchar())
    if (c == '-')
      fg = -1;
  for (; isdigit(c); c = getchar())
    sum = (sum << 3) + (sum << 1) + (c ^ 0x30);
  return fg * sum;
}
const int maxn = 2e5 + 10;
int n, k, sz[maxn];
LL ans;
vector<int> g[maxn];

// DFS to calculate subtree sizes and update answer based on edge contributions
inline void dfs(int x, int f = 0) {
  sz[x] = 1;
  for (int y : g[x])
    if (y != f)
      dfs(y, x), sz[x] += sz[y];
  if (f) {
    // If current subtree size is less than k, it's not valid for selecting k nodes
    // So subtract contribution from both ends of the edge
    if (sz[x] < k)
      ans -= (n - sz[x]);
    if (n - sz[x] < k)
      ans -= sz[x];
  }
}

// Solve function for each test case
inline void solve() {
  n = read<int>(), k = read<int>();
  for (int i = 1; i <= n; i++)
    g[i].clear();
  for (int i = 1; i < n; i++) {
    int x = read<int>(), y = read<int>();
    g[x].push_back(y), g[y].push_back(x);
  }
  ans = squ(LL(n)); // Initialize with n * n (total number of node pairs)
  dfs(1);           // Start DFS from root node 1
  printf("%lld\n", ans);
}

int main() {
#ifdef xunzhen
  freopen("F.in", "r", stdin);
  freopen("F.out", "w", stdout);
#endif
  int T = read<int>();
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/