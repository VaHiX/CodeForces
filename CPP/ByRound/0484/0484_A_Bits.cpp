// Problem: CF 484 A - Bits
// https://codeforces.com/contest/484/problem/A

/*
 * Problem: Find the number in range [l, r] with maximum set bits.
 *          If there are ties, return the smallest such number.
 *
 * Algorithm:
 * - Start with x = 1 (binary 1)
 * - While (l | x) <= r:
 *   - Update l = l | x (set the bit at position of x)
 *   - Shift x left by 1 bit
 * - Output the final value of l
 *
 * Time Complexity: O(log(max(l, r))) per query, since we loop through bits.
 * Space Complexity: O(1), only using constant extra space.
 */

#include <stdio.h>
int n;
int main() {
  scanf("%d", &n);
  while (n--) {
    long long l, r;
    scanf("%lld%lld", &l, &r);
    long long x = 1;
    while ((l | x) <= r) {
      l = l | x;   // Set the bit at position of x in l
      x = x << 1;  // Shift x to the left (move to next bit position)
    }
    printf("%lld\n", l);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/