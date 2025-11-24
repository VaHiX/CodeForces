// Problem: CF 952 E - Cheese Board
// https://codeforces.com/contest/952/problem/E

/*
 * Problem: Cheese Board
 * 
 * Purpose: This program determines the minimum number of square cheese boards 
 *          needed to arrange all cheeses such that each board contains at most 
 *          one soft cheese and one hard cheese, and the total area of boards 
 *          is minimized.
 * 
 * Algorithms/Techniques:
 * - Counting: Count the number of soft and hard cheeses.
 * - Mathematical Calculation: Use the formula to compute minimal board area,
 *   then take square root to determine the side length of the square board.
 * 
 * Time Complexity: O(N), where N is the number of cheeses.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

int main() {
  int hard = 0, soft = 0;  // Counters for hard and soft cheeses
  long n;
  std::cin >> n;  // Read number of cheeses
  while (n--) {
    std::string cheese, kind;
    std::cin >> cheese >> kind;  // Read cheese name and type
    if (kind == "soft") {
      ++soft;  // Increment soft cheese counter
    } else {
      ++hard;  // Increment hard cheese counter
    }
  }
  // Compute the minimum area required for the square board
  long ans = std::max(2 * std::max(hard, soft) - 1, hard + soft);
  ans = ceil(sqrt(ans));  // Take square root to get side length
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/