// Problem: CF 1993 C - Light Switches
// https://codeforces.com/contest/1993/problem/C

/*
Algorithm: 
- For each chip installed at time a[i], light status toggles every 2*k minutes (k on, k off).
- The key insight is to check for each possible starting time (0 to 2*k - 1) whether a chip exists at that time.
- We compute for each such time the earliest moment when light is on at that time (fr function).
- Then find the minimum such time across all times that have chips.
- If no such time exists, return -1.

Time Complexity: O(n + k)
Space Complexity: O(k)
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <utility>

#define pbk push_back
#pragma GCC optimize("Ofast")
typedef long long ll;
namespace Cirno_loves_Reimu {
char buf[1 << 20], obuf[1 << 20], *p1, *p2, *p3 = obuf;
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)     \
       ? 0                                                                     \
       : *p1++)
#define putchar(x)                                                             \
  (p3 - obuf < 1000000)                                                        \
      ? (*p3++ = x)                                                            \
      : (fwrite(obuf, p3 - obuf, 1, stdout), p3 = obuf, *p3++ = x)
inline int read() {
  int x = 0;
  bool f = 0;
  char c = getchar();
  while (!isdigit(c) && c != '-')
    c = getchar();
  if (c == '-')
    f = 1, c = getchar();
  while (isdigit(c))
    x = x * 10 + c - '0', c = getchar();
  return f ? -x : x;
}
void write(ll x) {
  if (x < 0)
    putchar('-'), x = -x;
  static char buf[19];
  static int len = -1;
  do
    buf[++len] = x % 10 + 48, x /= 10;
  while (x);
  while (len >= 0)
    putchar(buf[len]), --len;
  putchar(' ');
}
void flush() { fwrite(obuf, p3 - obuf, 1, stdout), exit(0); }
} // namespace Cirno_loves_Reimu
using namespace Cirno_loves_Reimu;
#define FOR(i, a, b) for (int i = a, i##i = b; i <= i##i; ++i)
#define ROF(i, a, b) for (int i = a, i##i = b; i >= i##i; --i)
using namespace std;
typedef pair<int, int> pii;
const int N = 5e5 + 7, mod = 998244353;
int n, k, ok[N], a[N];
int jud(ll x, ll d) {
  int t = x % (2 * k);
  if (t < d)
    t += 2 * k;
  return t < d + k;
}
ll fr(ll x, ll d) {
  if (jud(x, d))
    return x;
  int t = x % (2 * k);
  if (t <= d)
    return x - t + d;
  return x - t + 2 * k + d;
}
ll fl(ll x, ll d) {
  if (jud(x, d))
    return x;
  int t = x % (2 * k);
  if (t >= d + k)
    return x - t + d + k - 1;
  return x - t - 2 * k + d + k - 1;
}
void work() {
  n = read(), k = read();
  ll mx = 0;
  FOR(i, 0, 2 * k) ok[i] = 0;  // Initialize flags for each time slot in 2*k period
  FOR(i, 1, n) {
    a[i] = read(), ok[a[i] % (2 * k)] = 1;  // Mark which slots have chips
    mx = max(mx, 1ll * a[i]);  // Track max installation time
  }
  ll r = mx + k - 1;  // Upper bound for the result
  FOR(i, 0, 2 * k) if (ok[i]) {
    mx = fr(mx, i);  // Find earliest moment that works for slot i
    r = fl(r, i);    // Find latest moment that works for slot i
  }
  if (mx <= r) {
    printf("%lld\n", mx);
  } else
    puts("-1");
}
signed main() {
  int T = 1;
  T = read();
  while (T--)
    work();
  flush();
  return 0;
}


// https://github.com/VaHiX/CodeForces/