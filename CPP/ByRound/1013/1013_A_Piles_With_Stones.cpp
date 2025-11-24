// Problem: CF 1013 A - Piles With Stones
// https://codeforces.com/contest/1013/problem/A

/*
 * Problem: A. Piles With Stones
 * Purpose: Determine if two configurations of stone piles can be transformed into each other
 *          by moving one stone at a time between piles (or taking one stone).
 * Algorithms/Techniques: Simulation, summation
 * Time Complexity: O(n), where n is the number of piles
 * Space Complexity: O(1), only using constant extra space
 *
 * The key insight is that the total number of stones remains unchanged.
 * If sum of initial configuration is less than or equal to sum of final configuration,
 * then it's possible for jury members to have moved/removed stones appropriately.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long a(0); // Sum of initial pile sizes
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    a += x; // Accumulate total stones in first configuration
  }
  long b(0); // Sum of final pile sizes
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    b += x; // Accumulate total stones in second configuration
  }
  puts(b <= a ? "Yes" : "No"); // If final sum <= initial sum, valid transformation possible
  return 0;
}


// https://github.com/VaHiX/codeForces/