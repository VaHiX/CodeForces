// Problem: CF 1809 A - Garland
// https://codeforces.com/contest/1809/problem/A

/*
 * Problem: Garland
 * Purpose: Determine the minimum number of operations to turn all 4 light bulbs on,
 *          given that each operation can only be applied to a bulb of a different color
 *          than the previously operated bulb.
 *
 * Algorithms/Techniques:
 *   - Sorting to group same colors together
 *   - Case analysis based on sorted string patterns
 *
 * Time Complexity: O(t * log(4)) ≈ O(t), where t is number of test cases.
 * Space Complexity: O(1) - only using a fixed amount of extra space.
 */

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    sort(s.begin(), s.end()); // Sort the colors to group same ones together
    int res(0);
    if (s[0] == s[3]) {
      // All colors are the same, impossible to turn all on due to restriction
      res = -1;
    } else if (s[1] == s[3] || s[0] == s[2]) {
      // Two pairs of same colors or one color repeated thrice, need 6 ops
      res = 6;
    } else {
      // All colors are different, need 4 ops
      res = 4;
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/