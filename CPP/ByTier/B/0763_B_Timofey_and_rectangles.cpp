// Problem: CF 763 B - Timofey and rectangles
// https://codeforces.com/contest/763/problem/B

/*
Purpose: This code solves the problem of coloring rectangles on an infinite plane such that adjacent rectangles (sharing a side) have different colors.
The solution leverages the fact that each rectangle has odd-length sides and uses a coloring scheme based on parity of coordinates.

Key Techniques:
- Coordinate parity analysis: For each rectangle, compute the parity (even/odd) of its x and y coordinates.
- Color assignment: Use a simple formula to assign one of four colors (1 to 4) based on parity.

Time Complexity: O(n), where n is the number of rectangles. Each rectangle is processed in constant time.
Space Complexity: O(1), only a few variables are used regardless of input size.

Algorithm:
1. For each rectangle defined by (x1, y1, x2, y2), extract x1 and y1.
2. Compute parity of x1 and y1 using modulo 2.
3. Map the parity pair (x parity, y parity) to a color using the formula (2 * x + y + 1) % 4 + 1.
   This ensures a valid 4-coloring for all cases where rectangles are adjacent by side.
*/

#include <iostream>
int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::cout << "YES" << std::endl;
  while (n--) {
    long x, y, z, w;
    std::cin >> x >> y >> z >> w;
    x = ((x % 2) + 2) % 2;  // Compute the parity of x1 (0 or 1)
    y = ((y % 2) + 2) % 2;  // Compute the parity of y1 (0 or 1)
    std::cout << (2 * x + y + 1) << std::endl;  // Assign color based on parity
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/