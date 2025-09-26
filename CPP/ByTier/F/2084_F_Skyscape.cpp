/*
 * Problem URL : https://codeforces.com/problemset/problem/2084/F
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
const int inf = 2e9;
int n, m;
int a[N], b[N], c[N];
int p[N], q[N];
#define lowbit(x) (x & -x)
struct BIT {
  int t[N];
  void init() {
    for (int i = 0; i <= n; i++)
      t[i] = 0;
  }
  void add(int x, int y) {
    for (; x <= n; x += lowbit(x))
      t[x] = max(t[x], y);
  }
  int qry(int x) {
    int mx = 0;
    for (; x; x -= lowbit(x))
      mx = max(mx, t[x]);
    return mx;
  }
} t;
struct BIT2 {
  int t[N];
  void init() {
    for (int i = 0; i <= n; i++)
      t[i] = inf;
  }
  void add(int x, int y) {
    for (; x; x -= lowbit(x))
      t[x] = min(t[x], y);
  }
  int qry(int x) {
    int mx = inf;
    for (; x <= n; x += lowbit(x))
      mx = min(mx, t[x]);
    return mx;
  }
} t2;
struct node {
  int r, x;
  friend bool operator<(const node &x, const node &y) {
    return x.r > y.r || (x.r == y.r && x.x > y.x);
  }
};
vector<node> g[N];
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    p[i] = q[i] = c[i] = 0, g[i].clear();
  for (int i = 1; i <= n; i++)
    cin >> a[i], p[a[i]] = i;
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
    if (b[i])
      q[b[i]] = i;
  }
  t.init();
  for (int i = 1; i <= n; i++) {
    if (q[i]) {
      if (t.qry(p[i]) > q[i])
        return cout << "-1\n", void();
      t.add(p[i], q[i]);
    }
  }
  t.init();
  t2.init();
  for (int i = 1; i <= n; i++) {
    if (q[a[i]]) {
      t.add(a[i], q[a[i]]);
    } else
      c[i] = t.qry(a[i]) + 1;
  }
  for (int i = n; i >= 1; i--) {
    if (q[a[i]]) {
      t2.add(a[i], q[a[i]]);
    } else {
      int r = t2.qry(a[i]) - 1;
      if (r < c[i])
        return cout << "-1\n", void();
      g[c[i]].push_back({r, a[i]});
    }
  }
  priority_queue<node> q;
  for (int i = 1; i <= n; i++) {
    for (node p : g[i])
      q.push(p);
    if (!b[i]) {
      if (q.empty() || q.top().r < i)
        return cout << "-1\n", void();
      b[i] = q.top().x;
      q.pop();
    }
  }
  for (int i = 1; i <= n; i++)
    cout << b[i] << " \n"[i == n];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int _;
  cin >> _;
  while (_--)
    solve();
  return 0;
}