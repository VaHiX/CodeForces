// Problem: CF 1054 A - Elevator or Stairs?
// https://codeforces.com/contest/1054/problem/A

/*
 * Problem: A. Elevator or Stairs?
 * Purpose: Determine whether Masha should take the stairs or the elevator to reach Egor's floor.
 * Algorithm: 
 *   - Calculate time for stairs: |x - y| * t1
 *   - Calculate time for elevator:
 *     1. Time to reach x from z: |z - x| * t2
 *     2. Door opening time: t3
 *     3. Door closing time: t3
 *     4. Time to travel from x to y: |x - y| * t2
 *     5. Door opening time: t3
 *   - Compare times and output "YES" if elevator is faster or equal, otherwise "NO"
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long x, y, z, t1, t2, t3;
  scanf("%ld %ld %ld %ld %ld %ld", &x, &y, &z, &t1, &t2, &t3);
  
  // Time to walk stairs from x to y
  long a = (x - y) * t1;
  if (a < 0) {
    a = -a; // Ensure non-negative time
  }
  
  // Time for elevator to get to x floor (from z)
  long b = (z - x) * t2;
  if (b < 0) {
    b = -b; // Ensure non-negative time
  }
  
  // Time for elevator to travel from x to y
  long c = (x - y) * t2;
  if (c < 0) {
    c = -c; // Ensure non-negative time
  }
  
  // Total elevator time: travel from z to x, open doors, close doors, 
  // travel from x to y, open doors again
  long d = b + t3 + t3 + c + t3; // Simplified as b + c + 3 * t3
  puts((d <= a) ? "YES" : "NO"); // Output YES if elevator is faster or same
  return 0;
}


// https://github.com/VaHiX/codeForces/