// Problem: CF 1008 A - Romaji
// https://codeforces.com/contest/1008/problem/A

/*
 * Problem: A. Romaji
 * Purpose: Determine if a given string follows the rules of Berlanese language.
 *          - Every consonant (except 'n') must be followed by a vowel.
 *          - 'n' can be followed by anything (including nothing).
 *          - Vowels are 'a', 'o', 'u', 'i', 'e'.
 *
 * Algorithm:
 *   1. Check if the last character is a vowel or 'n'. If not, the string is invalid.
 *   2. Iterate through all characters except the last one:
 *      - For each consonant (not 'n' and not a vowel), check if the next character is a vowel.
 *      - If not, mark as invalid.
 *   3. Output "YES" if valid, otherwise "NO".
 *
 * Time Complexity: O(n) where n is the length of the string.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 */

#include <iostream>
#include <string>

bool isVowel(char x) {
  return ((x == 'a') || (x == 'o') || (x == 'u') || (x == 'i') || (x == 'e'));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string s;
  std::cin >> s;
  long n = s.size();
  bool valid(isVowel(s[n - 1]) || s[n - 1] == 'n'); // Check if last char is valid (vowel or 'n')
  for (long p = 0; p < n - 1; p++) {                // Iterate through all chars except the last
    if (!isVowel(s[p]) && (s[p] != 'n') && !isVowel(s[p + 1])) { // If current is consonant (not 'n') and next is also consonant
      valid = false;                                // Mark as invalid
      break;
    }
  }
  std::cout << (valid ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/