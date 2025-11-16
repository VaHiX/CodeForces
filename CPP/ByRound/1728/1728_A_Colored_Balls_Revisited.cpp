// Problem: CF 1728 A - Colored Balls: Revisited
// https://codeforces.com/contest/1728/problem/A

/*
 * Problem: Colored Balls: Revisited
 * 
 * Algorithm/Technique: Greedy approach
 * 
 * Time Complexity: O(n) per test case, where n is the number of colors.
 * Space Complexity: O(1), only using a few variables for computation.
 * 
 * The key insight is that in each move, we remove two balls of different colors.
 * Since the total number of balls is odd, at the end there will be exactly one ball left.
 * The color of that ball will be the one with the maximum count, since we can only pair up
 * balls from different colors, and the color with the most balls will be the last one remaining.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mx(0), ans(0); // mx stores maximum count, ans stores the color with max count
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      if (x > mx) {
        mx = x;     // Update maximum count
        ans = p;    // Update the color that has the maximum count
      }
    }
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/