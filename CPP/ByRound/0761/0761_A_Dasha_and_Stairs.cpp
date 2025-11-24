// Problem: CF 761 A - Dasha and Stairs
// https://codeforces.com/contest/761/problem/A

/*
 * Problem: Dasha and Stairs
 * 
 * Purpose: Determine if there exists an interval of steps from l to r such that 
 *          the number of even steps is 'a' and the number of odd steps is 'b'.
 * 
 * Algorithm: 
 *   - For any interval of consecutive integers, the difference between the count 
 *     of even and odd numbers can only be 0 or 1.
 *   - If the total number of steps (a + b) is 0, then we have no steps, so the interval 
 *     is invalid.
 *   - Otherwise, we check if the difference between even and odd steps is within [-1, 1].
 * 
 * Time Complexity: O(1) - Constant time operations.
 * Space Complexity: O(1) - Only using a fixed amount of extra space.
 */

#include <iostream>
int main() {
  int a, b;
  std::cin >> a >> b;
  // Check conditions:
  // 1. Total steps > 0 (interval must have at least one step)
  // 2. Difference between even and odd steps is in range [-1, 1]
  std::cout << (((a + b > 0) && (-1 <= a - b) && (a - b <= 1)) ? "YES" : "NO")
            << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/