// Problem: CF 1155 A - Reverse a Substring
// https://codeforces.com/contest/1155/problem/A

/*
 * Problem: Reverse a Substring
 * 
 * Purpose: To find a substring in the given string that, when reversed,
 *          results in a lexicographically smaller string. If possible,
 *          output "YES" and the indices of the substring to reverse.
 *          Otherwise, output "NO".
 * 
 * Algorithm:
 * 1. Scan the string from left to right.
 * 2. Find the first position where s[i] < s[i-1]. This indicates where
 *    a reversal can make the string lexicographically smaller.
 * 3. The substring to reverse starts at this position (1-indexed) and
 *    ends at the next position (in case of a single swap).
 * 4. If no such position exists, the string is already minimal,
 *    so output "NO".
 * 
 * Time Complexity: O(n) - linear scan of the string
 * Space Complexity: O(1) - only using a few variables
 */

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long pos(-1);
  // Find the first position where s[i] < s[i-1]
  for (long p = 1; p < s.size(); p++) {
    if (s[p] < s[p - 1]) {
      pos = p + 1; // Store 1-indexed position
      break;
    }
  }
  if (pos < 0) {
    std::cout << "NO" << std::endl;
  } else {
    // Output "YES" and the substring to reverse (1-indexed)
    std::cout << "YES\n" << (pos - 1) << " " << pos << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/