// Problem: CF 1592 A - Gamer Hemose
// https://codeforces.com/contest/1592/problem/A

/*
 * Problem: A. Gamer Hemose
 * Algorithm: Greedy approach with two largest weapons
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 *
 * The agent needs to kill an enemy with H health using n weapons,
 * each with damage a_i, under the constraint that no weapon can be
 * used twice consecutively.
 *
 * Strategy:
 * 1. Find the two largest damages (x and y) among all weapons.
 * 2. Use the combination of x and y optimally to minimize moves.
 *    - If using x + y damage per cycle, we get H / (x + y) full cycles.
 *    - Remaining health H % (x + y) is handled by one move if > 0,
 *      and possibly another move if remaining > x.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, H;
    scanf("%ld %ld", &n, &H);
    long x(0), y(0); // x = max damage, y = second max damage
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      if (a >= x) {
        y = x;   // Previous max becomes second max
        x = a;   // Update max
      } else if (a >= y) {
        y = a;   // Update second max
      }
    }
    long res = 2 * (H / (x + y)); // Number of full cycles using (x,y)
    H %= (x + y);                 // Remaining health after full cycles
    res += (H > 0) + (H > x);     // Add one more move if needed
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/