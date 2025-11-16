// Problem: CF 1787 C - Remove the Bracket
// https://codeforces.com/contest/1787/problem/C

/*
Problem: Remove the Bracket
Algorithm: Dynamic Programming
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves choosing pairs (x_i, y_i) for elements a_2 to a_{n-1} such that:
- x_i + y_i = a_i
- (x_i - s) * (y_i - s) >= 0

We want to minimize the sum:
F = a_1 * x_2 + y_2 * x_3 + y_3 * x_4 + ... + y_{n-2} * x_{n-1} + y_{n-1} * a_n

Approach:
We use dynamic programming where f[i][0] represents the minimum cost up to index i when choosing x_i,
and f[i][1] represents the minimum cost when choosing y_i.
The recurrence relation considers two transitions:
1. From previous x to current x (x_i-1 * x_i)
2. From previous y to current x (y_i-1 * x_i)
And similarly for y transitions.
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
#define I inline int
#define V inline void
#define ll long long int
#define isnum(ch) ('0' <= ch && ch <= '9')
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define ROF(i, a, b) for (int i = a; i >= b; i--)
#define REP(u) for (int i = h[u], v; v = e[i].t, i; i = e[i].n)
#define gc                                                                     \
  (_op == _ed &&                                                               \
           (_ed = (_op = _buf) + fread(_buf, 1, 100000, stdin), _op == _ed)    \
       ? EOF                                                                   \
       : *_op++)
char _buf[100000], *_op(_buf), *_ed(_buf);
I getint() {
  int _s = 0, _f = 1;
  char _ch = gc;
  while (!isnum(_ch))
    (_ch == '-') && (_f = -1), _ch = gc;
  while (isnum(_ch))
    _s = _s * 10 + _ch - 48, _ch = gc;
  return _s * _f;
}
const int N = 2e5 + 1, mod = 998244353;
V check(int &x) { x -= mod, x += x >> 31 & mod; }
V cmax(int &x, int y) {
  if (x - y >> 31)
    x = y;
}
V cmin(int &x, int y) {
  if (y - x >> 31)
    x = y;
}
ll f[N][2];
int T, n, a[N], x[N], y[N], tot;
V input() {
  int s;
  n = getint(), s = getint();
  FOR(i, 1, n) a[i] = getint();
  ll ans = 0;
  FOR(i, 1, n)
  if (a[i] <= s)
    x[i] = a[i], y[i] = 0;
  else
    x[i] = s, y[i] = a[i] - s;
  x[1] = y[1] = a[1];
  x[n] = y[n] = a[n];
  FOR(i, 1, n) {
    f[i][0] = min(f[i - 1][1] + 1ll * x[i - 1] * x[i],
                  f[i - 1][0] + 1ll * y[i - 1] * x[i]);
    f[i][1] = min(f[i - 1][1] + 1ll * x[i - 1] * y[i],
                  f[i - 1][0] + 1ll * y[i - 1] * y[i]);
  }
  cout << min(f[n][0], f[n][1]) << '\n';
}
V init() {}
V work() {}
int main() {
  for (scanf("%d", &T); T--;) {
    input();
    init();
    work();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/