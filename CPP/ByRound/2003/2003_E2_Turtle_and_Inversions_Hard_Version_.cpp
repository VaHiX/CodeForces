/*
 * Problem URL : https://codeforces.com/contest/2003/problem/E2
 * Submit Date : 2025-09-14
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 5e3 + 20;
int cnt_l[N], cnt_r[N], cnt[N];
bool must_l[N], must_r[N];
int n, m;

inline bool has_esh(int x, int y) { // y = x + 1 / x - 1
  if (x > y) {
    x += y;
    y = x - y;
    x = x - y;
  }
  return (cnt[x] - cnt_r[x] > 0);
}

inline int get_next(int ind, int d) {
  bool is_l = true;
  if (must_r[ind])
    is_l = false;
  while (true) {
    ind += d;
    if (ind > n || ind <= 0)
      return -1;
    if ((is_l && must_l[ind]) || (!is_l && must_r[ind]))
      break;
  }
  return ind;
}

inline void solve() {
  cin >> n >> m;
  for (int i = 0; i <= n; i++) {
    must_l[i] = must_r[i] = false;
    cnt_l[i] = cnt_r[i] = cnt[i] = 0;
  }
  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    cnt_l[l]++;
    cnt_r[r]++;
    must_l[l] = true;
    must_r[r] = true;
  }
  int cur = 0;
  for (int i = 1; i <= n; i++) {
    cur += cnt_l[i];
    cnt[i] = cur;
    cur -= cnt_r[i];
  }
  for (int i = 2; i <= n; i++) {
    if (has_esh(i - 1, i))
      must_r[i] |= must_r[i - 1];
  }
  for (int i = n - 1; i >= 1; i--) {
    if (has_esh(i, i + 1))
      must_l[i] |= must_l[i + 1];
  }
  for (int i = 1; i <= n; i++) {
    if (must_l[i] && must_r[i]) {
      cout << -1 << '\n';
      return;
    }
  }
  ll ans = 1ll * n * (n - 1) / 2;
  int cur_r = n + 1, cur_l = 0;
  must_l[0] = must_r[n + 1] = true;
  must_r[0] = must_l[n + 1] = false;
  while (true) {
    cur_l = get_next(cur_l, 1), cur_r = get_next(cur_r, -1);
    if (min(cur_l, cur_r) == -1 || cur_l > cur_r)
      break;
    ans -= cur_r - cur_l;
  }
  cout << ans << '\n';
  return;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int tt;
  cin >> tt;
  while (tt--)
    solve();
}
