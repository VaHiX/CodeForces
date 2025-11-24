// Problem: CF 2081 E - Quantifier
// https://codeforces.com/contest/2081/problem/E

/*
Algorithm: Dynamic Programming with Tree DP and Combinatorics
Time Complexity: O(n^3 + m^2) per test case
Space Complexity: O(n^2 + m^2) per test case

This problem involves a rooted tree with chips that can be moved according to specific rules. 
The key idea is to use tree dynamic programming where for each node, we compute the number of 
possible arrangements of chips in its subtree. We maintain states for black and white chips separately.

The solution uses:
1. Tree decomposition via DFS
2. Dynamic programming on trees with states for chip arrangements
3. Combinatorial calculations for merging different subtrees
4. Modular arithmetic for handling large numbers
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

using namespace std;
const int N = 5005, MOD = 998244353;
int T, F[N], C[N][N], n, m, p[N], c[N], d[N], fa[N][2], vis[N][2], cc[N][2],
    cnt[N], lst[N], top[N], topc[N], bot[N], botc[N], coef, s[N][2], f[N][N][2],
    S[2], sv[N][2], sw[N][2], tmp[N][2], ans;
basic_string<int> son[N];
int R(int x, int y) { return (x += y) >= MOD ? x - MOD : x; }
int find(int u, int t) { return u == fa[u][t] ? u : find(fa[u][t], t); }
void dfs1(int u, int t) {
  if (vis[u][t])
    return;
  vis[u][t] = 1;
  for (int v : son[u])
    fa[v][t] = u, dfs1(v, t);
}
void calc(int v) {
  if (!s[0][0] && !s[0][1])
    for (int t = 0; t <= 1; t++) {
      s[0][t] = s[v][t];
      for (int i = 1; i <= s[0][t]; i++)
        f[0][i][t] = f[v][i][t];
    }
  else {
    for (int t = 0; t <= 1; t++)
      if (!s[0][t ^ 1] && !s[v][t ^ 1]) {
        f[0][s[0][t] + s[v][t]][t] = 1ll * C[s[0][t] + s[v][t]][s[0][t]] *
                                     f[0][s[0][t]][t] % MOD * f[v][s[v][t]][t] %
                                     MOD;
        f[0][s[0][t]][t] = 0, s[0][t] += s[v][t];
        return;
      }
    int w = 0;
    for (int t = 0; t <= 1; t++) {
      S[t] = s[v][t] + s[w][t];
      sv[s[v][t] + 1][t] = sw[s[w][t] + 1][t] = 0;
      for (int i = s[v][t]; i; i--)
        sv[i][t] = R(sv[i + 1][t], f[v][i][t]);
      for (int i = s[w][t]; i; i--)
        sw[i][t] = R(sw[i + 1][t], f[w][i][t]);
    }
    for (int _ = 0; _ <= 1; _++) {
      for (int t = 0; t <= 1; t++)
        for (int i = 1; i <= S[t]; i++) {
          if (s[v][t ^ 1]) {
            for (int j = max(i - s[w][t], 1); j <= min(i - 1, s[v][t]); j++)
              tmp[i][t] =
                  (tmp[i][t] +
                   1ll * C[i][j] *
                       C[S[0] + S[1] - i - 1][s[v][0] + s[v][1] - j - 1] % MOD *
                       f[v][j][t] % MOD * sw[i - j][t]) %
                  MOD;
            if (i <= s[v][t])
              tmp[i][t] =
                  (tmp[i][t] +
                   1ll * C[S[0] + S[1] - i - 1][s[v][0] + s[v][1] - i - 1] *
                       f[v][i][t] % MOD * (sw[1][0] + sw[1][1])) %
                  MOD;
          }
          if (i <= s[v][t])
            tmp[i][t] = (tmp[i][t] +
                         1ll * C[S[0] + S[1] - i - 1][s[v][0] + s[v][1] - i] *
                             sv[i][t] % MOD * sw[1][t ^ 1]) %
                        MOD;
        }
      swap(v, w), swap(sv, sw);
    }
    for (int t = 0; t <= 1; t++) {
      s[0][t] = S[t];
      for (int i = 1; i <= s[0][t]; i++)
        f[0][i][t] = tmp[i][t], tmp[i][t] = 0;
    }
  }
}
void dfs2(int u) {
  for (int v : son[u])
    dfs2(v);
  s[0][0] = s[0][1] = 0;
  for (int v : son[u])
    if (s[v][0] || s[v][1])
      calc(v);
  s[u][0] = s[0][0] + cc[u][0], s[u][1] = s[0][1] + cc[u][1];
  if (!top[u])
    for (int t = 0; t <= 1; t++)
      for (int i = 1; i <= s[u][t]; i++)
        f[u][i][t] = f[0][i][t];
  else if (top[u] && !s[0][0] && !s[0][1])
    f[u][top[u]][topc[u]] = 1;
  else if (!bot[u]) {
    for (int i = 1; i <= s[0][topc[u]]; i++)
      f[u][i + top[u]][topc[u]] =
          1ll * C[i + top[u]][top[u]] * f[0][i][topc[u]] % MOD;
    for (int i = 1; i <= s[0][topc[u] ^ 1]; i++)
      f[u][top[u]][topc[u]] = R(f[u][top[u]][topc[u]], f[0][i][topc[u] ^ 1]);
  } else {
    for (int i = 1; i <= s[0][botc[u]]; i++)
      f[u][top[u]][topc[u]] = (f[u][top[u]][topc[u]] +
                               1ll * C[i + bot[u]][bot[u]] * f[0][i][botc[u]]) %
                              MOD;
    for (int i = 1; i <= s[0][botc[u] ^ 1]; i++)
      f[u][top[u]][topc[u]] = R(f[u][top[u]][topc[u]], f[0][i][botc[u] ^ 1]);
  }
  for (int i = 1; i <= s[0][0]; i++)
    f[0][i][0] = 0;
  for (int i = 1; i <= s[0][1]; i++)
    f[0][i][1] = 0;
}
int main() {
  cin >> T;
  F[0] = 1;
  for (int i = 1; i <= 5000; i++)
    F[i] = 1ll * F[i - 1] * i % MOD;
  for (int i = 0; i <= 5000; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++)
      C[i][j] = R(C[i - 1][j - 1], C[i - 1][j]);
  }
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
      son[i].clear(), cc[i][0] = cc[i][1] = cnt[i] = top[i] = bot[i] = 0,
                      memset(f[i], 0, sizeof f[i]);
    ans = 0, coef = 1;
    for (int i = 1; i <= n; i++)
      scanf("%d", &p[i]), son[p[i]] += i;
    for (int i = 1; i <= m; i++)
      scanf("%d", &c[i]);
    for (int i = 1; i <= m; i++)
      scanf("%d", &d[i]);
    for (int t = 0; t <= 1; t++)
      for (int i = 1; i <= n; i++)
        fa[i][t] = i, vis[i][t] = 0;
    for (int i = m; i; i--) {
      d[i] = find(d[i], !c[i]), dfs1(d[i], c[i]);
      cc[d[i]][c[i]]++;
      if (cnt[d[i]] && lst[d[i]] != c[i]) {
        if (!bot[d[i]])
          bot[d[i]] = cnt[d[i]], botc[d[i]] = lst[d[i]];
        coef = 1ll * coef * F[cnt[d[i]]] % MOD, cnt[d[i]] = 0;
      }
      lst[d[i]] = c[i], cnt[d[i]]++;
    }
    for (int i = 1; i <= n; i++)
      if (cnt[i])
        top[i] = cnt[i], topc[i] = lst[i], coef = 1ll * coef * F[cnt[i]] % MOD;
    dfs2(1);
    for (int i = 1; i <= s[1][0]; i++)
      ans = R(ans, f[1][i][0]);
    for (int i = 1; i <= s[1][1]; i++)
      ans = R(ans, f[1][i][1]);
    printf("%lld\n", 1ll * ans * coef % MOD);
  }
}


// https://github.com/VaHiX/CodeForces/