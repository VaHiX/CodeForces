// Problem: CF 712 B - Memory and Trident
// https://codeforces.com/contest/712/problem/B

/*
 * Problem: Memory and Trident
 * Purpose: Determine the minimum number of edits required to make a sequence of moves
 *          end at the origin (0,0). Each move is one of U, D, L, R.
 * 
 * Algorithm/Techniques:
 *   - Count the number of each type of move.
 *   - Calculate the imbalance in vertical (U/D) and horizontal (L/R) directions.
 *   - The minimum number of changes is half the sum of absolute differences
 *     because each change can fix one unit of imbalance in both directions.
 *   - If the total length is odd, it's impossible to return to origin.
 * 
 * Time Complexity: O(n), where n is the length of string s
 * Space Complexity: O(1), only using a few variables for counting
 */
#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  // If the length is odd, it's impossible to return to origin
  if (s.size() % 2) {
    puts("-1");
    return 0;
  }
  // Count occurrences of each direction
  long u(0), d(0), l(0), r(0);
  for (size_t p = 0; p < s.size(); p++) {
    if (s[p] == 'U') {
      ++u;
    } else if (s[p] == 'D') {
      ++d;
    } else if (s[p] == 'L') {
      ++l;
    } else if (s[p] == 'R') {
      ++r;
    }
  }
  // Calculate imbalance in vertical and horizontal directions
  long d1 = u - d;  // Vertical imbalance
  if (d1 < 0) {
    d1 = -d1;
  }
  long d2 = l - r;  // Horizontal imbalance
  if (d2 < 0) {
    d2 = -d2;
  }
  // Minimum edits = (vertical_imbalance + horizontal_imbalance) / 2
  long ans = (d1 + d2) / 2;
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/