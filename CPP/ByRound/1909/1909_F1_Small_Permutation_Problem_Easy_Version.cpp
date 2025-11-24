// Problem: CF 1909 F1 - Small Permutation Problem (Easy Version)
// https://codeforces.com/contest/1909/problem/F1

/*
Algorithm: Dynamic Programming with Pattern Recognition
Time Complexity: O(n) per test case
Space Complexity: O(n) for the array f and auxiliary arrays

The solution uses dynamic programming to count valid permutations. 
The key insight is to analyze how the a[i] values change as we build the permutation.
We maintain a DP array f[i] where f[i] represents the number of valid ways to place 
the first i elements of the permutation according to the given constraints.

The transitions depend on the difference between a[i] and a[i-1]:
- If a[i] == a[i-1]: f[i] = f[i-1] (no change in count of elements <= i)
- If a[i] == a[i-1] + 1: f[i] = f[i-1] * (2*i - 1 - 2*a[i-1]) (multiply by number of positions where next element can be inserted)
- If a[i] == a[i-1] + 2: f[i] = f[i-1] * (i-1-a[i-1])^2 (multiply by square of number of positions where next elements can be inserted)

This approach recognizes that in a valid permutation, once we know the number of elements <= i-1 at step i-1,
we can compute how many choices we have at step i based on a[i] and a[i-1].
*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#define LL long long
#define uint unsigned
#define LLL __int128_t
#define ldb long double
#define uLL unsigned long long
using namespace std;
char wS[262144], rdc[262144], *rS, *rT, *wT = wS;
#define gc()                                                                   \
  (rS == rT               ? rT = rdc + fread(rS = rdc, 1, 262144, stdin),      \
   rS == rT ? EOF : *rS++ : *rS++)
#define flush() fwrite(wS, 1, wT - wS, stdout), wT = wS
inline void pc(const char &x) {
  *wT++ = x;
  if (__builtin_expect(wS + 262144 == wT, 0))
    flush();
}
template <class T = int> inline T read() {
  T x(0);
  char c;
  bool f(1);
  while (!isdigit(c = gc()))
    if (c == 45)
      f = !f;
  if (f)
    do
      x = x * 10 + (c & 15);
    while (isdigit(c = gc()));
  else
    do
      x = x * 10 - (c & 15);
    while (isdigit(c = gc()));
  return x;
}
template <> inline char read() {
  char c;
  while ((c = gc()) < 33)
    ;
  return c;
}
template <> inline string read() {
  char c;
  string s;
  while ((c = gc()) < 33)
    ;
  do
    s += c;
  while ((c = gc()) > 32);
  return s;
}
inline int read(char *const s) {
  char c, *t = s;
  while ((c = gc()) < 33)
    ;
  do
    *t++ = c;
  while ((c = gc()) > 32);
  return *t = 0, t - s;
}
template <class T> inline void write(T x) {
  int wtop = 0;
  char wbuf[numeric_limits<T>::digits10 + 1];
  if (x >= 0)
    do
      wbuf[wtop++] = (x % 10) | 48;
    while (x /= 10);
  else {
    pc(45);
    do
      wbuf[wtop++] = -(x % 10) | 48;
    while (x /= 10);
  }
  for (; wtop; pc(wbuf[--wtop]))
    ;
}
template <> inline void write(char x) { pc(x); }
template <> inline void write(char *s) {
  for (; *s; pc(*s++))
    ;
}
template <> inline void write(const char *s) {
  for (; *s; pc(*s++))
    ;
}
template <> inline void write(string s) {
  for (auto c : s)
    pc(c);
}
template <class T, class... U> inline void write(const T &x, const U &...y) {
  write(x), write(y...);
}
inline LL mul(LL x, LL y, LL Mod) {
  LL r = x * y - Mod * (LL)(1.L / Mod * x * y);
  return r - Mod * (r >= Mod) + Mod * (r < 0);
}
inline LL qpow(LL x, LL y, LL Mod) {
  LL res = 1;
  for (; y; y >>= 1, x = mul(x, x, Mod))
    if (y & 1)
      res = mul(res, x, Mod);
  return res;
}
class MillerRabin {
private:
  const int pr[7] = {2, 325, 9375, 28178, 450775, 9780797, 101312313};

public:
  inline bool isprime(const LL &x) {
    if (x < 3 || x % 2 == 0)
      return x == 2;
    int r = __lg((x - 1) & -(x - 1));
    LL k = x >> r, p, v;
    for (int T = 7, j; T--;)
      if ((p = pr[T]) % x && (v = qpow(p, k, x)) != 1) {
        for (j = 1; j <= r; ++j, v = mul(v, v, x))
          if (v == x - 1)
            break;
        if (j > r)
          return 0;
      }
    return 1;
  }
} MR;
class PollardRho {
private:
  inline LL calc(const LL &n) {
    if (!(n & 1))
      return 2;
    LL x = 0, y = 0, z = 0, p = 1, q, g;
    for (int i = 0; (i & 255) || (g = __gcd(p, n)) == 1; ++i,
             x = mul(x, x, n) + 1, y = mul(y, y, n) + 1, y = mul(y, y, n) + 1) {
      if (x == y)
        x = z++, y = mul(x, x, n) + 1;
      if (q = mul(p, x - y + n, n))
        p = q;
    }
    return g;
  }

public:
  inline vector<LL> split(const LL &n) {
    if (n == 1)
      return {};
    if (MR.isprime(n))
      return {n};
    LL d = calc(n);
    while (d == 1 || d == n)
      d = calc(n);
    vector<LL> v1 = split(d), v2 = split(n / d), v3(v1.size() + v2.size());
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
    return v3;
  }
} PR;
const int N = 2e5 + 5, Mod = 998244353;
const LL INF = 1e18 + 7;
int a[N], f[N];
inline void MAIN() {
  int n = read();
  f[0] = 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
    if (!f[i - 1] || a[i] < a[i - 1] || a[i] > a[i - 1] + 2)
      f[i] = 0;
    else if (a[i] == a[i - 1])
      f[i] = f[i - 1];
    else if (a[i] == a[i - 1] + 1)
      f[i] = (LL)f[i - 1] * (i * 2 - a[i - 1] * 2 - 1) % Mod;
    else
      f[i] = (LL)f[i - 1] * (i - 1 - a[i - 1]) % Mod * (i - 1 - a[i - 1]) % Mod;
  }
  if (a[n] != n)
    f[n] = 0;
  write(f[n], '\n');
}
signed main() {
  cin.tie(0)->sync_with_stdio(0);
#define LOCAL
#ifndef LOCAL
  freopen(".in", "r", stdin);
  freopen(".out", "w", stdout);
#endif
  for (int T = read(); T--; MAIN())
    ;
  return flush(), 0;
}


// https://github.com/VaHiX/CodeForces/