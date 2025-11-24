// Problem: CF 1957 F2 - Frequency Mismatch (Hard Version)
// https://codeforces.com/contest/1957/problem/F2

/*
 * Problem: F2. Frequency Mismatch (Hard Version)
 * Purpose: For each query, find values that appear different numbers of times in two paths in a tree.
 * Algorithm:
 *   - Build a tree with DFS traversal and use a persistent segment tree to store frequency counts.
 *   - Use binary lifting to compute LCA efficiently.
 *   - For each query, compare the frequency multisets of two paths using persistent segment trees.
 * 
 * Time Complexity:
 *   - Preprocessing: O(n log n) for LCA and DFS traversal.
 *   - Query processing: O(log^2 m) per query, where m is the maximum value (up to 10^5).
 *   - Overall: O(n log n + q log^2 m)
 * 
 * Space Complexity:
 *   - O(n log n) for the persistent segment trees and LCA tables.
 */

#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <random>
#include <utility>
#include <vector>

using namespace std;
namespace qGet {
const int SZ = 1 << 18;
char buf[SZ], *S, *T;
inline char gc() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SZ, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
struct Reader {
  template <typename T> Reader &operator>>(T &x) {
    char c = gc();
    while (!isdigit(c))
      c = gc();
    x = 0;
    while (isdigit(c))
      x = x * 10 + (c - '0'), c = gc();
    return *this;
  }
} cin;
} // namespace qGet
namespace qPut {
const int SZ = 1 << 19;
char buf[SZ], *S = buf, *T = buf + SZ;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void pc(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct NTR {
  ~NTR() { flush(); }
} ztr;
struct Writer {
  template <typename T> Writer &operator<<(T x) {
    if (x == 0) {
      pc('0');
      return *this;
    }
    static int sta[45];
    int top = 0;
    while (x) {
      sta[++top] = x % 10;
      x /= 10;
    }
    while (top) {
      pc(sta[top] + '0');
      --top;
    }
    return *this;
  }
  Writer &operator<<(char c) {
    pc(c);
    return *this;
  }
} cout;
} // namespace qPut
#define cin qGet ::cin
#define cout qPut ::cout
#define rsz resize
#define mi (l + r) / 2
#define pb push_back
#define fore(i, a, b) for (int i = a; i <= b; i++)
mt19937 mt(time(0));
int n, tt, k, tc, dc, m = 1e5;
vector<unsigned> bas, tr;
vector<int> a, hd, to, nx, rt, pa, dfn, L, R, ans, st[18];
inline void adde(int x, int y) {
  to[++tt] = y;
  nx[tt] = hd[x];
  hd[x] = tt;
}
void add(int &u, int l, int r, int val) {
  int v = ++tc;
  L[v] = L[u], R[v] = R[u], tr[v] = tr[u] + bas[val];
  u = v;
  if (l == r)
    return;
  if (val <= mi)
    add(L[u], l, mi, val);
  else
    add(R[u], mi + 1, r, val);
}
void dfs(int u) {
  add(rt[u] = rt[pa[u]], 1, m, a[u]);
  st[0][dfn[u] = ++dc] = pa[u];
  for (int e = hd[u]; e; e = nx[e]) {
    int v = to[e];
    if (v == pa[u])
      continue;
    pa[v] = u;
    dfs(v);
  }
}
void query(int w, int x, int y, int z, int g, int h, int i, int j, int l,
           int r) {
  if (tr[w] + tr[x] + tr[i] + tr[j] == tr[g] + tr[h] + tr[y] + tr[z])
    return;
  if (l == r) {
    ans.pb(r);
    return;
  }
  query(L[w], L[x], L[y], L[z], L[g], L[h], L[i], L[j], l, mi);
  if (ans.size() == k)
    return;
  query(R[w], R[x], R[y], R[z], R[g], R[h], R[i], R[j], mi + 1, r);
}
int main() {
  cin >> n;
  int mx = 18 * n + 1;
  bas.rsz(m + 1);
  bas[0] = 1;
  fore(i, 1, m) bas[i] = mt();
  a.rsz(n + 1);
  dfn = pa = rt = hd = a;
  to.rsz(2 * n);
  nx = to;
  fore(i, 1, n) cin >> a[i];
  fore(i, 1, n - 1) {
    int u, v;
    cin >> u >> v;
    adde(u, v);
    adde(v, u);
  }
  L.rsz(mx);
  R = L;
  tr.rsz(mx);
  fore(i, 0, 17) st[i].rsz(n + 1);
  dfs(1);
  auto tmin = [&](int u, int v) { return dfn[u] < dfn[v] ? u : v; };
  for (int x = 1; (1 << x) <= n; x++)
    for (int y = 1; y + (1 << x) - 1 <= n; y++)
      st[x][y] = tmin(st[x - 1][y], st[x - 1][y + (1 << x - 1)]);
  auto lca = [&](int u, int v) {
    if (u == v)
      return u;
    u = dfn[u], v = dfn[v];
    if (u > v)
      swap(u, v);
    int k = __lg(v - u);
    return tmin(st[k][u + 1], st[k][v - (1 << k) + 1]);
  };
  int q;
  cin >> q;
  while (q--) {
    int u, v, x, y;
    cin >> u >> v >> x >> y >> k;
    int l1 = lca(u, v), l2 = lca(x, y);
    ans.clear();
    ans.reserve(k);
    query(rt[u], rt[v], rt[l1], rt[pa[l1]], rt[x], rt[y], rt[l2], rt[pa[l2]], 1,
          m);
    cout << ans.size() << ' ';
    for (auto q : ans)
      cout << q << ' ';
    cout << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/