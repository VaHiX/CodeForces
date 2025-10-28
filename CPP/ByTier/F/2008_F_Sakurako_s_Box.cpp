// Problem: CF 2008 F - Sakurako's Box
// https://codeforces.com/contest/2008/problem/F

/*
 * Problem: F. Sakurako's Box
 * 
 * Purpose: Calculate the expected value of the product of two randomly selected elements from an array.
 * 
 * Algorithm:
 * - The expected value of the product of two elements is:
 *   E[X*Y] = (1/n^2) * sum over all pairs (i,j) of a[i]*a[j]
 * - This can be simplified using the identity:
 *   sum of all pairs = (sum of elements)^2 - sum of squares of elements
 * - The result is then multiplied by the modular inverse of n*(n-1)/2 to get the final expected value.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the array
 * 
 * Techniques:
 * - Modular Arithmetic
 * - Fast Exponentiation (for modular inverse)
 * - Prefix Sum Technique
 */

#include <cstdio>

typedef long long i64;
namespace Input {
const int BUFFLEN = 1 << 20;
char buf[BUFFLEN | 2], *p1 = buf, *p2 = buf;
inline char getc() {
  if (p1 == p2)
    p1 = buf, p2 = buf + fread(buf, 1, BUFFLEN, stdin);
  return p1 == p2 ? EOF : *p1++;
}
inline bool isdgt(const char &op) { return op >= '0' && op <= '9'; }
inline bool isalpha(const char &op) { return op >= 'a' && op <= 'z'; }
inline bool iscapital(const char &op) { return op >= 'A' && op <= 'Z'; }
inline bool isletter(const char &op) { return isalpha(op) || iscapital(op); }
inline bool ischr(const char &op) { return isletter(op); }
long long read() {
  static long long res;
  static char op, f;
  for (f = 0, op = getc(); !isdgt(op); op = getc())
    f |= (op == '-');
  for (res = 0; isdgt(op); op = getc())
    res = res * 10 + (op ^ '0');
  return f ? -res : res;
}
int readstr(char *s) {
  static int len;
  static char op;
  do
    op = getc();
  while (!ischr(op));
  for (len = 0; ischr(op); op = getc())
    s[len++] = op;
  return len;
}
} // namespace Input
template <i64 MOD> i64 qpow(i64 x, i64 y) {
  i64 ans = 1;
  for (; y; x = x * x % MOD, y >>= 1)
    if (y & 1)
      ans = ans * x % MOD;
  return ans;
}
using Input::read;
const int N = 200010;
const i64 mod = 1e9 + 7;
int a[N], n;
void solve() {
  n = read();
  i64 ans1 = 0, ans2 = 0;
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
    ans1 = (ans1 + a[i]) % mod;
    ans2 = (ans2 + i64(a[i]) * a[i] % mod) % mod;
  }
  i64 ans = (ans1 * ans1 % mod + mod - ans2) % mod;
  i64 base = qpow<mod>((n - 1ll) * n % mod, mod - 2); // Modular inverse of n*(n-1)/2
  printf("%lld\n", ans * base % mod);
}
signed main(int argc, char **argv) {
#ifndef ONLINE_JUDGE
  freopen("order.in", "r", stdin);
  freopen("order.out", "w", stdout);
#endif
  int T = read();
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/