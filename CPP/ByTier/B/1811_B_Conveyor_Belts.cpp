// Problem: CF 1811 B - Conveyor Belts
// https://codeforces.com/contest/1811/problem/B

/*
B. Conveyor Belts
Algorithm: The problem involves finding the minimum energy to move from one cell to another in a special n×n matrix where cells form concentric clockwise cycles. Each layer (or "ring") of the matrix has a specific distance from the center, and movement within a layer follows the direction of the conveyor belt.

Time Complexity: O(1) per test case — all operations are constant time.
Space Complexity: O(1) — only a constant amount of extra space is used.

Approach:
- For any cell (x,y), calculate its minimum distance to the center of the matrix.
  This is done by taking the minimum of:
  - Distance from x to left edge,
  - Distance from x to right edge,
  - Distance from y to top edge,
  - Distance from y to bottom edge.
- Similarly for both start and end positions.
- The difference between these distances tells us how many layers apart they are.
  If the start is further from center than end, we spend that many steps of energy
  (as we can use belt movement for free within same layer; moving through layers costs energy).
*/

#include <algorithm>
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x1, y1, x2, y2;
    scanf("%ld %ld %ld %ld %ld", &n, &x1, &y1, &x2, &y2);
    // Calculate minimum distance from center for starting cell (x1,y1)
    long start = std::min(std::min(x1, n + 1 - x1), std::min(y1, n + 1 - y1));
    // Calculate minimum distance from center for ending cell (x2,y2)
    long finish = std::min(std::min(x2, n + 1 - x2), std::min(y2, n + 1 - y2));
    // Compute the difference in layer distances
    long diff = start - finish;
    // Take absolute value to get net energy cost (can be negative if end is further)
    diff = (diff > 0) ? diff : (-diff);
    printf("%ld\n", diff);
  }
}


// https://github.com/VaHiX/codeForces/