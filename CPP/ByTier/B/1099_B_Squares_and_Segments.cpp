// Problem: CF 1099 B - Squares and Segments
// https://codeforces.com/contest/1099/problem/B

/*
B. Squares and Segments
Purpose: Given n unit squares to be drawn on a grid, determine the minimum number of segments that must be measured directly with a ruler (not guided by existing segments).
Algorithm: The problem reduces to finding how many unique segments are needed when placing n unit squares optimally.
Time Complexity: O(1) - constant time calculation using square root and conditional checks.
Space Complexity: O(1) - only a few variables used.

Approach:
- To place n unit squares optimally, arrange them in a grid pattern.
- The minimal number of unique segments needed for n squares follows a pattern based on the side length of the rectangle formed.
- Let s = floor(sqrt(n)), then we check different cases based on how many squares can be placed within s x s, s x (s+1), or (s+1) x (s+1) grids.
- The result depends on which grid dimension can fit n squares and whether additional segments are needed.

Examples:
Input: 1 → Output: 2
Input: 2 → Output: 3  
Input: 4 → Output: 4
*/

#include <cmath>
#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long s = sqrt(n);  // Compute integer square root of n
  long ans(0);
  if (s * s >= n) {
    ans = 2 * s;  // If s x s grid fits all squares
  } else if (s * (s + 1) >= n) {
    ans = 2 * s + 1;  // If s x (s+1) grid is sufficient
  } else if ((s + 1) * (s + 1) >= n) {
    ans = 2 * s + 2;  // If (s+1) x (s+1) grid is needed
  }
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/