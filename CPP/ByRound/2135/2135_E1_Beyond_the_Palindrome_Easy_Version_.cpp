/*
 * Problem URL : https://codeforces.com/contest/2135/problem/E1
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 998244353;
const int MAXN = 1000000 + 10;

inline int addm(int x, int y) {
  x += y;
  return x >= MOD ? x - MOD : x;
}
inline int subm(int x, int y) {
  x -= y;
  return x < 0 ? x + MOD : x;
}
inline void inc(int &x, int y) {
  x += y;
  if (x >= MOD)
    x -= MOD;
}
inline void dec(int &x, int y) {
  x -= y;
  if (x < 0)
    x += MOD;
}

int invv[MAXN], arr[MAXN], pref[MAXN];

void buildInv(int n) {
  invv[1] = 1;
  for (int i = 2; i <= n; ++i)
    invv[i] = (ll)(MOD - MOD / i) * invv[MOD % i] % MOD;
}

int n;

inline int rangeSum(int l, int r) {
  l = max(l, 0);
  r = min(r, n);
  if (l > r)
    return 0;
  return l ? subm(pref[r], pref[l - 1]) : pref[r];
}

int calc(int k, int t) {
  int res = 0;
  int step = k + 2 - t;
  int L0 = (n - k) >> 1;
  int R0 = (n + k) >> 1;
  for (int p = 0; R0 - p * step >= 0; ++p) {
    int L = L0 - p * step;
    int R = R0 - t - p * step;
    inc(res, rangeSum(L, R));
  }
  for (int p = 0; L0 - 1 - p * step >= 0; ++p) {
    int idx = L0 - 1 - p * step;
    dec(res, (ll)(k + 1 - t) * arr[idx] % MOD);
  }
  for (int p = 1; L0 + p * step <= n; ++p) {
    int L = L0 + p * step;
    int R = R0 - t + p * step;
    inc(res, rangeSum(L, R));
  }
  for (int p = 0; R0 + 1 - t + p * step <= n; ++p) {
    int idx = R0 + 1 - t + p * step;
    dec(res, (ll)(k + 1 - t) * arr[idx] % MOD);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  buildInv(MAXN - 1);
  int T;
  if (!(cin >> T))
    return 0;
  while (T--) {
    cin >> n;
    arr[0] = 1;
    pref[0] = 1;
    for (int i = 1; i <= n; ++i) {
      arr[i] = (ll)arr[i - 1] * invv[i] % MOD * (n - i + 1) % MOD;
      pref[i] = addm(pref[i - 1], arr[i]);
    }
    int ans = 0;
    int x = 0, y = 0;
    for (int k = 1; k <= n; ++k) {
      if (((n + k) & 1))
        continue;
      inc(ans, x);
      x = calc(k, 0);
      inc(ans, x);
      y = calc(k, 1);
      int twoY = addm(y, y);
      dec(ans, twoY);
    }
    cout << ans << '\n';
  }
  return 0;
}
