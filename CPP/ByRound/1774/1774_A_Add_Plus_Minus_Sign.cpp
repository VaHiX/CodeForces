// Problem: CF 1774 A - Add Plus Minus Sign
// https://codeforces.com/contest/1774/problem/A

/*
 * Problem: Add Plus Minus Sign
 * Algorithm/Technique: Greedy approach
 *
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(1) extra space excluding input/output storage.
 *
 * Description:
 * Given a binary string of 0s and 1s, we need to place '+' or '-' signs
 * between consecutive characters such that the absolute value of the resulting
 * expression (interpreted as a binary number with signs) is minimized.
 * 
 * Strategy:
 * - Start by treating the first character as positive (+1).
 * - For each subsequent character:
 *   - If it's '0', we append '+' to minimize contribution to sum.
 *   - If it's '1' and current running total > 0, we append '-' to reduce sum.
 *   - If it's '1' and current running total == 0, we append '+' to increase sum.
 * This greedy method aims to keep the absolute value of the total as minimal.
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
    long t(s[0] == '1'); // Initialize running total with first character's value
    for (long p = 1; p < s.size(); p++) {
      if (s[p] == '0') {
        std::cout << '+'; // '0' contributes nothing. Keep sum stable.
      } else if (t > 0) {
        std::cout << '-'; // Reduce the positive sum
        t = 0;
      } else if (t == 0) {
        std::cout << '+'; // Increase the sum (starting fresh)
        t = 1;
      }
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/