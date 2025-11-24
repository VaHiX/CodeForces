// Problem: CF 1091 A - New Year and the Christmas Ornament
// https://codeforces.com/contest/1091/problem/A

#include <cstdio>
// Problem: A. New Year and the Christmas Ornament
// Purpose: Find the maximum number of ornaments that can be used to build a beautiful Christmas tree,
//          where the number of blue ornaments is exactly 1 more than yellow, and red is exactly 1 more than blue.
// Algorithm: Greedy approach.
// Time Complexity: O(1) - constant time operations
// Space Complexity: O(1) - only using a fixed amount of variables
int main() {
  long y, b, r;
  scanf("%ld %ld %ld", &y, &b, &r);
  // Determine the maximum possible number of yellow ornaments (y) that satisfies constraints
  y = (y < b - 1) ? y : (b - 1);
  // Further constrain y to also satisfy the red ornament constraint
  y = (y < r - 2) ? y : (r - 2);
  // Calculate total ornaments used: 
  // If y is the number of yellow ornaments, then b = y + 1 and r = y + 2,
  // so total = y + (y+1) + (y+2) = 3*y + 3
  printf("%ld\n", 3 * y + 3);
  return 0;
}

// https://github.com/VaHiX/codeForces/