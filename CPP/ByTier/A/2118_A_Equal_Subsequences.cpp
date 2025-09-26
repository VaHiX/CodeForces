// Problem: CF 2118 A - Equal Subsequences
// https://codeforces.com/contest/2118/problem/A

/*
 * Task: Construct a perfect bitstring of length n with exactly k '1' characters.
 *       A perfect bitstring has equal number of '101' and '010' subsequences.
 *
 * Algorithm:
 *   - To ensure equal counts of '101' and '010' subsequences:
 *     - Place all '1's at the end of the string
 *     - Prefix with (n - k) zeros, followed by k ones
 *   - This ensures that:
 *     - No '101' subsequence is formed (since all 1s are at the end)
 *     - No '010' subsequence is formed (since there are no 0s after 1s)
 *     - The count of both types of subsequences becomes zero, hence equal
 *
 * Time Complexity: O(n) per test case, as we construct a string of length n.
 * Space Complexity: O(n) for storing the output string.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Speeds up I/O operations
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    // Output (n - k) zeros followed by k ones
    std::cout << std::string(n - k, '0') << std::string(k, '1') << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/