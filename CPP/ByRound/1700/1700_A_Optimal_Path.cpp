// Problem: CF 1700 A - Optimal Path
// https://codeforces.com/contest/1700/problem/A

/*
Algorithm: Optimal Path
Techniques: Mathematical formula derivation for minimal path cost on a grid
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem involves finding the minimum cost path from (1,1) to (n,m) in an n×m grid,
where each cell (i,j) has value (i-1)*m + j. From any cell, you can only move right or down.
The optimal path always goes through all cells of the grid — there's only one valid path
from (1,1) to (n,m). 

The minimal cost is derived from summing values along any such path.
The total sum can be calculated using closed-form expression:
m * (n * n + n + m - 1) / 2

This is derived by realizing that the minimum path sum equals the sum of all elements
in the grid, and this sum has a known mathematical formula.
*/

#include <stdio.h>
int main() {
  long long t, n, m;
  for (scanf("%lld", &t); t; --t)
    scanf("%lld%lld", &n, &m), printf("%lld\n", m * (n * n + n + m - 1) / 2);
}


// https://github.com/VaHiX/codeForces/