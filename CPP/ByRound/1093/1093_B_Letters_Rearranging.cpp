// Problem: CF 1093 B - Letters Rearranging
// https://codeforces.com/contest/1093/problem/B

/*
Purpose: To rearrange the letters of a given string to form a non-palindromic string.
         If it's impossible (e.g., all characters are the same), output -1.

Algorithm:
- For each query, check if all characters in the string are the same.
- If all characters are the same, it's impossible to make a non-palindrome → output -1.
- Otherwise, find the first character that differs from the first character.
- Swap this character with the first character to break potential palindromes.
- Output the resulting string.

Time Complexity: O(n) where n is the length of the string. We scan the string twice in the worst case.
Space Complexity: O(1) excluding the input string, as we use only a constant amount of extra space.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long diff(-1);
    // Find the first character that is different from the first character
    for (long p = 0; p < s.size(); p++) {
      if (s[p] != s[0]) {
        diff = p;
        break;
      }
    }
    // If all characters are the same, it's impossible to make a good string
    if (diff < 0) {
      std::cout << "-1" << std::endl;
    } else {
      // If the first and last characters are the same,
      // swapping the first different character with the first one
      // ensures the result is not a palindrome
      if (s[0] == s[s.size() - 1]) {
        char tmp = s[0];
        s[0] = s[diff];
        s[diff] = tmp;
      }
      std::cout << s << std::endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/