// Problem: CF 989 A - A Blend of Springtime
// https://codeforces.com/contest/989/problem/A

// ### Flowerbox
// **Purpose:**  
// This code determines whether it's possible for all three flower colors (Amber 'A', Buff 'B', Canary Yellow 'C') to appear in a single cell after some flowers wither and spread their petals. The key idea is to check if there exists a middle cell such that it and its two adjacent cells contain exactly three distinct flower colors — enabling a color blend.

// **Algorithms/Techniques:**  
// - Linear scan through string to find valid triplets.
// - Simple conditional checks for color uniqueness.
// - Early termination optimization on finding a valid configuration.

// **Time Complexity:**  
// O(n), where n is the length of the input string. We traverse the string once with a linear loop.

// **Space Complexity:**  
// O(1), as we only use a constant amount of additional memory for variables (`possible`, `p`).

#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  bool possible(false);
  // Iterate through each cell, checking if it can be the center of a blend
  for (long p = 1; p + 1 < s.size(); p++) {
    // Skip if the current cell or its neighbors are empty (no flower there)
    if (s[p] == '.' || s[p - 1] == '.' || s[p + 1] == '.') {
      continue;
    }
    // Check if the three colors in the center and its two neighbors are all different
    // If so, a blend of all three colors is possible in the center cell
    if (s[p] != s[p - 1] && s[p] != s[p + 1] && s[p - 1] != s[p + 1]) {
      possible = true;
      break;
    }
  }
  std::cout << (possible ? "Yes" : "No") << std::endl;
  return 0;
}

// 
// https://github.com/VaHiX/CodeForces/