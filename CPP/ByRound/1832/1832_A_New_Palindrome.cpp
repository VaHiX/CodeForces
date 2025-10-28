// Problem: CF 1832 A - New Palindrome
// https://codeforces.com/contest/1832/problem/A

/*
 * Problem: A. New Palindrome
 * Purpose: Given a palindrome string, determine if it's possible to rearrange
 *          its letters to form another distinct palindrome.
 *
 * Algorithm:
 *   - For a string to be rearranged into another palindrome:
 *     1. If the string has even length, all characters must appear an even number of times.
 *     2. If the string has odd length, exactly one character can appear an odd number of times,
 *        and others must appear an even number of times.
 *   - Since input is guaranteed to be a palindrome:
 *     - All characters except possibly one occur an even number of times.
 *     - The condition for rearrangement is that there are more than one unique character
 *       (a single character cannot be rearranged into another string).
 *
 * Time Complexity: O(n), where n is the length of the string, due to scanning the string once.
 * Space Complexity: O(1), since we use a constant amount of extra space (only variables and fixed-size arrays).
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    bool res(false);
    // Loop through the first half of the string to check if all characters
    // (except the first one) are equal to the first character.
    for (long p = 1; p < s.size() / 2; p++) {
      if (s[p] != s[0]) {
        res = true;
        break;
      }
    }
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/