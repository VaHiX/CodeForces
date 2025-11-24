// Problem: CF 1975 E - Chain Queries
// https://codeforces.com/contest/1975/problem/E

/*
Algorithm/Techniques: 
- Heavy-Light Decomposition (HLD) with Binary Indexed Tree (BIT) for efficient path queries and updates
- Tree traversal and tracking of black vertices to determine if they form a chain
- LCA (Lowest Common Ancestor) is computed using HLD
- Time and Space Complexity:
  Time: O((n + q) * log n) per test case
  Space: O(n) for the tree structure, BIT, and auxiliary arrays.
*/
#include <ctype.h>
#include <stdio.h>
#include <iterator>
#include <unordered_set>
#include <utility>

#define fw fwrite(obuf, p3 - obuf, 1, stdout)
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
#define putchar(x)                                                             \
  (p3 - obuf < 1 << 20 ? (*p3++ = (x)) : (fw, p3 = obuf, *p3++ = (x)))
#define Yes() putchar('Y'), putchar('e'), putchar('s'), putchar('\n')
#define No() putchar('N'), putchar('o'), putchar('\n')
using namespace std;
char buf[1 << 20], obuf[1 << 20], *p1 = buf, *p2 = buf, *p3 = obuf,
                                  str[20 << 2];
int read() {
  int x = 0;
  char ch = getchar();
  while (!isdigit(ch))
    ch = getchar();
  while (isdigit(ch))
    x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return x;
}
template <typename T> void write(T x, char sf = '\n') {
  if (x < 0)
    putchar('-'), x = ~x + 1;
  int top = 0;
  do
    str[top++] = x % 10, x /= 10;
  while (x);
  while (top)
    putchar(str[--top] + 48);
  if (sf ^ '#')
    putchar(sf);
}
constexpr int MAXN = 2e5 + 5;
int T, n, q, head[MAXN], tot;
bool c[MAXN];
struct {
  int v, to;
} e[MAXN << 1];
void addedge(int u, int v) {
  e[++tot] = {v, head[u]};
  head[u] = tot;
}
int dep[MAXN], fa[MAXN], siz[MAXN], son[MAXN];
int dfn[MAXN], top[MAXN], rnk[MAXN], dfncnt;
int bfa[MAXN];
void dfs(int u, int fno) {
  siz[u] = 1;
  dep[u] = dep[fa[u] = fno] + 1;
  for (int i = head[u], v; i; i = e[i].to) {
    if ((v = e[i].v) == fno)
      continue;
    dfs(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]])
      son[u] = v;
  }
}
void dfs2(int u, int t) {
  top[u] = t;
  dfn[u] = ++dfncnt;
  rnk[dfn[u]] = u;
  if (!son[u])
    return;
  dfs2(son[u], t);
  for (int i = head[u], v; i; i = e[i].to)
    if (!top[v = e[i].v] && v != son[u])
      dfs2(v, v);
}
int lca(int x, int y) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]])
      swap(x, y);
    x = fa[top[x]];
  }
  return dep[x] < dep[y] ? x : y;
}
int dis(int x, int y) { return dep[x] + dep[y] - (dep[lca(x, y)] << 1); }
struct BIT {
#define lowbit(x) (x & -x)
  int c[MAXN];
  void add(int x, int k) {
    for (; x <= n; x += lowbit(x))
      c[x] += k;
  }
  int sum(int x) {
    int res = 0;
    for (; x; x -= lowbit(x))
      res += c[x];
    return res;
  }
  int sum(int l, int r) { return sum(r) - sum(l - 1); }
} B;
int qsum(int x, int y) {
  int res = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]])
      swap(x, y);
    res += B.sum(dfn[top[x]], dfn[x]);
    x = fa[top[x]];
  }
  if (dfn[x] > dfn[y])
    swap(x, y);
  res += B.sum(dfn[x], dfn[y]);
  return res;
}
void clear() {
  for (int i = 1; i <= n; ++i) {
    head[i] = son[i] = top[i] = B.c[i] = 0;
    bfa[i] = 0;
  }
  dfncnt = tot = 0;
}
int main() {
  T = read();
  while (T--) {
    n = read(), q = read();
    clear();
    for (int i = 1; i <= n; ++i)
      c[i] = read();
    for (int i = 1, u, v; i < n; ++i) {
      u = read(), v = read();
      addedge(u, v), addedge(v, u);
    }
    dfs(1, 0);
    dfs2(1, 1);
    int bcnt = 0;
    for (int i = 1; i <= n; ++i) {
      if (!c[i])
        continue;
      B.add(dfn[i], 1);
      ++bfa[fa[i]];
      ++bcnt;
    }
    unordered_set<int> st;
    for (int i = 1; i <= n; ++i)
      if (!bfa[i] && c[i])
        st.emplace(i);
    while (q--) {
      int u = read();
      if (!c[u]) {
        ++bfa[fa[u]];
        ++bcnt;
        B.add(dfn[u], 1);
        c[u] = 1;
        if (bfa[fa[u]] == 1 && c[fa[u]])
          st.erase(fa[u]);
        if (!bfa[u])
          st.emplace(u);
      } else {
        --bfa[fa[u]];
        --bcnt;
        B.add(dfn[u], -1);
        c[u] = 0;
        if (!bfa[fa[u]] && c[fa[u]])
          st.emplace(fa[u]);
        if (!bfa[u])
          st.erase(u);
      }
      switch (st.size()) {
      case 1:
        Yes();
        break;
      case 2: {
        int x = *st.begin(), y = *next(st.begin());
        int t = qsum(x, y);
        if (t == dis(x, y) + 1 && t == bcnt)
          Yes();
        else
          No();
        break;
      }
      default:
        No();
        break;
      }
    }
  }
  return fw, 0;
}


// https://github.com/VaHiX/CodeForces/