// Problem: CF 1840 A - Cipher Shifer
// https://codeforces.com/contest/1840/problem/A

/*
 * Problem: Decrypt a string encrypted according to a specific rule.
 * 
 * Algorithm:
 * - For each character in the encrypted string s, output it and then skip
 *   all subsequent characters until we find the same character again.
 * - This effectively removes the extra characters added between occurrences
 *   of the same character, recovering the original string.
 *
 * Time Complexity: O(n) where n is the length of the string s.
 * Space Complexity: O(1) excluding the input/output storage.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long idx(0);  // Index to traverse the string
    while (idx < n) {
      char ch = s[idx];  // Take current character
      std::cout << ch;   // Output it
      ++idx;             // Move to next character
      while (idx < n && s[idx] != ch) {  // Skip until we find the same character
        ++idx;
      }
      ++idx;  // Skip the matching character
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/