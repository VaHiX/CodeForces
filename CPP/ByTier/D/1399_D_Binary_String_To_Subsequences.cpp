// Problem: CF 1399 D - Binary String To Subsequences
// https://codeforces.com/contest/1399/problem/D

/*
 * Problem: Binary String To Subsequences
 * Algorithm: Greedy assignment of characters to alternating subsequences.
 * Approach:
 *   - Use two stacks (z and a) to track the last used index for '0' and '1' subsequences.
 *   - For each character in the string:
 *     - If it's '0': assign to the latest subsequence that ended with '1', or create a new one.
 *     - If it's '1': assign to the latest subsequence that ended with '0', or create a new one.
 *   - Time Complexity: O(n) per test case, where n is the length of string s.
 *   - Space Complexity: O(n) for storing the result vector and the stacks.
 */

#include <iostream>
#include <vector>
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
    long num(0);  // Tracks the maximum subsequence number assigned so far
    std::vector<long> z, a;  // Stacks for tracking last used indices for '0' and '1'
    std::vector<long> v(s.size());  // Final result vector storing subsequence numbers for each character
    for (long p = 0; p < s.size(); p++) {
      long cur;
      if (s[p] == '0') {  // Character is '0'
        if (a.empty()) {  // No previous '1' seen, so start a new subsequence
          cur = ++num;
        } else {
          cur = a.back();  // Use the last subsequence that ended with '1'
          a.pop_back();    // Remove from stack after using
        }
        z.push_back(cur);  // Push to '0' stack for future reference
      } else if (s[p] == '1') {  // Character is '1'
        if (z.empty()) {  // No previous '0' seen, so start a new subsequence
          cur = ++num;
        } else {
          cur = z.back();  // Use the last subsequence that ended with '0'
          z.pop_back();    // Remove from stack after using
        }
        a.push_back(cur);  // Push to '1' stack for future reference
      }
      v[p] = cur;  // Assign subsequence number to current character
    }
    std::cout << num << std::endl;
    for (long p = 0; p < n; p++) {
      std::cout << v[p] << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/