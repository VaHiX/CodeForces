// Problem: CF 1820 A - Yura's New Name
// https://codeforces.com/contest/1820/problem/A

/*
Problem: A. Yura's New Name
Purpose: Given a string consisting of '_' and '^', determine the minimum number of characters to insert so that every character is part of at least one smiley face "^_^" or "^^".

Algorithms/Techniques:
- Greedy approach to count required insertions by analyzing consecutive underscores and edges.

Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(1) - only using constant extra space.

*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    // Count initial smiley parts:
    // 1. If first char is '_', add 1 to count
    // 2. If last char is '_', add 1 to count
    // 3. If string equals "^", add 1 to count (as it's a valid smiley)
    long cnt((s[0] == '_') + (s.back() == '_') + (s == "^"));
    
    // Loop through string to check consecutive underscores
    for (long p = 1; p < s.size(); p++) {
      // If previous and current character are both '_', add 1 to count
      cnt += (s[p - 1] == '_' && s[p] == '_');
    }
    
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/