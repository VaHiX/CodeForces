// Problem: CF 707 C - Pythagorean Triples
// https://codeforces.com/contest/707/problem/C

/*
 * Pythagorean Triples
 * 
 * Algorithm:
 * - Given a side length 'n' of a right triangle, find two other sides 'm' and 'k' such that
 *   n^2 + m^2 = k^2 (Pythagorean triple).
 * 
 * Approach:
 * - If n <= 2, no Pythagorean triple exists (since smallest triple is (3,4,5)).
 * - If n is odd:
 *   - Use the identity: (2n+1)^2 + (2n^2 + 2n)^2 = (2n^2 + 2n + 1)^2
 *   - Let n = 2n+1 => m = 2n^2 + 2n, k = 2n^2 + 2n + 1
 * - If n is even:
 *   - Use the identity: (2n)^2 + (n^2 - 1)^2 = (n^2 + 1)^2
 *   - Let n = 2n => m = n^2 - 1, k = n^2 + 1
 * 
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - constant space usage
 */

#include <cstdio>
int main() {
  long long n;
  scanf("%lld\n", &n);
  if (n <= 2) {
    puts("-1"); // No valid Pythagorean triple for n <= 2
  } else if (n % 2) {
    // For odd n, compute m and k using derived formula
    printf("%lld %lld\n", (n * n) / 2, 1 + (n * n) / 2);
  } else {
    // For even n, compute m and k using derived formula
    printf("%lld %lld\n", (n * n) / 4 - 1, (n * n) / 4 + 1);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/