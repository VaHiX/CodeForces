// Problem: CF 630 G - Challenge Pennants
// https://codeforces.com/contest/630/problem/G

/*
 * Problem: G. Challenge Pennants
 * 
 * Purpose: Calculate the number of ways to distribute 5 "I fixed a critical bug" pennants 
 *          and 3 "I suggested a new feature" pennants among n tables, where each pennant 
 *          can be placed on any table and tables can hold any number of pennants.
 * 
 * Approach:
 * - The problem is about distributing indistinguishable objects (pennants) into distinguishable bins (tables).
 * - For each type of pennant, we calculate the number of ways to distribute them using combinations with repetition.
 * - The formula for distributing k indistinguishable items into n distinguishable bins is C(n + k - 1, k).
 * - We compute two separate values:
 *   - x: ways to distribute 5 "critical bug" pennants among n tables.
 *   - y: ways to distribute 3 "new feature" pennants among n tables.
 * - Final result is the product of x and y.
 * 
 * Time Complexity: O(1) - The computation involves only a fixed number of arithmetic operations.
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 */

#include <stdint.h>
#include <iostream>

int main() {
  int64_t n;
  std::cin >> n;
  // Compute the number of ways to distribute 5 critical bug pennants among n tables
  // Formula: C(n + 5 - 1, 5) = C(n + 4, 5) = n * (n + 1) * (n + 2) * (n + 3) * (n + 4) / (5!)
  int64_t x = n + 2 * n * (n - 1) + n * (n - 1) * (n - 2) +
              n * (((n - 1) * (n - 2) / 2) * (n - 3) / 3) +
              ((((n * (n - 1) / 2) * (n - 2) / 3) * (n - 3) / 4) * (n - 4) / 5);
  
  // Compute the number of ways to distribute 3 new feature pennants among n tables
  // Formula: C(n + 3 - 1, 3) = C(n + 2, 3) = n * (n + 1) * (n + 2) / (3!)
  int64_t y = n + n * (n - 1) + n * (n - 1) * (n - 2) / 6;
  
  // The total number of arrangements is the product of x and y
  int64_t ans = x * y;
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/