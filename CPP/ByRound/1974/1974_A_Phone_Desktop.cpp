// Problem: CF 1974 A - Phone Desktop
// https://codeforces.com/contest/1974/problem/A

/*
 * Problem: Phone Desktop
 * 
 * Purpose:
 *   Given x 1x1 icons and y 2x2 icons, place them on minimum number of 5x3 screens.
 *   Each screen has 15 cells. 2x2 icons take 4 cells; 1x1 icons take 1 cell.
 *
 * Algorithms/Techniques:
 *   Greedy approach to minimize screen usage by placing 2x2 icons first (more efficient),
 *   then filling remaining space with 1x1 icons.
 *
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), constant extra space used.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    long z = (y + 1) / 2; // Estimate minimum screens needed for 2x2 icons (each screen can hold at most 2 such icons)
    x -= (15 * z - 4 * y); // Subtract space occupied by 2x2 icons from available 1x1 icon count
    x = (x > 0 ? x : 0);   // Ensure non-negative count of leftover 1x1 icons
    z += (x + 14) / 15;    // Add extra screens needed for remaining 1x1 icons (each screen fits up to 15)
    printf("%ld\n", z);
  }
}


// https://github.com/VaHiX/codeForces/