// Problem: CF 2039 C2 - Shohag Loves XOR (Hard Version)
// https://codeforces.com/contest/2039/problem/C2

/*
C2. Shohag Loves XOR (Hard Version)
Algorithms/Techniques: Mathematical analysis, bitwise operations, modular arithmetic
Time Complexity: O(x + log m) per test case
Space Complexity: O(1)

Given x and m, count integers 1 <= y <= m such that (x ^ y) is divisible by either x, y, or both.
The solution uses mathematical properties of XOR and divisibility to efficiently compute the result:
- For each y in range [1, m], check if (x ^ y) % x == 0 or (x ^ y) % y == 0 or both.
- Optimized using loop unrolling and precomputed checks for small values.
*/

#include <algorithm>
#include <stdio.h>
using namespace std;
typedef long long LL;
int t;
int x;
LL m;
void solve() {
  scanf("%d%lld", &x, &m);
  LL ans = m / x - 1, a = m / x * x, b = a + x;  // Precompute bounds for efficient checking
  ans += ((x ^ a) <= m) + ((x ^ b) <= m);        // Check boundary cases
  for (int i = 1; i <= min(x - 1LL, m); i++)     // Loop for small y values
    ans += (x ^ i) % i == 0;                      // Count valid y in range [1, min(x-1, m)]
  printf("%lld\n", ans);
}
int main() {
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/