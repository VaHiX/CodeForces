/*
 * Problem URL : https://codeforces.com/problemset/problem/2065/H
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;

#define re register
#define Re register
#define i64 long long
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

const int N = 2e5 + 5, P = 998244353, inf = 0x3f3f3f3f;

int mi[N];
struct BIT {
  int tr[N], n;
#define lowbit(x) (x & (-x))
  inline void add(int x, int v) {
    for (; x <= n; x += lowbit(x))
      tr[x] = (tr[x] + v) % P;
  }
  inline int ask(int x) {
    int res = 0;
    for (; x; x -= lowbit(x))
      res = (res + tr[x]) % P;
    return res;
  }
  inline void init(const int nn) {
    n = nn;
    for (re int i = 1; i <= nn; ++i)
      tr[i] = 0;
  }
} pre[2], suf[2];

inline void solve() {
  string s;
  cin >> s;
  int n = s.size(), ans = (mi[n] - 1 + P) % P;
  pre[0].init(n), suf[0].init(n), pre[1].init(n), suf[1].init(n);
  for (re int i = 0; i < n; ++i)
    pre[s[i] - '0'].add(i + 1, mi[i]);
  for (re int i = n - 1; ~i; --i)
    suf[s[i] - '0'].add(n - i, mi[n - i - 1]);
  for (re int i = 0; i < n; ++i) {
    bool x = s[i] - '0';
    ans = (ans + 1ll * mi[i] * suf[!x].ask(n - i) % P) % P;
  }
  int q;
  cin >> q;
  while (q--) {
    int i;
    cin >> i;
    --i;
    bool x = s[i] - '0';
    ans = (ans - 1ll * mi[i] * suf[!x].ask(n - i) % P + P) % P;
    ans = (ans - 1ll * pre[!x].ask(i + 1) * mi[n - i - 1] % P + P) % P;
    pre[x].add(i + 1, P - mi[i]), suf[x].add(n - i, P - mi[n - i - 1]);
    x ^= 1, s[i] = '0' + x;
    ans = (ans + 1ll * mi[i] * suf[!x].ask(n - i) % P) % P;
    ans = (ans + 1ll * pre[!x].ask(i + 1) * mi[n - i - 1] % P) % P;
    pre[x].add(i + 1, mi[i]), suf[x].add(n - i, mi[n - i - 1]);
    cout << ans << ' ';
  }
  cout << '\n';
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  const int n = 2e5;
  mi[0] = 1;
  for (re int i = 1; i <= n; ++i)
    mi[i] = 2ll * mi[i - 1] % P;

  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}