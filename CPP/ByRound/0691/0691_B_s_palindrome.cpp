// Problem: CF 691 B - s-palindrome
// https://codeforces.com/contest/691/problem/B

/*
 * Purpose: Determine if a given string is an "s-palindrome", which means the string is symmetric
 *          when each character is replaced by its mirror reflection in the English alphabet.
 *          For example, 'o' maps to 'o', 'x' maps to 'x', etc.
 *
 * Algorithms/Techniques:
 *   - Predefined mapping of characters to their mirror reflections
 *   - Two-pointer approach to check symmetry: compare each character with its mirrored counterpart
 *
 * Time Complexity: O(n), where n is the length of the input string.
 *                  The algorithm reads the string once and performs constant-time operations for each character.
 *
 * Space Complexity: O(1), since the mapping size is fixed (32 characters), independent of input size.
 */

#include <iostream>
#include <map>
#include <string>

int main() {
  // Define the set of characters that have valid mirror reflections
  std::string a("AbdHIMOopqTUVvWwXxY");
  // Define the corresponding mirror characters for each in 'a'
  std::string b("AdbHIMOoqpTUVvWwXxY");
  // Map each character to its mirror reflection
  std::map<char, char> r;
  for (int p = 0; p < a.size(); p++) {
    r[a[p]] = b[p];
  }
  // Read input string
  std::string s;
  std::cin >> s;
  // Assume the string is an s-palindrome until proven otherwise
  bool palindrome(true);
  // Iterate through the string to check if it is symmetric with respect to mirror characters
  for (long p = 0; p < s.size(); p++) {
    // If current character has no mirror or does not match the mirror of the corresponding character
    if (r.count(s[p]) == 0 || r[s[p]] != s[s.size() - p - 1]) {
      palindrome = false;
      break;
    }
  }
  // Output result
  std::cout << (palindrome ? "TAK" : "NIE") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/