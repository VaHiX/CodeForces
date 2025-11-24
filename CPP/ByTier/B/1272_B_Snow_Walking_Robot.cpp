// Problem: CF 1272 B - Snow Walking Robot
// https://codeforces.com/contest/1272/problem/B

/*
Algorithm/Techniques: Greedy approach
Time Complexity: O(n) where n is the length of the input string
Space Complexity: O(1) - only using a few variables for counting and storing results

The solution works by:
1. Counting occurrences of each direction (U, D, L, R)
2. Balancing vertical moves (U and D) and horizontal moves (L and R) to ensure
   the robot returns to the origin (0,0) and doesn't visit any cell (except start) twice
3. Ensuring that we can form a valid cycle by taking min of opposing directions
4. Adjusting for cases when one dimension has no moves but the other does
5. Outputting the constructed valid sequence
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long q;
  std::cin >> q;
  while (q--) {
    std::string s;
    std::cin >> s;
    long u(0), d(0), l(0), r(0);
    // Count occurrences of each direction
    for (long p = 0; p < s.size(); p++) {
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
    // Balance up and down moves - take minimum of U and D to ensure we can return to origin
    u = (u < d) ? u : d;
    d = u;
    // Balance left and right moves - take minimum of L and R to ensure we can return to origin
    r = (l < r) ? l : r;
    l = r;
    // Special cases: if we have vertical moves but no horizontal, or vice versa
    // we must include at least 1 move in the dimension with no moves to allow valid path
    if (u <= 0 && l > 0) {
      l = r = 1;
    }
    if (r <= 0 && u > 0) {
      u = d = 1;
    }
    // Output the length of the valid sequence
    std::cout << (u + d + l + r) << std::endl;
    // Output U moves
    for (long p = 0; p < u; p++) {
      std::cout << "U";
    }
    // Output L moves
    for (long p = 0; p < l; p++) {
      std::cout << "L";
    }
    // Output D moves
    for (long p = 0; p < d; p++) {
      std::cout << "D";
    }
    // Output R moves
    for (long p = 0; p < r; p++) {
      std::cout << "R";
    }
    std::cout << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/