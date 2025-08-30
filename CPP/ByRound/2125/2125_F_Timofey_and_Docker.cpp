/*
 * Problem URL : https://codeforces.com/problemset/problem/2125/F
 * Submit Date : 2025-08-14
 */

// godmoo's code
#include <bits/stdc++.h>
#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define mkp make_pair
#define lbd lower_bound
#define ubd upper_bound
#define IMX INT_MAX
#define LMX LLONG_MAX
#define mathmod(a) (((a) % MOD + MOD) % MOD)
#define mem(a, b) memset(a, b, sizeof(a))
#define cpy(a, b) memcpy(a, b, sizeof(b))
#define ckmx(a, b) (a = max(a, b))
#define ckmn(a, b) (a = min(a, b))
#define all(a) a.begin(), a.end()
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
const int N = 5e5 + 5;
const pair<ll, int> INF = mkp(0x3f3f3f3f3f3f3f3fll, 0x3f3f3f3f);
int T, len, n, d[N], cst[N];
pair<ll, int> f[N];
char s[N];
int check(int m) {
  f[0] = mkp(0, 0);
  for (int i = 1; i <= len; i++)
    f[i] = min(f[i - 1],
               i < 6 ? INF : mkp(f[i - 6].fi + cst[i] - m, f[i - 6].se + 1));
  return f[len].se;
}
void init() {
  for (int i = 0, k = len / 6 + 1; i <= k; i++)
    d[i] = 0;
}
void solve() {
  init();
  cin >> (s + 1) >> n;
  int k = (len = strlen(s + 1)) / 6, cnt = 0;
  for (int i = 6; i <= len; i++) {
    cst[i] = (s[i - 5] != 'd') + (s[i - 4] != 'o') + (s[i - 3] != 'c') +
             (s[i - 2] != 'k') + (s[i - 1] != 'e') + (s[i] != 'r');
    if (!cst[i])
      cnt++;
  }
  for (int i = 1, l, r; i <= n; i++) {
    cin >> l >> r;
    if (l > k)
      continue;
    d[l]++, d[min(r, k) + 1]--;
  }
  if (!k)
    return cout << 0 << "\n", void(); // 此时再判，保证读入完成
  for (int i = 1; i <= k; i++)
    d[i] += d[i - 1];
  int mx = *max_element(d + 1, d + k + 1), pos1 = -0x3f3f3f3f, pos2 = k + 1;
  if (!mx)
    return cout << 0 << "\n", void(); //
  for (int i = 1; i <= k; i++)
    if (d[i] == mx) {
      if (i == cnt)
        return cout << 0 << "\n", void();
      else
        i < cnt ? ckmx(pos1, i) : ckmn(pos2, i);
    }
  if (pos1 == -0x3f3f3f3f && pos2 == k + 1)
    return cout << 0 << "\n", void(); //
  if (pos2 == k + 1)
    return cout << (cnt - pos1) << "\n", void();
  int l = 0, r = len + 1, ans;
  while (l <= r) {
    int m = l + r >> 1;
    if (check(m) <= pos2)
      l = m + 1, ans = m;
    else
      r = m - 1;
  }
  check(ans);
  cout << min((ll)cnt - pos1, f[len].fi + (ll)pos2 * ans) << "\n";
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  for (cin >> T; T; T--)
    solve();
  cout << flush;
  return 0;
}