/*
 * Problem URL : https://codeforces.com/contest/2035/problem/G2
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
#define Gc() getchar()
#define Me(x, y) memset(x, y, sizeof(x))
#define Mc(x, y) memcpy(x, y, sizeof(x))
#define d(x, y) ((m) * (x - 1) + (y))
#define R(n) (rnd() % (n) + 1)
#define Pc(x) putchar(x)
#define LB lower_bound
#define UB upper_bound
#define fi first
#define se second
#define eb emplace_back
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;
using db = double;
using lb = long db;
using ui = unsigned;
using ull = unsigned long long;
using pii = pair<int, int>;
const int N = 3e5 + 5, M = N * 4 + 5, K = 1000 + 5, mod = 998244353,
          Mod = mod - 1;
const db eps = 1e-9;
const int INF = 1e9 + 7;
mt19937 rnd(28382);
#define Tp template <typename T>
#define Ts template <typename T, typename... Ar>
namespace Debug {
Tp void _debug(char *f, T t) { cerr << f << '=' << t << endl; }
Ts void _debug(char *f, T x, Ar... y) {
  while (*f != ',')
    cerr << *f++;
  cerr << '=' << x << ",";
  _debug(f + 1, y...);
}
#ifdef LOCAL
#define gdb(...) _debug((char *)#__VA_ARGS__, __VA_ARGS__)
#else
#define gdb(...) void()
#endif
} // namespace Debug
using namespace Debug;
int m, n, A[N];
int d[N];
int id[N], mid[M];
ll siz[M];
void build(int l = 1, int r = n, int v = 1) {
  if (l == r) {
    id[l] = v;
    siz[v] = 1;
    return;
  }
  mid[v] = l + r >> 1;
  build(l, mid[v], v << 1);
  build(mid[v] + 1, r, v << 1 | 1);
  siz[v] = siz[v << 1] * siz[v << 1 | 1] % mod * n % mod;
}
ll dp[N];
vector<int> S[N];
ll f[M][2];
void add(int x, ll w) {
  w = (w * dp[x] % mod + mod) % mod;
  int y = id[x];
  while (y ^ 1) {
    if (~y & 1) {
      if (x == mid[y >> 1])
        (f[y >> 1][0] += w) %= mod;
      else {
        (f[y >> 1][0] += (mod - A[x]) * w) %= mod;
        (f[y >> 1][1] += w) %= mod;
      }
      (w *= siz[y ^ 1]) %= mod;
      if (mid[y >> 1] ^ x)
        (w *= n - A[x] + 1) %= mod;
    }
    y >>= 1;
  }
}
ll qry(int x) {
  ll ans = 0;
  ll w = 1;
  int y = id[x];
  while (y ^ 1) {
    if (y & 1) {
      (ans += w * f[y >> 1][0] + w * f[y >> 1][1] % mod * A[x]) %= mod;
      (w *= siz[y ^ 1]) %= mod;
      (w *= A[x] - 1) %= mod;
    }
    y >>= 1;
  }
  return ans;
}
void Solve() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    A[i] = -1, d[i] = 0, dp[i] = 0;
  for (int i = 1; i <= m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (y ^ 1 || x == 1)
      A[x] = y;
  }
  vector<int> st;
  for (int i = 1; i <= n; i++)
    if (~A[i]) {
      auto it = LB(all(st), A[i]);
      d[i] = max(1, int(it - st.begin()) + 1);
      if (it == st.end())
        st.push_back(A[i]);
      else
        (*it) = A[i];
    }
  int mx = *max_element(d + 1, d + n + 1);
  ll ans = 0;
  if (mx == 0) {
    ans = 1;
    for (int i = 1; i <= n; i++)
      (ans *= n) %= mod;
  }
  build(1, n, 1);
  for (int i = 1; i <= n; i++)
    S[i].clear();
  for (int i = 1; i <= n; i++)
    if (d[i])
      S[d[i]].push_back(i);
  for (int j = 1; j <= n; j++) {
    int L = 0, R = -1;
    for (int i : S[j]) {
      if (d[i] == 1) {
        int x = id[i];
        ll w = 1;
        while (x ^ 1) {
          if (x & 1) {
            (w *= siz[x ^ 1]) %= mod;
            (w *= A[i] - 1) %= mod;
          }
          x >>= 1;
        }
        dp[i] = w;
      }
      while (R + 1 < S[j - 1].size() && S[j - 1][R + 1] < i)
        add(S[j - 1][R + 1], 1), R++;
      while (L < S[j - 1].size() && A[S[j - 1][L]] > A[i])
        add(S[j - 1][L], -1), L++;
      (dp[i] += qry(i)) %= mod;
      if (d[i] == mx) {
        ll w = dp[i] * (i == n ? 1 : n) % mod;
        int y = id[i];
        while (y ^ 1) {
          if (~y & 1) {
            (w *= siz[y ^ 1]) %= mod;
            if (mid[y >> 1] ^ i)
              (w *= n - A[i] + 1) %= mod;
          }
          y >>= 1;
        }
        ans += w;
      }
    }
    while (L <= R)
      add(S[j - 1][L], -1), L++;
  }
  printf("%d %lld\n", m - mx, ans % mod);
}
int main() {
  int t = 1;
  scanf("%d", &t);
  while (t--)
    Solve();
  cerr << clock() * 1.0 / CLOCKS_PER_SEC << '\n';
}