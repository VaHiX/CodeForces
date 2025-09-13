/*
 * Problem URL : https://codeforces.com/problemset/problem/2061/I
 * Submit Date : 2025-08-23
 */

#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stdint.h>
#include <unordered_map>
#include <vector>
using namespace std;
typedef long long ll;
const int maxn = 300005;
const ll inf = 0x3f3f3f3f3f3f3f3fll;
int T, n, p[maxn];
ll dp[maxn], buf[maxn], gg[maxn];
pair<int, int> gq(int l, int r) {
  return make_pair(max(0, l - (r - 1) / 2), min(l, (r - 1) / 2));
}
void efz(int l, int r, int x, int tl, int tr, int gc) {
  if (l > r || tl > tr)
    return;
  int mid = l + r >> 1, cd = 0;
  ll mn = inf;
  for (int i = max(tl, mid - gc); i <= min(tr, mid); ++i) {
    ll tmp = buf[i] + gg[mid - i];
    if (mn > tmp)
      mn = tmp, cd = i;
  }
  dp[mid + x] = min(dp[mid + x], mn);
  efz(l, mid - 1, x, tl, cd, gc);
  efz(mid + 1, r, x, cd, tr, gc);
}
void solve(int l, int r) {
  int cl = gq(l, r).first, cr = gq(l, r).second;
  if (l + 1 == r) {
    if (p[r] == -1)
      dp[cl + 1] = min(dp[cl + 1], dp[cl]);
    else
      dp[cl + 1] = min(dp[cl + 1], dp[cl] + p[r]);
    return;
  }
  vector<ll> vc;
  int mid = l + r >> 1;
  for (int i = cl; i <= cr; ++i)
    vc.push_back(dp[i]);
  solve(l, mid);
  int cnt = 0, cm = 0;
  for (int i = l + 1; i <= mid; ++i) {
    if (p[i] >= 0)
      gg[++cnt] = p[i];
    else
      ++cm;
  }
  sort(gg + 1, gg + cnt + 1);
  for (int i = 2; i <= cnt; ++i)
    gg[i] += gg[i - 1];
  int tul = gq(l, mid).first, tur = gq(l, mid).second;
  for (int i = cl; i <= cr; ++i)
    buf[i] = vc[i - cl];
  efz(cl, tul - 1 + cnt, 0, cl, tul - 1, cnt);
  efz(tur + 1, cr + cnt, cm, tur + 1, cr, cnt);
  vc.clear();
  for (int i = cl; i <= cr + mid - l; ++i)
    vc.push_back(dp[i]);
  solve(mid, r);
  cnt = cm = 0;
  for (int i = mid + 1; i <= r; ++i) {
    if (p[i] >= 0)
      gg[++cnt] = p[i];
    else
      ++cm;
  }
  sort(gg + 1, gg + cnt + 1);
  for (int i = 2; i <= cnt; ++i)
    gg[i] += gg[i - 1];
  tul = gq(mid, r).first, tur = gq(mid, r).second;
  for (int i = cl; i <= cr + mid - l; ++i)
    buf[i] = vc[i - cl];
  efz(cl, tul - 1 + cnt, 0, cl, tul - 1, cnt);
  efz(tur + 1, cr + mid - l + cnt, cm, tur + 1, cr + mid - l, cnt);
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; ++i)
      cin >> p[i], dp[i] = inf;
    solve(0, n);
    for (int i = 0; i <= n; ++i)
      cout << dp[i] << ' ';
    cout << '\n';
  }
  return 0;
}