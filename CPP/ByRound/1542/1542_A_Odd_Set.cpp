// Problem: CF 1542 A - Odd Set
// https://codeforces.com/contest/1542/problem/A

/*
 * Problem: A. Odd Set
 * Purpose: Determine if a multiset of 2n integers can be split into exactly n pairs
 *          such that each pair's sum is odd.
 *
 * Algorithm:
 * - For a pair to have an odd sum, one element must be even and the other odd.
 * - Therefore, in the entire set, there must be equal numbers of even and odd elements.
 * - Count the number of odd elements and check if it equals n (half of 2n).
 *
 * Time Complexity: O(2*n) = O(n) per test case, where n is the input size.
 * Space Complexity: O(1), only using a few variables for counting and processing.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0); // Counter for odd numbers
    for (long p = 0; p < 2 * n; p++) {
      long x;
      scanf("%ld", &x);
      cnt += (x % 2); // Increment if x is odd (x%2 == 1)
    }
    puts(cnt == n ? "Yes" : "No"); // If exactly n odds, we can pair them all with evens
  }
}


// https://github.com/VaHiX/codeForces/