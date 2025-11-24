// Problem: CF 1108 D - Diverse Garland
// https://codeforces.com/contest/1108/problem/D

/*
D. Diverse Garland
Algorithm: Greedy approach to make the garland diverse by minimizing recolors.
Time Complexity: O(n), where n is the number of lamps.
Space Complexity: O(1) excluding input/output storage.

Approach:
- Traverse the string from left to right.
- When we find two adjacent lamps with the same color, we change the color of the second lamp
  to one that is different from both itself and its previous lamp.
- We try each of the three colors (R, G, B) in order until we find a valid one.
- This greedy strategy ensures minimal number of changes since we only change what's necessary.
*/

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  const std::string f = "RGB"; // Available colors
  std::string s;
  std::cin >> s;
  long cnt(0); // Count of recolors needed
  for (long p = 1; p < n; p++) { // Start from index 1 to compare with previous
    if (s[p] == s[p - 1]) { // If current lamp has same color as previous
      ++cnt; // Increment recolor counter
      for (long u = 0; u < 3; u++) { // Try each of the three colors
        // Check if color u is different from both adjacent lamps
        if (f[u] != s[p - 1] && ((p == n - 1) || f[u] != s[p + 1])) {
          s[p] = f[u]; // Change current lamp's color
          break; // Break after first valid change
        }
      }
    }
  }
  std::cout << cnt << std::endl;
  std::cout << s << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/