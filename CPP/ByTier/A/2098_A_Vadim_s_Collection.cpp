// Problem: CF 2098 A - Vadim's Collection
// https://codeforces.com/contest/2098/problem/A

/*
 * Problem: Rearrange digits of a beautiful phone number to form the smallest possible beautiful phone number.
 *
 * A beautiful phone number is a 10-digit string where the i-th digit (from left) is at least (10 - i).
 * Example: 9988776655 is beautiful; 9099999999 is not, because the second digit '0' < 8.
 *
 * Algorithm:
 * 1. For each test case, count occurrences of each digit (0-9) in the input string.
 * 2. Build the result from left to right:
 *    - For each position p (0 to 9), try placing the largest possible digit u such that:
 *      - There are remaining occurrences of u.
 *      - The digit u satisfies the constraint: u >= (10 - p).
 * 3. Place the chosen digit, decrement its count, and proceed.
 *
 * Time Complexity: O(t * n), where t is number of test cases and n = 10 (fixed) → effectively O(t)
 * Space Complexity: O(1), since we use fixed-size arrays of size 10.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    int v[10] = {0}; // Count of each digit (0-9)
    for (long p = 0; p < s.size(); p++) {
      ++v[s[p] - '0']; // Count occurrences of each digit
    }
    std::string w(s); // Copy input string to build result
    for (long p = 0; p < w.size(); p++) {
      for (long u = 9 - p; u < 10; u++) { // Try from highest feasible digit down
        if (!v[u]) {
          continue; // Skip if no more of this digit available
        }
        w[p] = '0' + u; // Place the digit
        --v[u];         // Decrease count
        break;          // Move to next position
      }
    }
    std::cout << w << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/