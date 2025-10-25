// Problem: CF 1884 A - Simple Design
// https://codeforces.com/contest/1884/problem/A

/*
 * Problem: Find the smallest k-beautiful number >= x
 * Algorithm: Brute-force search from x upward until we find a number whose digit sum is divisible by k
 * Time Complexity: O(d * log(x)) per test case, where d is the average number of digits in the range.
 *                  In worst case: up to ~10^9, so approximately 10 operations for digit sum + 10 iterations max.
 * Space Complexity: O(1)
 */

#include <cstdio>
long digsum(long x) {
  long res(0);
  while (x > 0) {
    res += x % 10; // Add last digit to the sum
    x /= 10;       // Remove last digit
  }
  return res;
}
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, k;
    scanf("%ld %ld", &x, &k);
    long res(x);
    while (digsum(x) % k) { // While digit sum is not divisible by k
      ++x;                  // Increment x until condition is met
    }
    printf("%ld\n", x);
  }
}


// https://github.com/VaHiX/codeForces/