// Problem: CF 1740 H - MEX Tree Manipulation
// https://codeforces.com/contest/1740/problem/H

/*
 * Problem: H. MEX Tree Manipulation
 * 
 * Algorithm: Heavy-Light Decomposition (HLD) + Segment Tree with Lazy Propagation
 * 
 * Time Complexity: O(q * log^2(q)) where q is the number of queries
 * Space Complexity: O(q * log(q)) for segment tree and auxiliary arrays
 * 
 * Approach:
 * - For each node, we maintain a structure to track MEX of children values.
 * - Heavy-Light Decomposition is used to efficiently update and query the tree.
 * - A segment tree is used to store information about MEX values for each path in the HLD.
 * - Each vertex's value is updated based on the MEX of its children.
 * - Sum of all vertex values is maintained and reported after each insertion.
 */

#include <cstdio>
#include <cstring>
const int maxq = 3e5 + 10;
struct E {
  int to;
  int nxt;
} ed[maxq];
int head[maxq];
int tot;
void J(int a, int b) {
  ed[++tot].to = b;
  ed[tot].nxt = head[a];
  head[a] = tot;
}
struct T {
  int x;
  int b1, b2;
  int ans1, ans2;
  int getans(int val) const { return val == x ? ans1 : ans2; }
  int getnxt(int val) const { return val == x ? b1 : b2; }
  friend T operator+(const T &a, const T &b) {
    T tmp;
    tmp.x = a.x;
    tmp.b1 = b.getnxt(a.b1);
    tmp.b2 = b.getnxt(a.b2);
    tmp.ans1 = a.ans1 + b.getans(a.b1);
    tmp.ans2 = a.ans2 + b.getans(a.b2);
    return tmp;
  }
} tr[maxq * 4];
T Search(int x, int sl, int sr, int l, int r) {
  if (sl <= l && sr >= r)
    return tr[x];
  int mid = (l + r) / 2;
  if (sl <= mid && sr > mid)
    return Search(x * 2 + 1, sl, sr, mid + 1, r) +
           Search(x * 2, sl, sr, l, mid);
  if (sl <= mid)
    return Search(x * 2, sl, sr, l, mid);
  return Search(x * 2 + 1, sl, sr, mid + 1, r);
}
void Modify(int x, int pst, T val, int l, int r) {
  if (l == r) {
    tr[x] = val;
    return;
  }
  int mid = (l + r) / 2;
  if (pst <= mid)
    Modify(x * 2, pst, val, l, mid);
  else
    Modify(x * 2 + 1, pst, val, mid + 1, r);
  tr[x] = tr[x * 2 + 1] + tr[x * 2];
}
int son[maxq];
int sz[maxq];
int top[maxq];
int d[maxq];
int dfn[maxq];
int f[maxq];
void Dfs1(int x, int fa) {
  sz[x] = 1;
  for (int i = head[x]; i; i = ed[i].nxt) {
    Dfs1(ed[i].to, x);
    sz[x] += sz[ed[i].to];
    if (!son[x] || sz[ed[i].to] > sz[son[x]])
      son[x] = ed[i].to;
  }
}
int cnt;
void Dfs2(int x, int s) {
  dfn[x] = ++cnt;
  top[x] = s;
  if (son[x])
    Dfs2(son[x], s);
  for (int i = head[x]; i; i = ed[i].nxt) {
    if (ed[i].to == son[x])
      continue;
    Dfs2(ed[i].to, ed[i].to);
  }
}
int ha[maxq][30];
int ans;
T get(int p[]) {
  T tmp;
  int bj = 0;
  for (int i = 0; i <= 29; i++) {
    if (!p[i]) {
      if (bj) {
        tmp.ans1 = tmp.b1 = i;
        break;
      }
      tmp.ans2 = tmp.x = tmp.b2 = i;
      bj = 1;
    }
  }
  return tmp;
}
int q;
int All(int x) {
  int ans = 0;
  while (x) {
    if (x == d[top[x]])
      ans += Search(1, dfn[top[x]], dfn[x], 1, q + 1).ans2;
    else
      ans += Search(1, dfn[top[x]], dfn[x], 1, q + 1)
                 .getans(Search(1, dfn[x] + 1, dfn[d[top[x]]], 1, q + 1).b2);
    x = f[top[x]];
  }
  return ans;
}
int gx[maxq];
void Modify(int x) {
  int t = f[x];
  ans -= All(t);
  d[top[x]] = x;
  Modify(1, dfn[x], get(ha[x]), 1, q + 1);
  while (f[top[x]]) {
    x = top[x];
    int tmp = Search(1, dfn[x], dfn[d[x]], 1, q + 1).b2;
    if (gx[x] != -1)
      ha[f[x]][gx[x]]--;
    ha[f[x]][gx[x] = tmp]++;
    Modify(1, dfn[f[x]], get(ha[f[x]]), 1, q + 1);
    x = f[x];
  }
  ans += All(t);
}
int main() {
  memset(gx, -1, sizeof(gx));
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    scanf("%d", &f[i + 1]);
    J(f[i + 1], i + 1);
  }
  Dfs1(1, 0);
  Dfs2(1, 1);
  d[1] = 1;
  Modify(1, dfn[1], get(ha[1]), 1, 1 + q);
  for (int i = 1; i <= q; i++) {
    Modify(i + 1);
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/