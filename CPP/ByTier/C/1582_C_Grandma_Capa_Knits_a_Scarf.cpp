// Problem: CF 1582 C - Grandma Capa Knits a Scarf
// https://codeforces.com/contest/1582/problem/C

/*
 * Problem: C. Grandma Capa Knits a Scarf
 * Purpose: Given a string, find the minimum number of characters to remove 
 *          such that the resulting string is a palindrome. Only one character type 
 *          can be removed from the string.
 * Algorithm: 
 *   - For each possible character (from 'a' to 'z'), simulate removing all its occurrences
 *     and check if the remaining string forms a palindrome.
 *   - Use two pointers approach to determine if current substring is palindrome.
 *   - If it's not palindrome, try to make it so by consuming one of the mismatched ends 
 *     if it matches the character being considered for removal.
 * Time Complexity: O(26 * n) = O(n), where n is length of string
 * Space Complexity: O(1)
 */
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long res(-1); // Initialize result to -1, indicating no valid solution yet
    for (char c = 'a'; c <= 'z'; c++) { // Try each character from 'a' to 'z'
      long left(0), right(n - 1); // Two pointers, starting at both ends
      long cnt(0); // Count of removals needed for current character c
      while (cnt >= 0 && left < right) { // While valid and not overlapping
        if (s[left] == s[right]) {
          ++left; // If characters match, move towards center
          --right;
        } else if (s[left] == c) {
          ++left; // Move left pointer forward and count as removal
          ++cnt;
        } else if (s[right] == c) {
          --right; // Move right pointer backward and count as removal
          ++cnt;
        } else {
          cnt = -1; // Mismatch and neither side equals the target char, impossible
        }
      }
      if (cnt >= 0) { // If this character lead to a valid palindrome
        res = ((res < 0) || (cnt < res) ? cnt : res); // Update minimum count
      }
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/