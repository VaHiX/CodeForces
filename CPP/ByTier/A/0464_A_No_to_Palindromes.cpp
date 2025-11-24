// Problem: CF 464 A - No to Palindromes!
// https://codeforces.com/contest/464/problem/A

/*
 * Problem: Find the lexicographically next "tolerable" string.
 * A tolerable string uses only the first 'p' letters and contains no palindromic
 * contiguous substrings of length 2 or more.
 *
 * Algorithm:
 * - Start from the last character and increment it.
 * - If the character exceeds 'a' + p, reset to 'a' and carry over to the previous position.
 * - At each step, ensure that the current character does not form a palindrome with:
 *   - The previous character (s[pos] != s[pos - 1])
 *   - The character before that (s[pos] != s[pos - 2])
 * - If we go out of bounds (pos < 0), return "NO".
 *
 * Time Complexity: O(n^2) in worst case due to potential backtracking and checks.
 * Space Complexity: O(n) for the string storage.
 */

#include <cstdio>
#include <iostream>
#include <string>
int main() {
  int n, p;
  scanf("%d %d\n", &n, &p);
  std::string s;
  getline(std::cin, s);
  int pos = n - 1;
  ++s[pos];
  while (pos >= 0 && pos < n) {
    if (s[pos] >= 'a' + p) {
      // If character exceeds allowed range, reset and carry to the left
      s[pos] = 'a';
      ++s[--pos];
    } else if (pos > 0 && s[pos] == s[pos - 1]) {
      // If current char equals previous, increment to avoid palindrome of length 2
      ++s[pos];
    } else if (pos > 1 && s[pos] == s[pos - 2]) {
      // If current char equals the one before previous, increment to avoid palindrome of length 3
      ++s[pos];
    } else {
      // Valid character, move forward
      ++pos;
    }
  }
  if (pos < 0) {
    puts("NO");
  } else {
    std::cout << s << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/