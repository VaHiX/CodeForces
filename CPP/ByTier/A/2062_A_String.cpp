// Problem: CF 2062 A - String
// https://codeforces.com/contest/2062/problem/A

/*
 * Problem: Minimum Operations to Convert String to All Zeros
 *
 * Purpose:
 * Given a binary string s consisting of '0' and '1', find the minimum number of operations
 * to convert all characters to '0'. Each operation selects a subsequence where adjacent
 * characters are different and flips all selected characters.
 *
 * Algorithm:
 * The key insight is that each group of consecutive '1's must be flipped at least once,
 * and each flip can cover multiple adjacent '1's if they form a valid subsequence.
 * However, the minimum number of operations equals the number of groups of consecutive '1's.
 * For example:
 *   - "000" → 0 operations
 *   - "1001" → 2 operations (groups: "1", "1")
 *   - "10101" → 3 operations (groups: "1", "1", "1")
 *
 * Time Complexity: O(n) where n is the length of the string.
 * Space Complexity: O(1) — only using a constant amount of extra space.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Disable synchronization between C and C++ I/O for faster input
  long t;
  std::cin >> t; // Read number of test cases
  while (t--) {
    std::string s;
    std::cin >> s; // Read the binary string
    long ones(0); // Counter for '1's in the string
    for (char x : s) { // Iterate through each character in the string
      ones += (x == '1'); // Increment counter if character is '1'
    }
    std::cout << ones << std::endl; // Output number of '1's (which equals minimum operations)
  }
}


// https://github.com/VaHiX/codeForces/