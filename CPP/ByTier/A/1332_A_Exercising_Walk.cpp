// Problem: CF 1332 A - Exercising Walk
// https://codeforces.com/contest/1332/problem/A

/*
 * Problem: A. Exercising Walk
 * Purpose: Determine if a cat can perform a series of moves within given bounds.
 * Algorithms/Techniques:
 *   - Simulation with boundary checks
 *   - Greedy approach to check feasibility of movement
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 * 
 * The solution computes the net displacement in x and y directions, then verifies
 * whether all possible positions during movement stay within the bounds.
 * Special care is taken for cases where there's no horizontal/vertical movement allowed,
 * which could lead to invalid paths if the start position already exceeds bounds.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    long x, y, x1, y1, x2, y2;
    scanf("%ld %ld %ld %ld %ld %ld", &x, &y, &x1, &y1, &x2, &y2);
    bool ans(true);
    
    // Calculate final position after all moves
    x += (b - a);  // Net horizontal displacement
    if (x < x1 || x > x2) {
      ans = false;
    }
    
    // Check for impossible situation: no horizontal movement but must stay in place
    if (a == b && x1 == x2 && a > 0) {
      ans = false;
    }
    
    y += (d - c);  // Net vertical displacement
    if (y < y1 || y > y2) {
      ans = false;
    }
    
    // Check for impossible situation: no vertical movement but must stay in place
    if (c == d && y1 == y2 && c > 0) {
      ans = false;
    }
    
    puts(ans ? "Yes" : "No");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/