// Problem: CF 1811 A - Insert Digit
// https://codeforces.com/contest/1811/problem/A

/*
 * Problem: A. Insert Digit
 * Purpose: Given a positive number as a string and an additional digit,
 *          insert the digit at a position to maximize the resulting number.
 *
 * Algorithm:
 *   - For each digit in the input string from left to right:
 *     - If current digit is less than the new digit, insert the new digit before it
 *       and stop insertion process
 *     - Otherwise, append the original digit to result
 *   - If no insertion occurred (e.g., number is non-decreasing), append the new digit at end
 *
 * Time Complexity: O(n) where n is the length of the string.
 * Space Complexity: O(n) for storing the result string.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    char d;
    std::cin >> n >> d;
    std::string s;
    std::cin >> s;
    bool done(false); // flag to indicate if the new digit has been inserted
    for (long p = 0; p < s.size(); p++) {
      if (!done && s[p] < d) {  // If not yet inserted and current digit < new digit
        std::cout << d;         // Insert the new digit
        done = true;            // Mark insertion as done
      }
      std::cout << s[p];        // Output current digit
    }
    if (!done) {                // If never inserted, append at end
      std::cout << d;
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/