// Problem: CF 1951 G - Clacking Balls
// https://codeforces.com/contest/1951/problem/G

/*
Algorithm: 
- The problem simulates a process where balls move around baskets in a circle, and when a ball moves to a basket that already contains a ball, the latter is removed.
- The expected number of operations can be computed using linearity of expectation.
- The key idea is to compute contributions from gaps between balls.
- We calculate expected time for transitions from one gap to the next, using combinatorics and modular arithmetic.

Time Complexity: O(n * log(m)) - dominated by sorting and modular exponentiation
Space Complexity: O(n) - for storing the positions of balls

Techniques Used:
- Modular arithmetic with precomputed inverses
- Sorting and gap analysis
- Linearity of expectation
- Combinatorial counting using combinations
*/

#include <stdio.h>
#include <algorithm>

#define FIO(file)                                                              \
  freopen(file ".in", "r", stdin), freopen(file ".out", "w", stdout)
using namespace std;
const int N = 3e5 + 5;
const int mod = 1e9 + 7;
const int iv2 = 500000004;
const int iv3 = 333333336;
static char buf[1000000], *p1 = buf, *p2 = buf;
#define getchar()                                                              \
  p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2)      \
      ? EOF                                                                    \
      : *p1++
inline int wrd() {
  int x = 0, f = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-')
      f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = (x << 3) + (x << 1) + c - 48;
    c = getchar();
  }
  return x * f;
}
inline void write(int x) {
  static char buf[20];
  static int len = -1;
  if (x < 0)
    putchar('-'), x = -x;
  do
    buf[++len] = x % 10, x /= 10;
  while (x);
  while (len >= 0)
    putchar(buf[len--] + 48);
}
int n, m, a[N];
void ad(int &a, int b) { (a += b) >= mod && (a -= mod); }
int qpow(int a, int b) {
  int as = 1;
  while (b) {
    if (b & 1)
      as = 1ll * as * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return as;
}
int C3(int n) {
  if (n < 3)
    return 0;
  return 1ll * n * (n - 1) % mod * (n - 2) % mod * iv2 % mod * iv3 % mod;
}
int f(int n, int im, int x) {
  return mod - 1ll * n * im % mod * C3(x + 1) % mod;
}
void solve() {
  n = wrd(), m = wrd();
  int im = qpow(m, mod - 2);
  for (int i = 1; i <= n; ++i)
    a[i] = wrd();
  sort(a + 1, a + n + 1);
  int s(0), t(0);
  for (int i = 2; i <= n; ++i)
    ad(s, f(n, im, a[i] - a[i - 1]));
  ad(s, f(n, im, a[1] - a[n] + m));
  t = f(n, im, m);
  write((s - t + mod) % mod), puts("");
}
signed main() {
  int T = wrd();
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/