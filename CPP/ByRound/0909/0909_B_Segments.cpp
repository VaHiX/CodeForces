// Problem: CF 909 B - Segments
// https://codeforces.com/contest/909/problem/B

/*
Code purpose: This program calculates the minimum number of layers required to draw all possible segments on a coordinate axis with integer endpoints from 0 to N, such that no segments overlap within the same layer.

Algorithm: The problem is solved by recognizing a pattern based on the mathematical properties of segment arrangements. For n segments, we need to determine the optimal layering strategy.

Time Complexity: O(1) - The solution performs constant time operations regardless of input size.
Space Complexity: O(1) - Only a constant amount of extra space is used.

The approach uses mathematical formulas derived from observing the optimal arrangement:
- For odd N: result = (N+1)²/4
- For even N: result = (N/2) * (N/2 + 1)
*/
#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  if (n % 2) { // Check if n is odd
    printf("%ld\n", (n + 1) * (n + 1) / 4); // Formula for odd case
  } else {
    printf("%ld\n", (n / 2) * (n / 2 + 1)); // Formula for even case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/