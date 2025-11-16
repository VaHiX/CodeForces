// Problem: CF 1030 B - Vasya and Cornfield
// https://codeforces.com/contest/1030/problem/B

#include <cstdio>
// Problem: Vasya and Cornfield
// Description: Determine if grasshoppers are inside a specific polygonal cornfield defined by parameters n and d.
// The cornfield is a rectangle with vertices at (0, d), (d, 0), (n, n - d), and (n - d, n).
// Algorithm: Check if point (x, y) satisfies four linear inequalities derived from the polygon boundaries.
// Time Complexity: O(m) where m is the number of grasshoppers
// Space Complexity: O(1)
int main() {
  long n, d;
  scanf("%ld %ld", &n, &d);
  long m;
  scanf("%ld", &m);
  while (m--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    // Check if point (x, y) is inside or on the border of the cornfield
    // Four conditions represent the four boundaries of the polygon:
    // 1. x + y >= d: above line from (0,d) to (n,n-d)
    // 2. x + y <= 2*n - d: below line from (d,0) to (n-d,n)
    // 3. y - x >= -d: above line from (0,d) to (d,0)
    // 4. y - x <= d: below line from (n-d,n) to (n,n-d)
    puts(((x + y >= d) && (x + y <= 2 * n - d) && (y - x >= -d) && (y - x <= d))
             ? "YES"
             : "NO");
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/