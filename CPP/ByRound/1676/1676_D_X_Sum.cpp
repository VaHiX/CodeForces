// Problem: CF 1676 D - X-Sum
// https://codeforces.com/contest/1676/problem/D

/*
D. X-Sum
Purpose: Given an n×m grid of non-negative integers, find the maximum sum of cells that can be attacked by placing a bishop on any cell. A bishop attacks diagonally in all four directions (including the cell it stands on).

Algorithm:
- For each diagonal going from top-left to bottom-right, we precompute the sum of values in that diagonal (stored in map s).
- For each diagonal going from top-right to bottom-left, we precompute the sum of values in that diagonal (stored in map d).
- For every cell (i,j), compute the total sum as: s[i+j] + d[i-j] - a[i][j], and keep track of the maximum.
- This works because when placing a bishop at (i,j), it covers all cells in diagonals i+j and i-j, but we must avoid double counting the cell itself.

Time Complexity: O(n*m) per test case
Space Complexity: O(n+m) for maps s and d

Input Format:
- t: number of test cases
- n, m: dimensions of grid
- n lines with m integers each representing the grid values

Output Format:
- For each test case, a single integer representing the maximum sum achievable.
*/

#include <cstdio>
#include <map>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<std::vector<long>> f(n, std::vector<long>(m, 0));
    std::map<long, long> s, d; // s: sum of diagonals (row + col), d: sum of anti-diagonals (row - col)
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        scanf("%ld", &f[row][col]);
        s[row + col] += f[row][col];     // accumulate sum for this diagonal
        d[row - col] += f[row][col];     // accumulate sum for this anti-diagonal
      }
    }
    long res(0);
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        long cand = s[row + col] + d[row - col] - f[row][col]; // total sum minus the cell's value (it was added twice)
        res = (cand > res) ? cand : res;
      }
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/