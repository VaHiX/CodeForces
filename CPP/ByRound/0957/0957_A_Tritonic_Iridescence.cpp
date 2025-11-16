// Problem: CF 957 A - Tritonic Iridescence
// https://codeforces.com/contest/957/problem/A

/*
 * Problem: Tritonic Iridescence
 * 
 * Algorithm/Technique:
 * - The problem involves coloring a canvas with 3 colors (C, M, Y) such that no two adjacent segments have the same color.
 * - '?' represents an unpainted segment that can be filled with any of the three colors.
 * - Key idea: If there's a contradiction in existing colors (adjacent same-colored segments), the answer is "No".
 * - Then, for each '?' we check:
 *   - If it's at the start or end, there's always at least one valid coloring (since it only affects one neighbor).
 *   - If it's between two '?', there's always at least one valid coloring.
 *   - If it's between two same-colored neighbors, there's at least one valid coloring (we can choose the third color).
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  
  // Check if there are already adjacent segments with the same color
  for (long p = 0; p < n - 1; ++p) {
    if (s[p] != '?' && s[p] == s[p + 1]) {
      puts("No");
      return 0;
    }
  }
  
  // Check each '?' to see if there are at least two valid ways to color
  for (int p = 0; p < n; ++p) {
    if (s[p] == '?') {
      // If it's the first or last position, one valid coloring always exists
      if (p == 0 || p == n - 1) {
        puts("Yes");
        return 0;
      }
      // If it's adjacent to another '?', one valid coloring always exists
      if (s[p + 1] == '?') {
        puts("Yes");
        return 0;
      }
      // If the neighbors are the same color, one valid coloring always exists
      if (s[p - 1] == s[p + 1]) {
        puts("Yes");
        return 0;
      }
    }
  }
  
  // If no '?', then only one way, so output "No"
  puts("No");
  return 0;
}


// https://github.com/VaHiX/CodeForces/