/*
 * Problem URL : https://codeforces.com/problemset/problem/2063/F2
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>

using namespace std;

#define MOD 998244353

int t, n, x[300005], y[300005], par[600005], si[600005];
long long fac[600005], inv[600005], cat[300005], icat[300005], ans[300005];

long long po(long long b, int p) {
  long long re = 1;
  while (p) {
    if (p % 2)
      re = re * b % MOD;
    b = b * b % MOD;
    p /= 2;
  }
  return re;
}

int find(int a) { return par[a] == a ? a : par[a] = find(par[a]); }

int main() {
  fac[0] = 1;
  for (int i = 1; i < 600005; i++)
    fac[i] = fac[i - 1] * i % MOD;
  inv[600004] = po(fac[600004], MOD - 2);
  for (int i = 600003; i >= 0; i--)
    inv[i] = inv[i + 1] * (i + 1) % MOD;
  for (int i = 0; i < 300002; i++) {
    cat[i] = fac[i * 2] * inv[i + 1] % MOD * inv[i] % MOD;
    icat[i] = inv[i * 2] * fac[i + 1] % MOD * fac[i] % MOD;
  }
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    fill(si, si + n * 2 + 1, 0);
    for (int i = 0; i <= n * 2; i++)
      par[i] = i;
    for (int i = 0; i < n; i++) {
      scanf("%d%d", x + i, y + i);
      int ta = find(x[i] - 1);
      int tb = find(y[i]);
      if (ta != tb)
        par[ta] = tb;
    }
    ans[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
      ans[i] = ans[i + 1];
      int tmp = find(x[i]);
      ans[i] = ans[i] * icat[si[tmp]] % MOD;
      si[tmp]++;
      ans[i] = ans[i] * cat[si[tmp]] % MOD;
      for (int j : {x[i], y[i]}) {
        int ta = find(j - 1);
        int tb = find(j);
        if (ta == tb)
          continue;
        par[tb] = ta;
        ans[i] = ans[i] * icat[si[ta]] % MOD * icat[si[tb]] % MOD;
        si[ta] += si[tb];
        ans[i] = ans[i] * cat[si[ta]] % MOD;
      }
    }
    for (int i = 0; i <= n; i++)
      printf("%lld%c", ans[i], " \n"[i == n]);
  }
}
