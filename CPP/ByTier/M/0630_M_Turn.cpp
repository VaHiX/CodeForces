// Problem: CF 630 M - Turn
// https://codeforces.com/contest/630/problem/M

/*
 * Problem: Rotate image to minimize deviation from vertical
 * Purpose: Given a camera rotation angle x, find the minimum number of 90-degree clockwise turns
 *          needed to minimize the deviation from "true up" (vertical).
 *
 * Algorithm:
 * - Normalize the input angle to [0, 360) range.
 * - Try all possible numbers of 90-degree clockwise turns (0 to 4).
 * - For each turn count, compute the resulting deviation from vertical,
 *   considering the equivalent counter-clockwise rotation.
 * - Select the turn count that minimizes the deviation.
 *
 * Time Complexity: O(1) - constant time due to fixed iteration limit (5)
 * Space Complexity: O(1) - only using a few integer variables
 */
#include <stdint.h>
#include <iostream>

int main() {
  const int64_t C = 360;  // Full circle in degrees
  int64_t x;
  std::cin >> x;
  x %= C;  // Normalize x to [0, 360)
  if (x < 0) {
    x += C;  // Ensure x is positive
  }
  int ans(0), min(C + 1);  // Initialize answer and minimum deviation
  for (int p = 0; p < 5; p++) {  // Try 0 to 4 clockwise turns
    int64_t y = (C + x - 90 * p) % C;  // Compute resulting rotation after p turns
    if (y < min) {  // Check clockwise deviation
      min = y;
      ans = p;
    }
    if ((C - y) < min) {  // Check counter-clockwise deviation (equivalent to clockwise)
      min = C - y;
      ans = p;
    }
  }
  ans %= 4;  // Ensure result is in [0, 3) range
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/