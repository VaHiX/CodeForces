// Problem: CF 1930 G - Prefix Max Set Counting
// https://codeforces.com/contest/1930/problem/G

/*
 * Problem: G. Prefix Max Set Counting
 * 
 * Purpose: This code counts the number of distinct values of f(a) over all possible pre-orders of a tree,
 *          where f(a) is the array of prefix maxima of a permutation a.
 * 
 * Algorithm:
 *   - Uses DFS traversal to compute tree properties including ancestors, prefix maxima, and depth-first numbers
 *   - Implements binary lifting for efficient ancestor queries
 *   - Uses a Binary Indexed Tree (BIT) to efficiently update and query prefix sums
 *   - Dynamic programming with the BIT to count the number of valid configurations
 * 
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 * 
 * Techniques Used:
 *   - Binary Lifting
 *   - DFS Tree Traversal
 *   - Binary Indexed Tree (BIT)
 *   - Dynamic Programming
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

#define fi first
#define se second
#define pb push_back
using namespace std;
using ll = long long;
const int N = 1000010, mod = 998244353, SZ = (1 << 18) + 5;
static char buf[SZ], *bgn = buf, *til = buf;
char getc() {
  if (bgn == til)
    bgn = buf, til = buf + fread(buf, 1, SZ, stdin);
  return bgn == til ? EOF : *bgn++;
}
template <typename T> void read(T &x) {
  char ch = getc();
  T fh = 0;
  x = 0;
  while (ch < '0' || ch > '9')
    fh |= (ch == '-'), ch = getc();
  while (ch >= '0' && ch <= '9')
    x = x * 10 + ch - '0', ch = getc();
  x = fh ? -x : x;
}
template <typename Type, typename... argc> void read(Type &x, argc &...args) {
  read(x), read(args...);
}
template <typename T> void print(T x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x / 10)
    print(x / 10);
  putchar(x % 10 + '0');
}
int n, u, v, mx[N], pre[N], dfn[N], cnt, mxdfn[N], f[N], g[N], ff[20][N];
vector<int> edge[N];
void Add(int &a, int b) {
  a += b;
  a = a >= mod ? a - mod : a;
}
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
struct BIT {
  int sum[N];
  void modify(int x, int val) {
    for (; x <= n; x += x & (-x))
      Add(sum[x], val);
  }
  void upd(int l, int r, int val) { modify(l, val), modify(r + 1, mod - val); }
  int ask(int x) {
    int res = 0;
    for (; x; x -= x & (-x))
      Add(res, sum[x]);
    return res;
  }
} bit;
void dfs(int x, int fa) {
  ff[0][x] = fa, mx[x] = x, dfn[x] = ++cnt,
  pre[x] = fa > pre[fa] ? fa : pre[fa];
  for (int y : edge[x])
    if (y != fa)
      dfs(y, x), mx[x] = max(mx[x], mx[y]);
  mxdfn[x] = cnt;
}
int jump(int x) {
  int tmp = x;
  if (mx[x] > tmp)
    return x;
  for (int i = 19; i >= 0; --i)
    if (ff[i][x] && mx[ff[i][x]] <= tmp)
      x = ff[i][x];
  return x == 1 ? x : ff[0][x];
}
void clear() {
  cnt = 0;
  for (int i = 1; i <= n; ++i)
    edge[i].clear(), f[i] = g[i] = pre[i] = mx[i] = bit.sum[i] = 0;
}
void mian() {
  read(n), clear();
  for (int i = 1; i < n; ++i)
    read(u, v), edge[u].pb(v), edge[v].pb(u);
  dfs(1, 0);
  for (int j = 1; j <= 19; ++j)
    for (int i = 1; i <= n; ++i)
      ff[j][i] = ff[j - 1][ff[j - 1][i]];
  f[1] = 1;
  for (int i = 1; i <= n; ++i) {
    if (pre[i] > i)
      continue;
    if (i != 1)
      g[i] = bit.ask(dfn[i]), f[i] = add(g[i], mod - g[pre[i]]);
    int x = jump(i);
    bit.upd(dfn[x], mxdfn[x], f[i]);
  }
  print(f[n]), putchar('\n');
}
int main() {
#ifdef Kelly
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  freopen("err.txt", "w", stderr);
#endif
  int T = 1;
  read(T);
  while (T--)
    mian();
  return 0;
}


// https://github.com/VaHiX/CodeForces/