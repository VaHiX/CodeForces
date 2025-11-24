// Problem: CF 1931 G - One-Dimensional Puzzle
// https://codeforces.com/contest/1931/problem/G

/*
 * Problem: One-Dimensional Puzzle
 * 
 * Algorithm/Techniques:
 * - Combinatorics with inclusion-exclusion and modular arithmetic
 * - Precomputed factorials for efficient combination calculations
 * - Fast exponentiation for modular inverse
 * 
 * Time Complexity: O(n) per test case where n = max(c1, c2, c3, c4), due to precomputation and
 *                  constant time operations per test.
 * Space Complexity: O(n) for storing precomputed factorials.
 *
 * The solution models the puzzle as arranging elements in a chain such that
 * consecutive elements are compatible (i.e., left connection of right element
 * is the opposite of right connection of left element). There are 4 types of
 * elements with different connection types. The problem reduces to counting valid
 * sequences based on how many elements of each type are available.
 */

#include <stdlib.h>
#include <algorithm>
#include <cstdio>

using namespace std;
using LL = long long;
int T, a, b, c, d, fac[2000006];
#define mo 998244353

// Fast exponentiation to compute modular inverse
LL quick_power(LL x, LL y) {
  LL res = 1, base = x;
  while (y) {
    if (y & 1)
      res = res * base % mo;
    base = base * base % mo;
    y >>= 1;
  }
  return res;
}

// Computes combination C(n + t - 1, n) using precomputed factorials
LL solve(int n, int t) {
  return (LL)fac[n + t - 1] *
         quick_power((LL)fac[n] * fac[t - 1] % mo, mo - 2) % mo;
}

int main() {
  scanf("%d", &T);
  fac[0] = 1;
  // Precompute factorials modulo 998244353
  for (int i = 1; i <= 2000000; i++) {
    fac[i] = (LL)fac[i - 1] * i % mo;
  }
  while (T--) {
    scanf("%d%d%d%d", &a, &b, &c, &d);
    LL ans = 0;
    // If difference in counts of types 1 and 2 exceeds 1, impossible to arrange
    if (abs(a - b) > 1) {
      ans = 0;
    } else if (a == b) {
      // If a and b are both zero, check if c or d are non-zero
      if (a == 0 && b == 0) {
        if (c > 0 && d > 0)
          ans = 0;  // Impossible if both c and d are present
        else
          ans = 1;  // Only one way if either c or d is zero
      } else {
        // Two ways to interleave sequences: (start with c then d) or (start with d then c)
        ans = solve(c, a) * solve(d, a + 1) % mo;
        ans = (ans + solve(c, a + 1) * solve(d, a)) % mo;
      }
    } else
      // Otherwise, alternate between two types in a valid way
      ans = solve(c, max(a, b)) * solve(d, max(a, b)) % mo;
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/