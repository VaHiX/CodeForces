// Problem: CF 2089 C2 - Key of Like (Hard Version)
// https://codeforces.com/contest/2089/problem/C2

#include <algorithm>
#include <cstdio>
#include <cstring>
#define F(i, l, r) for (int i = (l), i##_end = (r); i < i##_end; ++i)
using namespace std;
typedef unsigned long long ull;
constexpr int N = 105, M = 5005, MOD = 1000000007;
void reduce_(int &x) {
  if (x < 0)
    x += MOD;
}
void reduce(int &x) {
  if (x >= MOD)
    x -= MOD;
}
int qpow(ull a, int b, ull c = 1) {
  for (; b; b >>= 1, (a *= a) %= MOD)
    if (b & 1)
      (c *= a) %= MOD;
  return (int)c;
}
int n;
struct poly {
  int a[N];
  poly &operator<<=(int x) {
    x %= n;
    rotate(a, a + n - x, a + n);
    return *this;
  }
  void add(int c, const poly &b) {
    F(i, 0, n) a[i] = (int)((a[i] + (ull)c * b.a[i]) % MOD);
  }
  void shs(int c) {
    static int ps[N];
    poly b;
    F(i, 0, n) reduce(ps[i + 1] = ps[i] + a[i]);
    int cn = c / n;
    c %= n;
    int l = (n - c + 1) % n, r = 1 % n;
    F(i, 0, n) {
      b.a[i] = (int)((ull)ps[n] * cn % MOD);
      reduce_(b.a[i] -= ps[l]);
      reduce(b.a[i] += ps[r]);
      if (l > r)
        reduce(b.a[i] += ps[n]);
      if (++l == n)
        l = 0;
      if (++r == n)
        r = 0;
    }
    *this = b;
  }
};
int l, k;
poly f[M][N], g, h;
int solve() {
  scanf("%d%d%d", &n, &l, &k);
  F(i, 0, l + 1) F(j, 0, k + 1) memset(&f[i][j], 0, sizeof(int) * n);
  F(i, 1, l + 1) {
    F(j, 0, k + 1) {
      if (i + j == 1) {
        f[i][j].a[0] = 1;
        continue;
      }
      int br1 = i - 1, br2 = i + j - 1, sbr = br1 + br2,
          iij = qpow(i + j, MOD - 2);
      br1 = qpow(sbr, MOD - 2, br1);
      br2 = qpow(sbr, MOD - 2, br2);
      if (j) {
        g = f[i][j - 1];
        g <<= i;
        f[i][j].add((int)((ull)br1 * j % MOD * iij % MOD), g);
      }
      g = f[i - 1][j];
      g <<= 1;
      reduce(g.a[0] += 1);
      h = g;
      h.shs(i);
      f[i][j].add((int)((ull)br1 % MOD * iij % MOD), h);
      h = g;
      h.shs(i + j);
      f[i][j].add((int)((ull)br2 % MOD * iij % MOD), h);
    }
  }
  F(i, 0, n) printf("%d ", f[l][k].a[i]);
  puts("");
  return 0;
}
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/