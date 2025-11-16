// Problem: CF 1837 C - Best Binary String
// https://codeforces.com/contest/1837/problem/C

/*
 * Problem: C. Best Binary String
 * 
 * Purpose: Given a pattern string with '0', '1', and '?', we need to assign 0 or 1 to each '?'
 *          such that the resulting binary string has the minimum cost to sort it in non-decreasing order.
 *          The cost is defined as the minimum number of "reverse a contiguous substring" operations needed.
 * 
 * Approach: 
 * - For each '?', we greedily assign the same value as the previous character to minimize the number of transitions.
 * - This greedy assignment ensures that we have at most one transition from 0 to 1, which leads to a minimal cost.
 * - Specifically, if we have a sequence like 000...0111...1, we can sort it with only one reverse operation.
 * 
 * Time Complexity: O(n) where n is the length of the string. Each character is visited once.
 * Space Complexity: O(1) excluding the input string, as we only use a few variables.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    if (s[0] == '?') {
      s[0] = '0';  // Greedily assign '0' to the first '?'
    }
    for (long p = 1; p < s.size(); p++) {
      if (s[p] == '?') {
        s[p] = s[p - 1];  // Assign same value as previous character to minimize transitions
      }
    }
    std::cout << s << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/