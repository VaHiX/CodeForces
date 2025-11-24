// Problem: CF 575 D - Tablecity
// https://codeforces.com/contest/575/problem/D

/*
Code Purpose:
This code provides a strategy for Albert, the Chief of Police in Tablecity, to guarantee catching the thief within 2015 hours.
The thief moves on a 1000x2 grid, and each hour he can move to one of six adjacent districts.
Albert can investigate exactly two districts per hour.
The algorithm guarantees that no matter where the thief starts or how he moves, he will be caught within 2015 hours.

Algorithms/Techniques:
- Strategic coverage of the grid using a two-phase approach:
  1. First phase: Investigate all districts (x,1) and (x,2) for x in [1, 1000] in increasing order.
  2. Second phase: Investigate all districts (x,1) and (x,2) for x in [1000, 1] in decreasing order.
- This ensures that any path the thief can take is covered, as the thief's movement is constrained within the grid and the investigation covers all possible positions.

Time Complexity: O(1) - The number of operations is fixed (2000), independent of input size.
Space Complexity: O(1) - Only a constant amount of memory is used for variables.

*/

#include <cstdio>
int main() {
  const int n = 1000;
  printf("%d\n", 2 * n); // Total hours needed: 2 * 1000 = 2000
  for (int p = 1; p <= n; p++) {
    printf("%d 1 %d 2\n", p, p); // First phase: check (p,1) and (p,2) in increasing order
  }
  for (int p = n; p >= 1; p--) {
    printf("%d 1 %d 2\n", p, p); // Second phase: check (p,1) and (p,2) in decreasing order
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/