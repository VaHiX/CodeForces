// Problem: CF 802 G - Fake News (easy)
// https://codeforces.com/contest/802/problem/G

#include <iostream>
#include <string>

/*
Algorithm: Subsequence Matching
Approach: Two-pointer technique to check if "heidi" appears as a subsequence in the input string
Time Complexity: O(n) where n is the length of input string s
Space Complexity: O(1) - only using constant extra space

The algorithm works by:
1. Maintaining a pointer 'ind' to track progress through "heidi"
2. Iterating through each character of input string s
3. When a character matches the current expected character in "heidi", advance the pointer
4. If we've matched all characters in "heidi", the string is fake (contains heidi as subsequence)
*/

int main() {
  const std::string t("heidi");  // Target subsequence to find
  std::string s;                 // Input string
  std::cin >> s;                 // Read input string
  bool fake(false);              // Flag to indicate if subsequence is found
  long ind(0);                   // Index tracking progress through "heidi"
  for (long p = 0; p < s.size(); p++) {  // Iterate through each character of input
    if (s[p] == t[ind]) {      // If current character matches expected character
      ++ind;                   // Move to next character in "heidi"
    }
    if (ind >= t.size()) {     // If all characters of "heidi" have been matched
      fake = true;             // Mark as fake
      break;                   // Exit early
    }
  }
  std::cout << (fake ? "YES" : "NO") << std::endl;  // Output result
  return 0;
}

// https://github.com/VaHiX/CodeForces/