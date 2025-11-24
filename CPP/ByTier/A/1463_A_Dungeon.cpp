// Problem: CF 1463 A - Dungeon
// https://codeforces.com/contest/1463/problem/A

/*
 * Problem: Dungeon
 * Algorithm/Techniques: Mathematical analysis and simulation logic
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * The game involves killing three monsters with a cannon. Regular shots deal 1 damage to one monster,
 * while every 7th shot is enhanced and deals 1 damage to all monsters.
 * To win beautifully, all monsters must be killed by the same enhanced shot.
 *
 * Key insight:
 * - Let s = a + b + c be the total health points.
 * - With each enhanced shot, all remaining monsters lose 1 health point.
 * - If all monsters die on an enhanced shot (say kth shot), then:
 *   - After (k-1) regular shots and (k//7) enhanced shots, total damage = (k-1) + (k//7)*3
 *   - Or simpler: After k-1 full cycles of 7 shots, plus k%7 regular shots to get to kth shot,
 *     which is the enhanced one.
 *
 * Simplified logic:
 * Let d = total damage needed = s.
 * If d % 9 == 0, then it's possible that each monster's health can be reduced equally by enhanced shots,
 * and (d / 9) will denote how many times the enhanced shot needs to be fired.
 * But also need to ensure (d/9) is <= a, b, c (since no monster can have negative hp).
 *
 * This approach checks:
 * - Total health s is divisible by 9.
 * - Each monster's health does not exceed total shots required.
 */

#include <stdio.h>

int t, a, b, c, s;
int main() {
  for (scanf("%d", &t); t--;) {           // Read number of test cases and loop through them
    scanf("%d%d%d", &a, &b, &c);          // Read health points of three monsters
    s = a + b + c;                       // Calculate total health points
    puts((s % 9 || s / 9 > a || s / 9 > b || s / 9 > c) ? "NO" : "YES");  // Check conditions and output result
  }
}


// https://github.com/VaHiX/codeForces/