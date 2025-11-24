// Problem: CF 1998 C - Perform Operations to Maximize Score
// https://codeforces.com/contest/1998/problem/C

/*
 * Problem: C. Perform Operations to Maximize Score
 * 
 * Purpose: Given an array `a` of length `n`, a binary array `b` of same length, and integer `k`,
 *          we can perform at most `k` operations to increase elements of `a` where `b[i] == 1`.
 *          Score is defined as maximum of (a[i] + median of array a after removing a[i]).
 *          Goal: Find the maximum possible score.
 * 
 * Algorithm:
 *   - Group elements of `a` based on `b[i]`: elements where `b[i] == 0` go to group 0, and `1` to group 1.
 *   - Sort both groups.
 *   - Try to optimize by increasing elements in group 1.
 *   - Binary search for best value to increase group 0 elements.
 *   - Compute score using median of remaining array after each element removal.
 * 
 * Time Complexity: O(n * log(n) + k * log(max_value))
 * Space Complexity: O(n)
 * 
 * Techniques:
 *   - Binary search on answer
 *   - Greedy approach with median calculations
 *   - Efficient I/O using fast input/output
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <vector>

#define pbk push_back
#define FOR(i, a, b) for (int i = a, i##i = b; i <= i##i; ++i)
#define ROF(i, a, b) for (int i = a, i##i = b; i >= i##i; --i)
using namespace std;
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
void write(int x) {
  if (x < 0)
    putchar('-'), x = -x;
  static char buf[15];
  static int len = -1;
  do
    buf[++len] = x % 10 + 48, x /= 10;
  while (x);
  while (len >= 0)
    putchar(buf[len]), --len;
  putchar(' ');
}
void flush() { fwrite(obuf, p3 - obuf, 1, stdout), exit(0); }
#undef getchar
#undef putchar
} // namespace Cirno_loves_Reimu
using namespace Cirno_loves_Reimu;
const int N = 2e6 + 9;
const ll inf = 2e9 + 7;
int n, k, a[N], b[N];
vector<int> s[2];
int chk(ll d) {
  int cnt = n - n / 2;
  ll nd = 0;
  for (int x : s[0])
    if (x >= d)
      --cnt;
  for (int x : s[1])
    if (cnt > 0) {
      if (x < d)
        nd += d - x;
      --cnt;
    }
  if (cnt > 0)
    return 0;
  return nd <= k;
}
void work() {
  n = read(), k = read();
  FOR(i, 0, 1) s[i].clear();
  FOR(i, 1, n) a[i] = read();
  FOR(i, 1, n) {
    b[i] = read();
    s[b[i]].pbk(a[i]);
  }
  FOR(i, 0, 1) sort(s[i].begin(), s[i].end());
  reverse(s[1].begin(), s[1].end());
  ll ans = 0;
  if (s[1].size()) {
    ll t = s[1][0];
    FOR(i, 1, n) if (a[i] == t) {
      a[i] = inf;
      break;
    }
    sort(a + 1, a + n + 1);
    ans = t + k + a[n / 2];
    a[n] = t;
  }
  if (s[0].size()) {
    int t = *prev(s[0].end());
    s[0].pop_back();
    ll l = 1, r = inf;
    while (l + 1 < r) {
      ll mid = (l + r) >> 1;
      if (chk(mid))
        l = mid;
      else
        r = mid;
    }
    ans = max(ans, l + t);
  }
  printf("%lld\n", ans);
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