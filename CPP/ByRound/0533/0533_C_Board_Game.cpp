// Problem: CF 533 C - Board Game
// https://codeforces.com/contest/533/problem/C

/*
 * Problem: Board Game
 * 
 * Algorithm/Technique: Game Theory, Strategic Analysis
 * 
 * Time Complexity: O(1) - Constant time computation based on input values.
 * Space Complexity: O(1) - Only a constant amount of space is used.
 * 
 * The game involves two players moving pawns on an infinite grid towards (0,0).
 * Polycarp can move left or down; Vasiliy can move left, down, or diagonally.
 * The key insight is to determine whether Polycarp can force a win by analyzing
 * the relative positions of the pawns.
 * 
 * The logic is based on the idea that if the distance (in terms of moves) from
 * Polycarp's position to (0,0) is less than or equal to a certain threshold,
 * then Polycarp wins. This is determined using the condition:
 * 
 * (d >= a + b) || (c >= a + b) || (c >= a && d >= b)
 * 
 * Where:
 *   a, b are Polycarp's coordinates (xp, yp)
 *   c, d are Vasiliy's coordinates (xv, yv)
 * 
 * If any of the three conditions is true, Polycarp wins.
 * Otherwise, Vasiliy wins.
 */

#include <cstdio>
int main() {
  long a, b, c, d;
  scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
  puts((d >= a + b) || (c >= a + b) || (c >= a && d >= b) ? "Polycarp"
                                                          : "Vasiliy");
  return 0;
}


// https://github.com/VaHiX/CodeForces/