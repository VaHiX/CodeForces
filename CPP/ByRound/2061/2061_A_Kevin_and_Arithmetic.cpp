// Problem: CF 2061 A - Kevin and Arithmetic
// https://codeforces.com/contest/2061/problem/A

/*
 * Problem: Kevin and Arithmetic
 * Algorithm: Greedy approach to maximize points by arranging numbers optimally.
 *            A point is earned when the cumulative sum becomes even and then divided by 2 until odd.
 *            Strategy:
 *              - Count total odd and even numbers.
 *              - If there are no evens, no points can be earned.
 *              - Otherwise, we can earn points if we start with an odd number,
 *                and every time the sum becomes even we score a point.
 *              - To maximize points, we should arrange all odds first, then all evens
 *                (or vice versa), ensuring that as many operations as possible result in even sums.
 *
 * Time Complexity: O(n) per test case, where n is the size of input array.
 * Space Complexity: O(1), only using a few variables for counting and processing.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long odds(0), evens(0); // Count of odd and even numbers
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      x %= 2;           // Convert to 0 if even, 1 if odd
      odds += x;        // Increment odd count
      evens += (1 - x); // Increment even count
    }
    // If there are no even numbers, no points can be earned (return -1)
    // Otherwise, at least one point is earned because we can make the sum even
    printf("%ld\n", odds + (evens ? 1 : -1));
  }
}


// https://github.com/VaHiX/codeForces/