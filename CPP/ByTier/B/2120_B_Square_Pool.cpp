// Problem: CF 2120 B - Square Pool
// https://codeforces.com/contest/2120/problem/B

/*
B. Square Pool

Purpose:
This program determines how many balls out of n placed on a square pool table
will fall into one of the four corners (pockets) after being shot at 45-degree angles.
Each ball has an initial position and a direction vector (+1 or -1 for both x and y axes).
The pool table is of side length s, with pockets at (0,0), (0,s), (s,0), and (s,s).

Algorithms/Techniques:
- Simulation of ball trajectories in a 2D grid
- Determining if a ball reaches a pocket by checking coordinate sums or differences

Time Complexity: O(n) per test case, where n is the number of balls.
Space Complexity: O(1), only using a constant amount of extra space.

Input Format:
- First line contains t (number of test cases)
- For each test case:
  - Line 1: n s (balls count and table side length)
  - Next n lines: dx dy x y (direction vector and initial position)

Output Format:
- For each test case, print the number of balls that reach a pocket.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, s;
    scanf("%ld %ld", &n, &s);
    long total(0); // Counter for balls that fall into pockets
    for (long p = 0; p < n; p++) {
      long dx, dy, x, y;
      scanf("%ld %ld %ld %ld", &dx, &dy, &x, &y);
      if (dx == dy) {
        // Ball moves diagonally towards a corner where x + y = s or x + y = 0
        // Since x,y are positive and < s, we only care about x + y == s for pocket (s,s)
        total += (x == y); 
      } else {
        // Ball moves in mixed directions (one axis changes sign)
        // It will reach a pocket if x + y == s (for top-right or bottom-left pockets)
        total += (x + y == s);
      }
    }
    printf("%ld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/