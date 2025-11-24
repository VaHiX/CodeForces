// Problem: CF 1375 A - Sign Flipping
// https://codeforces.com/contest/1375/problem/A

/*
 * Problem: Sign Flipping
 * 
 * Purpose: Given an array of odd length integers, flip signs of some elements 
 *          such that at least half of the adjacent differences are non-negative 
 *          and at least half are non-positive.
 * 
 * Algorithm/Technique:
 *   - Greedy approach:
 *     - For even indices: keep the sign as is if the number is non-negative,
 *       else flip it.
 *     - For odd indices: keep the sign as is if the number is non-negative,
 *       else flip it.
 *   - The approach ensures that the sequence alternates between positive and 
 *     negative values, balancing the number of positive and negative differences.
 * 
 * Time Complexity: O(n) where n is the number of elements in the array.
 * Space Complexity: O(1) as we only use a constant amount of extra space.
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      // If index is odd and number is positive, flip the sign
      if (p % 2 && x > 0) {
        printf("%ld ", -x);
      } 
      // If index is even and number is negative, flip the sign
      else if (p % 2 == 0 && x < 0) {
        printf("%ld ", -x);
      } 
      // Otherwise, keep the original sign
      else {
        printf("%ld ", x);
      }
    }
    puts(""); // Print newline after each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/