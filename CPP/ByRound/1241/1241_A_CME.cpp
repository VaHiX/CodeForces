// Problem: CF 1241 A - CME
// https://codeforces.com/contest/1241/problem/A

/*
 * Problem: CME - Correct Match Equation
 * 
 * Task: Given n matches, determine the minimum number of additional matches
 *       needed to form a valid equation a + b = c where all values are positive.
 * 
 * Algorithm:
 * - A valid equation uses exactly a + b + c matchsticks (sum of lengths).
 * - Minimum matches needed for any valid CME is 5: 1+2=3
 * - For n matches, we need to form an equation such that total match count
 *   equals n and all values are positive integers.
 * 
 * Observation:
 * - If n <= 4: We can't form a valid CME using all matches, need to buy matches.
 * - For n > 4: 
 *   - If n is odd, we can construct a CME with 1 extra match
 *   - If n is even, we can construct a CME with 0 extra matches
 * 
 * Time Complexity: O(q), where q is number of queries
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    long n;
    scanf("%ld", &n);
    if (n <= 4) {
      // For small n, we can't form a CME with exactly n matches
      // We need to buy 4 - n matches for cases where n < 4 
      // For n = 4, we need to buy 0 matches (we already have enough for 1+1=2)
      printf("%ld\n", 4 - n);
    } else {
      // For larger n, check if it's odd or even
      // Odd n: 1 extra match needed to make a valid CME
      // Even n: no extra matches needed
      puts(n % 2 ? "1" : "0");
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/