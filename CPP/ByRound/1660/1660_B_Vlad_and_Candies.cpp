// Problem: CF 1660 B - Vlad and Candies
// https://codeforces.com/contest/1660/problem/B

/*
 * Problem: Vlad and Candies
 * 
 * Purpose: Determine if it's possible to eat all candies such that no two 
 *          candies of the same type are eaten consecutively. At each step, 
 *          Vlad chooses to eat from the most frequent remaining candy type.
 *
 * Algorithm:
 *   - For each test case, find the maximum and second maximum counts of candies.
 *   - If the maximum count is greater than the second maximum plus one,
 *     it's impossible to interleave them without having two same types in a row.
 *   - Time Complexity: O(n) per test case, where n is the number of candy types.
 *   - Space Complexity: O(1), only using constant extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mxa(0), mxb(0); // mxa = max count, mxb = second max count
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x >= mxa) { // If x is greater than or equal to current max
        mxb = mxa;    // Move old max to second max
        mxa = x;      // Update max
      } else if (x > mxb) { // If x is greater than second max but not max
        mxb = x;      // Update second max
      }
    }
    puts(mxa <= mxb + 1 ? "YES" : "NO"); // Check condition for valid interleaving
  }
}


// https://github.com/VaHiX/codeForces/