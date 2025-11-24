// Problem: CF 1650 A - Deletions of Two Adjacent Letters
// https://codeforces.com/contest/1650/problem/A

/*
 * Problem: A. Deletions of Two Adjacent Letters
 * Purpose: Determine if a given odd-length string can be reduced to a single character 'c'
 *          by deleting two adjacent characters at a time.
 * 
 * Algorithm/Techniques:
 *   - For each test case, check whether there exists an occurrence of character 'c'
 *     at an even index (0-based) in the string. If such an index exists,
 *     then it is possible to reduce the string to just that character.
 * 
 * Time Complexity: O(n), where n is the length of the string (each character is checked once)
 * Space Complexity: O(1), only using a constant amount of extra space
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    char c;
    std::cin >> c;
    bool res(false);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] != c) {
        continue; // Skip characters that are not the target character
      }
      if (p % 2 == 0) {
        res = true; // Found a match at an even index
        break;
      }
    }
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/