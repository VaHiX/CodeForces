/*
 * Problem URL : https://codeforces.com/problemset/problem/2097/B
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
namespace IO {
char buf[1 << 16], *p1 = buf, *p2 = buf, ibuf;
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin)),          \
   p1 == p2 ? EOF : *p1++)
int rd(int x = 0, int f = 1) {
  for (; !isdigit(ibuf); ibuf = getchar())
    if (ibuf == '-')
      f = -1;
  for (; isdigit(ibuf); ibuf = getchar())
    x = x * 10 + (ibuf ^ 48);
  return x * f;
}
int rds(char *s, int n = 0) {
  for (; !isgraph(ibuf); ibuf = getchar())
    if (ibuf == EOF)
      return -1;
  for (; isgraph(ibuf); ibuf = getchar())
    s[n++] = ibuf;
  return s[n] = 0, n;
}
} // namespace IO
using IO::rd;
using IO::rds;
int deg[1000100];
int d2[1000100];
int pa[1000100];
int siz[1000100];
int sum[1000100];
int s2[1000100];
int x[1000100], y[1000100];
int find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
const int mod = 1000000007;
void con(int x, int y) {
  x = find(x), y = find(y);
  if (x == y)
    return;
  siz[x] += siz[y];
  pa[y] = x;
}
int slv(int n, int m, int k) {
  for (int i = 0; i < n * m; i++)
    pa[i] = i, siz[i] = 1, deg[i] = 0, sum[i] = 0, d2[i] = 0, s2[i] = 0;
  for (int i = 0; i < k; i++) {
    int a = x[i], b = y[i], c = x[i + 1], d = y[i + 1];
    if (abs(a - c) + abs(b - d) != 2)
      return 0;
    if (abs(a - c) == 0) {
      int x = a, y = b + d >> 1;
      d2[x * m + y]++;
    } else if (abs(b - d) == 0) {
      int x = a + c >> 1, y = b;
      d2[x * m + y]++;
    } else {
      //(a,d),(c,b)
      deg[a * m + d]++, deg[c * m + b]++;
      con(a * m + d, c * m + b);
    }
  }
  int ans = 1;
  for (int i = 0; i < n * m; i++)
    sum[find(i)] += deg[i];
  for (int i = 0; i < n * m; i++)
    s2[find(i)] += d2[i];
  for (int i = 0; i < n * m; i++)
    if (find(i) == i) {
      int x = siz[i];
      if (sum[i] + s2[i] * 2 > siz[i] * 2)
        return 0;
      if (sum[i] == siz[i] * 2) // ring
      {
        ans = ans * 2 % mod;
      } else {
        if (!s2[i])
          ans = ans * siz[i] % mod;
      }
    }
  return ans;
}
signed main() {
  int T = rd();
  while (T--) {
    int n = rd(), m = rd(), k = rd();
    for (int i = 0; i <= k; i++)
      x[i] = rd() - 1, y[i] = rd() - 1;
    printf("%lld\n", slv(n, m, k));
  }
}