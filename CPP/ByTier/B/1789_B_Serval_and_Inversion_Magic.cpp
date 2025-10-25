// Problem: CF 1789 B - Serval and Inversion Magic
// https://codeforces.com/contest/1789/problem/B

/*
 * Problem: B. Serval and Inversion Magic
 * Purpose: Determine if a binary string can become a palindrome after exactly one inversion operation (flipping a substring).
 * Algorithm:
 *   - For each test case, check the first half of the string against its corresponding second half.
 *   - Count how many times adjacent character pairs differ in their equality to the previous pair.
 *   - If this count is less than 3, then it's possible to make a palindrome using one inversion.
 * Time Complexity: O(n) per test case, where n is the length of the string
 * Space Complexity: O(1) excluding input storage
 */

#include <stdio.h>
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
    int cnt(0); // Counter for mismatches in adjacent pairs
    bool prev(true); // Tracks the previous comparison result (true = equal, false = not equal)
    for (long p = 0; cnt < 3 && p < n / 2; p++) {
      int check = (s[p] == s[n - 1 - p]); // Check if characters at symmetric positions are equal
      if (check != prev) { // If current pair doesn't match the previous one
        ++cnt; // Increment mismatch counter
      }
      prev = check; // Update previous comparison result
    }
    puts(cnt < 3 ? "Yes" : "No"); // Output Yes if less than 3 mismatches, otherwise No
  }
}


// https://github.com/VaHiX/codeForces/