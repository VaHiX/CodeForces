/*
 * Problem URL : https://codeforces.com/contest/2006/problem/E
 * Submit Date : 2025-09-13
 */

/*
2024-08-31
q409257934
*/
#include<bits/stdc++.h>
using namespace std;

struct SegTree
{
  vector<int> gmin, lazy;
  void pulldown(int rt) {
    if (lazy[rt]) {
      lazy[rt << 1] += lazy[rt];
      gmin[rt << 1] += lazy[rt];
      lazy[rt << 1 | 1] += lazy[rt];
      gmin[rt << 1 | 1] += lazy[rt];
      lazy[rt] = 0;
    }
  }
  void pullup(int rt) {
    gmin[rt] = min(gmin[rt << 1], gmin[rt << 1 | 1]);
  }
  void build(int rt, int l, int r) {
    if (l == r) {
      if (gmin.size() <= rt) {
        gmin.resize(rt + 1);
        lazy.resize(rt + 1);
      }
      gmin[rt] = 1e9;
      return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1 | 1, mid + 1, r);
    build(rt << 1, l, mid);
    pullup(rt);
  }
  void update(int rt, int l, int r, int x, int y) {
    if (l == r) {
      gmin[rt] = y;
      return;
    }
    pulldown(rt);
    int mid = (l + r) >> 1;
    if (mid >= x) {
      update(rt << 1, l, mid, x, y);
    } else {
      update(rt << 1 | 1, mid + 1, r, x, y);
    }
    pullup(rt);
  }
  void add(int rt, int l, int r, int al, int ar, int av) {
    if (al <= l && r <= ar) {
      lazy[rt] += av;
      gmin[rt] += av;
      return;
    }
    pulldown(rt);
    int mid = (l + r) >> 1;
    if (al <= mid) add(rt << 1, l, mid, al, ar, av);
    if (ar > mid) add(rt << 1 | 1, mid + 1, r, al, ar, av);
    pullup(rt);
  }
  int query(int rt, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return gmin[rt];
    }
    pulldown(rt);
    int mid = (l + r) >> 1;
    int rs = 1e9;
    if (ql <= mid) rs = min(rs, query(rt << 1, l, mid, ql, qr));
    if (qr > mid) rs = min(rs, query(rt << 1 | 1, mid + 1, r, ql, qr));
    return rs;
  }
};


void solve() {
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  vector<int> p(n);
  for (int i = 1; i < n; ++i) {
    cin >> p[i];
    --p[i];
    g[p[i]].push_back(i);
  }
  int dfsnb = 0;
  vector<int> dfsl(n), dfsr(n), d2i(n), dep(n);
  dep[0] = -1;
  auto dfs = [&](auto &self, int x) ->void {
    d2i[dfsnb] = x;
    dep[dfsnb] = dep[dfsl[p[x]]] + 1;
    dfsl[x] = dfsnb++;
    for (const auto &e : g[x]) {
      self(self, e);
    }
    dfsr[x] = dfsnb;
  };
  dfs(dfs, 0);
  SegTree seg;
  seg.build(1, 0, n - 1);
  seg.update(1, 0, n - 1, 0, 0);
  vector<int> ds(n);
  cout << "1 ";
  for (int i = 1, ct = 0, ct2 = 0, gmx = 0, ok = 1; i < n; ++i) {
    int x = dfsl[i], px = dfsl[p[i]];
    if (++ds[i] > 3 || ++ds[p[i]] > 3) {
      ok = 0;
    }
    if (!ok) {
      cout << "-1" << " \n"[i == n - 1];
      continue;
    }
    int len = seg.query(1, 0, n - 1, px, px);
    if (ds[p[i]] == 3) {
      seg.update(1, 0, n - 1, px, 1e9);
    }
    seg.update(1, 0, n - 1, x, len + 1);
    if (gmx < len + 1) {
      gmx = len + 1;
      if (ct == ct2) {
        ct2 = p[ct];
        for (const auto &e : g[ct]) {
          if (dfsl[e] <= x && x < dfsr[e]) {
            ct2 = e;
          }
        }
        if (ct > ct2) {
          seg.add(1, 0, n - 1, dfsl[ct], dfsr[ct] - 1, 1);
          swap(ct, ct2);
        } else {
          seg.add(1, 0, n - 1, dfsl[ct2], dfsr[ct2] - 1, -1);
          seg.add(1, 0, n - 1, 0, n - 1, 1);
        }
      } else {
        if (dfsl[ct2] <= x && x < dfsr[ct2]) {
          seg.add(1, 0, n - 1, dfsl[ct2], dfsr[ct2] - 1, -1);
          seg.add(1, 0, n - 1, 0, n - 1, 1);
          ct = ct2;
        } else {
          seg.add(1, 0, n - 1, dfsl[ct2], dfsr[ct2] - 1, 1);
          ct2 = ct;
        }
      }
    }
    cout << (seg.query(1, 0, n - 1, 0, n - 1) + 1) << " \n"[i == n - 1];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T = 1;
  cin >> T;
  while (T--) solve();
  return 0;
}