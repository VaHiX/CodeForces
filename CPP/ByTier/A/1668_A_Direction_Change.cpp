// Problem: CF 1668 A - Direction Change
// https://codeforces.com/contest/1668/problem/A

#include <cstdio>
// Flowerbox describing the code purpose, algorithms, and complexity
/*
Problem: Minimum moves to reach from (1,1) to (n,m) in a grid with constraints:
- Can move up, down, left, right
- Cannot move in the same direction twice consecutively
- Cannot leave the grid

Algorithm: Mathematical approach based on grid dimensions
Time Complexity: O(1) per test case
Space Complexity: O(1)

Key observations:
- If n == 1 and m >= 3, it's impossible to avoid consecutive moves in same direction
- For other cases, minimum moves calculated using formula:
  2 * (max(n,m) - 1) - (n + m) % 2
*/
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    long x = (m < n) ? m : n;   // x is the smaller dimension
    long y = (m > n) ? m : n;   // y is the larger dimension
    if (x == 1 && y >= 3) {     // Special case: impossible when one dimension is 1 and other >= 3
      puts("-1");
    } else {
      printf("%ld\n", 2 * (y - 1) - (x + y) % 2);  // Compute minimum moves using derived formula
    }
  }
}

// https://github.com/VaHiX/codeForces/