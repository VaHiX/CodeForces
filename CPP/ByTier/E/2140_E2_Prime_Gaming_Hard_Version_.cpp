/*
 * Problem URL : https://codeforces.com/contest/2140/problem/E2
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1'000'000'007;
using i64 = long long;
using u32 = uint32_t;

inline int addm(int a, int b) {
  a += b;
  if (a >= MOD)
    a -= MOD;
  return a;
}
inline int subm(int a, int b) {
  a -= b;
  if (a < 0)
    a += MOD;
  return a;
}
inline int mulm(i64 a, i64 b) { return int((a * b) % MOD); }

static const int MX = 25;
int f[MX], ifc[MX], P[MX][MX];

int mpow(i64 a, int e) {
  i64 r = 1;
  while (e) {
    if (e & 1)
      r = (r * a) % MOD;
    a = (a * a) % MOD;
    e >>= 1;
  }
  return (int)r;
}
int inv(int x) { return mpow(x, MOD - 2); }
void init() {
  f[0] = 1;
  for (int i = 1; i < MX; i++)
    f[i] = mulm(f[i - 1], i);
  ifc[MX - 1] = inv(f[MX - 1]);
  for (int i = MX - 2; i >= 0; i--)
    ifc[i] = mulm(ifc[i + 1], i + 1);
  for (int i = 0; i < MX; i++) {
    P[i][0] = 1;
    for (int j = 1; j < MX; j++)
      P[i][j] = mulm(P[i][j - 1], i);
  }
}

inline int C(int n, int r) {
  if (r < 0 || r > n)
    return 0;
  return mulm(f[n], mulm(ifc[r], ifc[n - r]));
}

int spows(i64 M, int p) {
  if (M <= 0)
    return (p == 0 ? 1 : 0);
  int k = p + 1;
  static int y[MX];
  i64 s = 0;
  for (int i = 0; i <= k; i++) {
    int u = (p == 0 ? 1 : P[i][p]);
    s += u;
    if (s >= MOD)
      s -= MOD;
    y[i] = (int)s;
  }
  if (M <= k)
    return y[(int)M];
  i64 x = M % MOD;
  static int pre[MX + 2], suf[MX + 2];
  pre[0] = 1;
  for (int i = 0; i <= k; i++)
    pre[i + 1] = mulm(pre[i], (x - i + MOD) % MOD);
  suf[k + 1] = 1;
  for (int i = k; i >= 0; i--)
    suf[i] = mulm(suf[i + 1], (x - i + MOD) % MOD);
  int r = 0;
  for (int i = 0; i <= k; i++) {
    int num = mulm(pre[i], suf[i + 1]);
    int t = mulm(y[i], mulm(num, mulm(ifc[i], ifc[k - i])));
    if ((k - i) & 1)
      t = subm(0, t);
    r = addm(r, t);
  }
  return r;
}

static inline unsigned sr(unsigned S, int i) {
  unsigned l = S & ((1u << (i - 1)) - 1), h = S >> i;
  return l | (h << (i - 1));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  init();
  int T;
  if (!(cin >> T))
    return 0;
  while (T--) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> g(k);
    for (int i = 0; i < k; i++)
      cin >> g[i];
    if (m == 1) {
      cout << 1 << "\n";
      continue;
    }
    vector<vector<int>> A(n + 1);
    for (int p = 1; p <= n; p++)
      for (int x : g)
        if (x <= p)
          A[p].push_back(x);
    vector<unsigned char> pv(2);
    pv[0] = 0;
    pv[1] = 1;
    for (int p = 2; p <= n; p++) {
      size_t SZ = 1u << p;
      vector<unsigned char> cu(SZ);
      bool al = ((n - p) % 2 == 0);
      auto &opt = A[p];
      const unsigned char *pr = pv.data();
      for (unsigned S = 0; S < SZ; S++) {
        if (al) {
          unsigned char r = 0;
          for (int i : opt) {
            unsigned sh = sr(S, i);
            if (pr[sh]) {
              r = 1;
              break;
            }
          }
          cu[S] = r;
        } else {
          unsigned char r = 1;
          for (int i : opt) {
            unsigned sh = sr(S, i);
            if (!pr[sh]) {
              r = 0;
              break;
            }
          }
          cu[S] = r;
        }
      }
      pv.swap(cu);
    }
    int N = 1 << n;
    vector<int> U(n + 1, 0);
    for (int S = 0; S < N; S++)
      if (pv[S])
        ++U[__builtin_popcount((u32)S)];
    vector<int> Sp(n + 1);
    i64 M = m - 1;
    for (int r = 0; r <= n; r++)
      Sp[r] = spows(M, r);
    vector<int> PM(n + 1);
    PM[0] = 1;
    for (int e = 1; e <= n; e++)
      PM[e] = mulm(PM[e - 1], m);
    int ans = 0;
    for (int s = 0; s <= n; s++)
      if (U[s]) {
        int inn = 0, d = n - s;
        for (int j = 0; j <= s; j++) {
          int t = mulm(C(s, j), mulm(PM[s - j], Sp[j + d]));
          if (j & 1)
            t = subm(0, t);
          inn = addm(inn, t);
        }
        ans = (ans + mulm(U[s], inn)) % MOD;
      }
    cout << ans << "\n";
  }
  return 0;
}