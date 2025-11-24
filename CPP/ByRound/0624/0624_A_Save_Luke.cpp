// Problem: CF 624 A - Save Luke
// https://codeforces.com/contest/624/problem/A

/*
 * Code Purpose:
 * This program calculates the maximum time Luke can survive before the two presses
 * come together and crush him. The presses start at positions 0 and L, moving towards
 * each other with speeds v1 and v2 respectively. Luke has a width d and must choose
 * a position to maximize his survival time.
 *
 * Algorithm:
 * - The key insight is that Luke should position himself such that the distance
 *   between the presses reduces to exactly his width d.
 * - The relative speed at which the presses approach each other is v1 + v2.
 * - Time = (Initial Distance - Width) / Relative Speed = (L - d) / (v1 + v2)
 *
 * Time Complexity: O(1) - Constant time computation
 * Space Complexity: O(1) - Only a few variables used
 */

#include <stdio.h>
#include <iostream>

using namespace std;
int main() {
  long long int i, j, k;
  double d, l, v1, v2, x;
  cin >> d >> l >> v1 >> v2;
  x = (l - d) / (v1 + v2);  // Compute the time until the presses meet at distance d
  printf("%.15lf", x);
  return 0;
}


// https://github.com/VaHiX/CodeForces/