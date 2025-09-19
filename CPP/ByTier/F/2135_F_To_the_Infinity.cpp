/*
 * Problem URL : https://codeforces.com/contest/2135/problem/F
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

const int MAXN = 400000 + 10;
const int MAXNODE = MAXN * 20;

struct PSTNode {
  int l, r;
  int num;
  ull val;
} t[MAXNODE];
int cnt;
int rt[MAXN];

ull seedA =
    (ull)chrono::high_resolution_clock::now().time_since_epoch().count();
inline ull shift_x(ull x) {
  x ^= seedA;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 11;
  x ^= seedA;
  return x;
}

void add(int &p, int pre, int L, int R, int pos, ull v) {
  p = ++cnt;
  t[p] = t[pre];
  t[p].val += v;
  t[p].num++;
  if (L == R)
    return;
  int mid = (L + R) >> 1;
  if (pos <= mid)
    add(t[p].l, t[pre].l, L, mid, pos, v);
  else
    add(t[p].r, t[pre].r, mid + 1, R, pos, v);
}

bool cmpSeg(int p, int pre, int L, int R) {
  if (L == R)
    return t[p].num > t[pre].num;
  int mid = (L + R) >> 1;
  if (t[t[p].r].val == t[t[pre].r].val)
    return cmpSeg(t[p].l, t[pre].l, L, mid);
  else
    return cmpSeg(t[p].r, t[pre].r, mid + 1, R);
}

int n;
int lf[MAXN], rg[MAXN], fa[MAXN], degc[MAXN];
ull hval[MAXN];
int rk[MAXN];

struct CmpPQ {
  bool operator()(int x, int y) const {
    if (hval[x] == hval[y])
      return x > y;
    return cmpSeg(rt[x], rt[y], 1, n);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  if (!(cin >> T))
    return 0;
  while (T--) {
    cin >> n;
    cnt = 0;
    for (int i = 1; i <= n; ++i) {
      rt[i] = 0;
      fa[i] = 0;
      degc[i] = 0;
      hval[i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
      int a, b;
      cin >> a >> b;
      lf[i] = a;
      rg[i] = b;
      if (a)
        fa[a] = i;
      if (b)
        fa[b] = i;
      degc[i] = (a && b) ? 2 : 0;
    }

    priority_queue<int, vector<int>, CmpPQ> pq;
    for (int i = 1; i <= n; ++i)
      if (degc[i] == 0) {
        hval[i] = 1;
        pq.push(i);
      }

    int lst = 0;
    int tot = 0;
    vector<int> ans;
    ans.reserve(n);
    while (!pq.empty()) {
      int u = pq.top();
      pq.pop();
      ans.push_back(u);
      if (hval[u] != hval[lst])
        ++tot;
      lst = u;
      rk[u] = tot;

      int p = fa[u];
      if (p) {
        degc[p]--;
        if (degc[p] == 0) {
          hval[p] = hval[lf[p]] + shift_x(hval[rg[p]]);
          add(rt[p], rt[lf[p]], 1, n, rk[rg[p]], shift_x(hval[rg[p]]));
          pq.push(p);
        }
      }
    }

    for (int i = 0; i < (int)ans.size(); ++i) {
      if (i)
        cout << ' ';
      cout << ans[i];
    }
    cout << '\n';
  }
  return 0;
}
