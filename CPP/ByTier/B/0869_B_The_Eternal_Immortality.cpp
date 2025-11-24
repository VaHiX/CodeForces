// Problem: CF 869 B - The Eternal Immortality
// https://codeforces.com/contest/869/problem/B

#include <stdint.h>
#include <iostream>

/*
 * Problem: B. The Eternal Immortality
 *
 * Purpose: Calculate the last digit of the number of times a phoenix reincarnates
 *          in a timespan of b! years, given that it reincarnates every a! years.
 *          This is equivalent to computing (b! / a!) mod 10.
 *
 * Algorithm:
 *   - Compute the product of integers from (a+1) to b, taking modulo 10 at each step.
 *   - Since we are only interested in the last digit, we can reduce modulo 10 after
 *     each multiplication to avoid overflow.
 *   - If the result becomes 0 at any point, it will remain 0, so we can break early.
 *
 * Time Complexity: O(b - a), which is at most 10^18 in the worst case, but practically
 *                  much smaller due to early termination when d == 0.
 *
 * Space Complexity: O(1), only using a fixed number of variables.
 */

int main() {
  int64_t a, b;
  std::cin >> a >> b;
  int64_t d(1); // Initialize the result to 1
  for (int64_t p = a + 1; p <= b; p++) {
    d *= (p % 10);  // Multiply by the last digit of p
    d %= 10;        // Keep only the last digit to prevent overflow
    if (d == 0) {
      break;        // If result is 0, it will stay 0
    }
  }
  std::cout << d << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/