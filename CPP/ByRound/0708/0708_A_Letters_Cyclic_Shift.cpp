// Problem: CF 708 A - Letters Cyclic Shift
// https://codeforces.com/contest/708/problem/A

/*
 * Problem: Letters Cyclic Shift
 * 
 * Algorithm:
 * - The goal is to find the lexicographically smallest string by shifting
 *   exactly one non-empty substring of the input string s.
 * - Strategy:
 *   1. Skip all leading 'a' characters since shifting them would make the string larger.
 *   2. Once we encounter a character that is not 'a', start shifting characters
 *      until we hit an 'a' or reach the end of the string.
 *   3. If the entire string is made of 'a's, shift the last character to 'z'.
 * 
 * Time Complexity: O(n) where n is the length of the string.
 * Space Complexity: O(1) excluding the input string.
 */

#include <stddef.h>
#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  bool inside(0), done(0);
  size_t ind(0);
  // Skip all leading 'a' characters
  while ((ind < s.size()) && (s[ind] == 'a')) {
    ++ind;
  }
  // If all characters are 'a', change the last one to 'z'
  if (ind == s.size()) {
    s[s.size() - 1] = 'z';
    std::cout << s << std::endl;
    return 0;
  }
  // Shift characters until we hit an 'a'
  while ((ind < s.size()) && (s[ind] != 'a')) {
    --s[ind]; // Shift character to the previous one in the alphabet
    ++ind;
  }
  std::cout << s << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/