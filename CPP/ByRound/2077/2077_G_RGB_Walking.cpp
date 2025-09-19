/*
 * Problem URL : https://codeforces.com/problemset/problem/2077/G
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int N = 222222;
int n, m, w, ex[N], ey[N], ez[N], ec[N], f[N * 8], s[3], ans;
char ch[11];
int fnd(int x) {
  if (f[x] == x)
    return x;
  return f[x] = fnd(f[x]);
}
void solve2(int D, int X, int Y, int x, int y) {
  int g, a, b, c, i;
  x = (x % X + X) % X;
  y = (y % Y + Y) % Y;
  g = __gcd(__gcd(X, Y), D);
  D /= g, X /= g, Y /= g;
  a = __gcd(X, Y);
  b = __gcd(D, Y);
  c = __gcd(D, X);
  for (i = 0; i < a; i++)
    ans = min((LL)ans, max((x + (LL)i * b * c * g) % (a * c * g),
                           (y + (LL)i * b * c * g) % (a * b * g)));
}
void solve(int j) {
  int x, y, z;
  x = j & 1 ? s[0] : 0;
  y = j & 2 ? s[1] : 0;
  z = j & 4 ? s[2] : 0;
  solve2(s[0] * 2, s[1] * 2, s[2] * 2, x - y, x - z);
  solve2(s[1] * 2, s[2] * 2, s[0] * 2, y - z, y - x);
  solve2(s[2] * 2, s[0] * 2, s[1] * 2, z - x, z - y);
}
int main() {
  int T, i, j, k, x, y, z, o;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &w);
    for (k = 0; k < 3; k++)
      s[k] = 0;
    for (i = 1; i <= m; i++) {
      scanf("%d%d%d%s", ex + i, ey + i, ez + i, ch);
      ec[i] = ch[0] == 'r' ? 0 : ch[0] == 'g' ? 1 : 2;
      s[ec[i]] = __gcd(s[ec[i]], ez[i]);
    }
    for (i = 1; i <= n; i++)
      for (j = 0; j < 8; j++)
        f[i * 8 + j] = i * 8 + j;
    for (i = 1; i <= m; i++)
      for (j = 0; j < 8; j++)
        f[fnd(ex[i] * 8 + j)] =
            fnd(ey[i] * 8 + (j ^ ((ez[i] / s[ec[i]] % 2) << ec[i])));
    ans = 1e9;
    for (j = 0; j < 8; j++)
      if (fnd(1 * 8 + 0) == fnd(n * 8 + j))
        solve(j);
    printf("%d\n", ans);
  }
  return 0;
}