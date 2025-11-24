// Problem: CF 1943 D1 - Counting Is Fun (Easy Version)
// https://codeforces.com/contest/1943/problem/D1

/*
 * Problem: Counting Is Fun (Easy Version)
 * 
 * Purpose: Given an array of length n with elements in range [0, k], count how many
 *          "good" arrays exist, where a good array can be reduced to all zeros
 *          using specific operations: select two indices l < r and subtract 1 from
 *          all elements in range [l, r].
 *
 * Algorithm: Dynamic Programming with inclusion-exclusion principle.
 *            The key insight involves using a recurrence relation on prefix sums
 *            and leveraging convolution techniques for efficient computation.
 *            The solution computes the number of valid sequences using a 2D DP array.
 *
 * Time Complexity: O(n^2 * k)
 * Space Complexity: O(n * k)
 *
 * Techniques:
 *   - Dynamic Programming
 *   - Prefix sum optimization
 *   - Modular arithmetic
 *   - Inclusion-exclusion principle
 */

#include <ctype.h>
#include <stdio.h>
#include <iosfwd>

#define vc vector
#define pb emplace_back
#define pii pair<int, int>
#define mkp make_pair
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define lep(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
inline int read() {
  int x = 0, w = 0;
  char ch = getchar();
  while (!isdigit(ch))
    w |= (ch == '-'), ch = getchar();
  while (isdigit(ch))
    x = x * 10 + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}
const int N = 3005;
int P;
inline void inc(int &x, int y) {
  x += y - P;
  x += (x >> 31) & P;
}
inline void dec(int &x, int y) {
  x -= y;
  x += (x >> 31) & P;
}
inline int pls(int x, int y) {
  x += y - P;
  x += (x >> 31) & P;
  return x;
}
int n, m, f[N][N];
inline void testcase() {
  n = read();
  m = read();
  P = read();
  rep(i, 0, n + 1) rep(j, 0, m) f[i][j] = 0;
  f[0][0] = 1;
  for (int i = 1, sum; i <= n + 1; i++) {
    sum = 0;
    rep(j, 0, m) inc(sum, f[i - 1][j]);
    rep(j, 0, m) f[i][j] = sum;
    if (i == 1)
      continue;
    for (int j = m, k = 0, b = 0; j >= 0; j--) {
      inc(k, f[i - 2][m - j]);
      dec(b, 1ll * j * f[i - 2][m - j] % P);
      inc(f[i][j], pls(1ll * k * j % P, b));
    }
  }
  printf("%d\n", f[n + 1][0]);
}
signed main() {
  int t = read();
  while (t--)
    testcase();
  return 0;
}


// https://github.com/VaHiX/CodeForces/