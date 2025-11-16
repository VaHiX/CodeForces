// Problem: CF 938 A - Word Correction
// https://codeforces.com/contest/938/problem/A

/*
Purpose: This program corrects a word by removing consecutive vowels, keeping only the second vowel in a pair of consecutive vowels.
         It iterates through the string and skips the first vowel in any consecutive vowel pair.

Algorithms/Techniques:
- Single pass through the string
- Character-by-character comparison to detect consecutive vowels
- String building with conditional skipping

Time Complexity: O(n) where n is the length of the input string
Space Complexity: O(n) for storing the input string and output string

*/
#include <iostream>
#include <string>

bool isVowel(char x) {
  return (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u' || x == 'y');
}
int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::cout << s[0];  // Output first character unconditionally
  for (long p = 1; p < s.size(); p++) {
    if (isVowel(s[p]) && isVowel(s[p - 1])) {
      continue;  // Skip the current vowel if it's consecutive to the previous one
    }
    std::cout << s[p];  // Output the current character
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/