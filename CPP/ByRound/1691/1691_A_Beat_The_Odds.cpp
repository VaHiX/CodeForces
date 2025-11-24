// Problem: CF 1691 A - Beat The Odds
// https://codeforces.com/contest/1691/problem/A

/*
 * Problem: Beat The Odds
 * Algorithm: Greedy approach based on parity (odd/even)
 * Time Complexity: O(n) where n is the total number of elements across all test cases
 * Space Complexity: O(1) - only using a constant amount of extra space
 *
 * Approach:
 * For the sum of two numbers to be even, they must both be odd or both be even.
 * So we need to ensure that no two consecutive elements in the resulting sequence have different parities.
 * This means we can either:
 *   1. Keep all odd numbers and remove all even numbers (or vice versa)
 *   2. Count how many odd and even numbers there are
 *   3. Remove the smaller count to make all remaining elements of same parity
 *
 * In this implementation:
 *   - We count odd and even numbers in each sequence
 *   - We remove the smaller count (as it's optimal to keep the majority)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a(0), b(0); // a = count of odd numbers, b = count of even numbers
    while (n--) {
      long x;
      scanf("%ld", &x);
      (x % 2) ? (++a) : (++b); // increment a if odd, b if even
    }
    printf("%ld\n", a < b ? a : b); // remove the smaller count
  }
}


// https://github.com/VaHiX/codeForces/