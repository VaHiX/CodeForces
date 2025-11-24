// Problem: CF 1461 A - String Generation
// https://codeforces.com/contest/1461/problem/A

/*
 * Code Purpose: Generate a string of length n using characters 'a', 'b', 'c' 
 *               such that the maximum length of any palindromic substring is at most k.
 * 
 * Algorithm/Technique: 
 *   - Use a cyclic pattern of 'a', 'b', 'c' to fill the string.
 *   - This ensures that no three consecutive characters are the same,
 *     which prevents long palindromes from forming.
 *   - Since k >= 1, and we use at most 3 different characters in a cyclic manner,
 *     we are guaranteed to avoid palindromes longer than k.
 * 
 * Time Complexity: O(n) - single loop over n characters.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 */

#include <iostream>
int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    for (long p = 0; p < n; p++) {
      // Cyclically assign 'a', 'b', 'c' to each position
      char x = 'a' + (p % 3);
      std::cout << x;
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/