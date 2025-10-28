// Problem: CF 1064 B - Equations of Mathematical Magic
// https://codeforces.com/contest/1064/problem/B

/*
 * Problem: Equations of Mathematical Magic
 * Algorithm: Bit manipulation and pattern observation
 * Description: Given equation a - (a ^ x) - x = 0, find number of non-negative solutions for x.
 *              This simplifies to a ^ x = a - x.
 *              Through analysis, it turns out that the number of valid x values is 2^(number of set bits in a).
 * Time Complexity: O(log a) per test case due to bit manipulation loop
 * Space Complexity: O(1)
 */

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll a;
    scanf("%lld", &a);
    ll res(1);  // Initialize result to 1
    while (a > 0) {
      if (a & 1) {  // If the least significant bit is 1
        res *= 2;   // Multiply result by 2 for each set bit
      }
      a /= 2;  // Right shift a by 1 bit
    }
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/