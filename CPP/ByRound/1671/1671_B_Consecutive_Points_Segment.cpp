// Problem: CF 1671 B - Consecutive Points Segment
// https://codeforces.com/contest/1671/problem/B

/*
B. Consecutive Points Segment
Algorithm: Greedy approach to check if points can form a consecutive segment after at most one move per point.
Time Complexity: O(n) per test case, where n is the number of points.
Space Complexity: O(1), only using a few variables.

For each test case:
- We are given n points in strictly increasing order.
- Each point can be moved at most once by 1 unit (left or right).
- Goal: Determine if we can make the points form a consecutive sequence [l, l+1, ..., l+n-1].

Approach:
- For a valid consecutive segment starting at some value l:
  - First point must be in range [l-1, l+1]
  - Last point must be in range [l+n-2, l+n]

We iterate through all possible starting values of such segments,
but since we only care about last point being within feasible bounds,
we simulate by tracking the final value and checking if it fits.

- For each test case:
  - Read n points.
  - Read first point x.
  - Initialize y = x.
  - Loop from second to nth point:
    - Read next point as y.
  - Check: is y <= x + n + 1?
    - If yes, it means last point can fit in the range for valid segment.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x;
    scanf("%ld", &x);
    long y(x); // Initialize y with value of first point
    for (long p = 1; p < n; p++) {
      scanf("%ld", &y); // Read and update y to last point in the sequence
    }
    puts(y <= x + n + 1 ? "YES" : "NO"); // Decide based on last point vs first point's max possible position
  }
}


// https://github.com/VaHiX/codeForces/