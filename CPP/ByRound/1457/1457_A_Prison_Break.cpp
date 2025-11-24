// Problem: CF 1457 A - Prison Break
// https://codeforces.com/contest/1457/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, r, c;
    scanf("%ld %ld %ld %ld", &n, &m, &r, &c);
    // Calculate maximum distance in rows from (r,c) to any cell
    long x = (n - r > r - 1) ? (n - r) : (r - 1);
    // Calculate maximum distance in columns from (r,c) to any cell
    long y = (m - c > c - 1) ? (m - c) : (c - 1);
    printf("%ld\n", x + y);
  }
}
/*
A. Prison Break

Algorithm:
- For each test case, we need to find the minimum time for all prisoners to reach cell (r, c).
- The problem is essentially finding the maximum Manhattan distance from any cell in the matrix to cell (r, c).
- In a grid, the maximum Manhattan distance from point (r, c) to any other point occurs at one of the four corners.
- We compute the maximum row distance (from r to top or bottom) and column distance (from c to left or right).
- The result is the sum of these two maxima.

Time Complexity:
O(t), where t is the number of test cases. Each test case takes constant time O(1).

Space Complexity:
O(1), only a constant amount of extra space is used.
*/

// https://github.com/VaHiX/codeForces/