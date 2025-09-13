/*
 * Problem URL : https://codeforces.com/problemset/problem/2104/G
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
#define mk make_pair
#define For(i, il, ir) for (int i = (il); i <= (ir); ++i)
#define Rof(i, ir, il) for (int i = (ir); i >= (il); --i)
using namespace std;
typedef pair<int, int> pii;
const int maxn = 2e5 + 10;

int n, Q;
int k[maxn];
int pa[maxn], pt[maxn];

#define mid (l + r >> 1)
pii opz;
int opx, opy;
vector<pii> tr[maxn << 2];
void update(int o, int l, int r) {
  if (opx <= l && r <= opy) {
    tr[o].push_back(opz);
    return;
  }
  if (opx <= mid)
    update(o << 1, l, mid);
  if (opy > mid)
    update(o << 1 | 1, mid + 1, r);
}
void update(int l, int r, pii v) {
  opx = l, opy = r, opz = v;
  update(1, 0, Q);
}

int tp, ans;
pii st[maxn];
int fa[maxn], val[maxn], h[maxn];

int fd(int x, int &v) {
  v = 0;
  while (x ^ fa[x])
    v ^= val[x], x = fa[x];
  return x;
}
void merge(int x, int y) {
  int vx, vy;
  x = fd(x, vx), y = fd(y, vy);
  if (x == y)
    ans ^= vx ^ vy;
  else {
    if (h[x] > h[y])
      swap(x, y);
    st[++tp] = make_pair(x, h[x] == h[y]);
    fa[x] = y, val[x] = vx ^ vy ^ 1, h[y] += (h[x] == h[y]);
  }
}
void undo(int tar) {
  while (tp > tar) {
    int x = st[tp].first, d = st[tp].second;
    h[fa[x]] -= d, fa[x] = x, val[x] = 0, tp--;
  }
}

int res[maxn];
void dfs(int o, int l, int r) {
  int pretp = tp, preans = ans;
  for (pii c : tr[o])
    merge(c.first, c.second);
  if (l == r)
    res[l] = ans;
  else
    dfs(o << 1, l, mid), dfs(o << 1 | 1, mid + 1, r);
  undo(pretp);
  ans = preans;
}
signed main() {
  scanf("%d%d", &n, &Q);
  For(i, 1, n) scanf("%d", &pa[i]), fa[i] = i, h[i] = 1;
  For(i, 1, Q) {
    int x, y;
    scanf("%d%d%d", &x, &y, &k[i]);
    update(pt[x], i - 1, mk(x, pa[x]));
    pa[x] = y, pt[x] = i;
  }
  For(i, 1, n) update(pt[i], Q, mk(i, pa[i]));

  ans = n & 1;
  dfs(1, 0, Q);
  For(i, 1, Q) printf("%d\n", k[i] % 3 ? (res[i] ? k[i] % 3 : 1) : 0);
  return 0;
}