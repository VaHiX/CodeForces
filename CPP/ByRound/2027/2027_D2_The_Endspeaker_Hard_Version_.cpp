/*
 * Problem URL : https://codeforces.com/contest/2027/problem/D2
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
#define EL puts("Elaina")
typedef long long ll;
using namespace std;
namespace IO {
const int siz = 1 << 18;
char buf[siz], *p1, *p2;
inline char getc() {
  return p1 == p2 && (p2 = buf + fread(p1 = buf, 1, siz, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
inline int read() {
  int x = 0;
  char ch = getc();
  bool f = 1;
  while (!isdigit(ch))
    ch == '-' && (f = 0), ch = getc();
  while (isdigit(ch))
    x = x * 10 + (ch ^ 48), ch = getc();
  return f ? x : -x;
}
} // namespace IO
using IO::read;
const int maxn = 3e5 + 3, mod = 1e9 + 7;
int n, m, a[maxn], b[maxn], g[maxn];
ll f[maxn];
inline void add(int &x, const int y) { (x += y) >= mod && (x -= mod); }
inline void MyDearMoments() {
  n = read(), m = read();
  int tmp = 0;
  for (int i = 1; i <= n; ++i)
    a[i] = read(), a[i] > tmp && (tmp = a[i]);
  for (int i = 1; i <= m; ++i)
    b[i] = read();
  if (tmp > b[1]) {
    puts("-1");
    return;
  }
  memset(f + 1, 0x3f, n * sizeof(ll)), g[0] = 1;
  for (int k = 1; k <= m; ++k) {
    ll sum = 0;
    int ts = 0;
    for (int i = 1, j1 = 1, j2 = 0; i <= n; ++i) {
      sum += a[i];
      while (j1 <= i && sum > b[k])
        sum -= a[j1], add(ts, mod - g[j1 - 1]), ++j1;
      if (j2 < j1)
        j2 = j1, ts = g[j1 - 1];
      while (j2 < i && f[j2] == f[j1 - 1])
        add(ts, g[j2++]);
      if (j1 <= i)
        if (f[j1 - 1] + m - k < f[i])
          f[i] = f[j1 - 1] + m - k, g[i] = ts;
        else if (f[j1 - 1] + m - k == f[i])
          f[i] = f[j1 - 1] + m - k, add(g[i], ts);
    }
  }
  printf("%lld %d\n", f[n], g[n]);
}
int main() {
  int T = read();
  while (T--)
    MyDearMoments();
  return 0;
}