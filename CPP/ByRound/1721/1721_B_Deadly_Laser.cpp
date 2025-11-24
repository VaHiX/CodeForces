// Problem: CF 1721 B - Deadly Laser
// https://codeforces.com/contest/1721/problem/B

/*
B. Deadly Laser

Purpose:
This program computes the minimum number of steps required for a robot to travel from the top-left corner (1, 1) to the bottom-right corner (n, m) of a grid, avoiding a deadly laser located at (sx, sy). The robot cannot enter any cell within distance d (Manhattan distance) of the laser.

Algorithm:
The solution uses a greedy approach to determine if there's a valid path. 
It checks two possible paths:
1. Go right then down
2. Go down then right

If either path avoids all cells within distance d from the laser, it returns the Manhattan distance (n + m - 2).
Otherwise, it's impossible and returns -1.

Time Complexity: O(1) per test case — constant time operations.
Space Complexity: O(1) — only a fixed number of variables are used.

Input Format:
- t: number of test cases
- For each test case: n m sx sy d

Output Format:
- Minimum steps to reach (n, m), or -1 if impossible.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, sx, sy, d;
    scanf("%ld %ld %ld %ld %ld", &n, &m, &sx, &sy, &d);
    
    // Calculate distances from start (1,1) to laser (sx,sy) in two directions:
    // bl: distance to left border (from start), br: distance to right border
    long bl(sx - 1), br(m - sy);
    long u = bl < br ? bl : br;  // Minimum of left and right distances

    // Calculate distances from start (1,1) to laser (sx,sy) in two directions:
    // bl: distance to bottom border (from start), br: distance to top border
    bl = n - sx;
    br = sy - 1;
    long v = bl < br ? bl : br;  // Minimum of bottom and top distances

    // Check whether either path avoids the dangerous area:
    bool res = (u > d) || v > d;
    printf("%ld\n", res ? (n + m - 2) : -1);  // Output result
  }
}


// https://github.com/VaHiX/codeForces/