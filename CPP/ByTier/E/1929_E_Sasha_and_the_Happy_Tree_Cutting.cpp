// Problem: CF 1929 E - Sasha and the Happy Tree Cutting
// https://codeforces.com/contest/1929/problem/E

/*
Purpose: Solve the problem of finding the minimum number of edges to color in a tree such that for each of k given pairs of vertices, at least one edge on the simple path between them is colored.

Algorithm:
- Build an undirected tree from input edges.
- For each query pair (a_i, b_i), trace paths from a_i and b_i up to the root (1).
- Mark all nodes visited with a bitmask indicating which pairs they are involved in.
- Use bitmask DP to find minimum number of edges to cover all pairs.
- The approach uses DFS to traverse tree and bitmasks to track covered pairs efficiently.

Time Complexity: O(n + k * 2^k), where n is number of vertices and k is number of pairs.
Space Complexity: O(n + k * 2^k), for storing the tree structure and intermediate data.
*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <set>
#include <string>
#include <vector>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
namespace Fread {
const int SZ = 1 << 17;
char buf[SZ], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SZ, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SZ = 1 << 10;
char buf[SZ], *S = buf, *T = buf + SZ;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void putchar(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct NTR {
  ~NTR() { flush(); }
} ztr;
} // namespace Fwrite
#define getchar Fread ::getchar
#define putchar Fwrite ::putchar
namespace Fast {
struct Reader {
  template <typename T> Reader &operator>>(T &x) {
    char c = getchar();
    while (!isdigit(c))
      c = getchar();
    x = 0;
    while (isdigit(c))
      x = x * 10 + (c - '0'), c = getchar();
    return *this;
  }
} cin;
struct Writer {
  template <typename T> Writer &operator<<(T x) {
    static int sta[45];
    int top = 0;
    while (x) {
      sta[++top] = x % 10;
      x /= 10;
    }
    while (top) {
      putchar(sta[top] + '0');
      --top;
    }
    return *this;
  }
  Writer &operator<<(char c) {
    putchar(c);
    return *this;
  }
} cout;
} // namespace Fast
#define cin Fast ::cin
#define cout Fast ::cout
void solve() {
  int n, tt = 0;
  cin >> n;
  vector<int> pa(n + 1), f(n + 1), hd(n + 1), vr(2 * n), nx(2 * n);
  auto add = [&](int u, int v) {
    vr[++tt] = v;
    nx[tt] = hd[u];
    hd[u] = tt;
  };
  for (int i = 1, u, v; i < n; i++) {
    cin >> u >> v;
    add(u, v);
    add(v, u);
  }
  function<void(int, int)> fdp = [&](int c, int p) {
    pa[c] = p;
    for (int i = hd[c]; i; i = nx[i]) {
      int v = vr[i];
      if (v != p)
        fdp(v, c);
    }
  };
  fdp(1, 1);
  int k;
  cin >> k;
  for (int i = 0; i < k; i++) {
    int c, lca = 1;
    cin >> c;
    while (c > 1) {
      f[c] ^= 1 << i;
      c = pa[c];
    }
    cin >> c;
    while (c > 1) {
      if (f[c] & (1 << i) && lca == 1)
        lca = c;
      f[c] ^= 1 << i;
      c = pa[c];
    }
  }
  set<int> st;
  for (int x : f)
    if (x)
      st.insert(x);
  vector<basic_string<int>> a(k);
  for (int y : st)
    for (int len = 0; len < k; len++)
      if (y & (1 << len))
        a[len].push_back(y);
  int ans = min(k, n - 1);
  function<void(int, int)> dfs = [&](int cnt, int cf) {
    if (cnt >= ans)
      return;
    if (cf == (1 << k) - 1) {
      ans = min(ans, cnt);
      return;
    }
    int z = __builtin_ctz(~cf);
    for (int nxt : a[z])
      dfs(cnt + 1, cf | nxt);
  };
  dfs(0, 0);
  cout << ans << '\n';
}
int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/