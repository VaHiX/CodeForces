// Problem: CF 1634 A - Reverse and Concatenate
// https://codeforces.com/contest/1634/problem/A

/*
 * Problem: Determine the number of distinct strings achievable after exactly k operations,
 * where each operation appends either the reverse of the string or the string to the reverse.
 *
 * Algorithms/Techniques:
 * - String manipulation with reverse concatenation
 * - Key insight: If k == 0, only one string possible (original).
 *   If the original string is a palindrome, then it remains a palindrome after any number of operations,
 *   thus still only one distinct string can be formed.
 *   Otherwise, after at least one operation, we can get at most 2 distinct strings.
 *
 * Time Complexity: O(n) for each test case (n = length of the string)
 * Space Complexity: O(n) for storing the string and its reverse
 */

#include <stdio.h>
#include <iostream>
#include <string>

bool isPalindrome(std::string s) {
  for (long p = 0; 2 * p < s.size(); p++) { // Loop through half of the string to compare with mirrored positions
    if (s[p] != s[s.size() - 1 - p]) {     // If characters at symmetric positions don't match, not a palindrome
      return false;
    }
  }
  return true;
}

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    if (!k) {
      puts("1"); // No operations performed, only original string
    } else if (isPalindrome(s)) {
      puts("1"); // If original string is palindrome, repeated operations maintain the same set of distinct strings
    } else {
      puts("2"); // Otherwise, two distinct strings possible after any number of operations >= 1
    }
  }
}


// https://github.com/VaHiX/codeForces/