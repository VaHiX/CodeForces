// Problem: CF 1428 C - ABBB
// https://codeforces.com/contest/1428/problem/C

/*
 * Problem: C. ABBB
 * Purpose: Simulate a process where we can remove substrings "AB" or "BB"
 *          from a string of 'A' and 'B' characters to minimize its length.
 * Algorithm: Use a stack-like approach with a vector to simulate the process:
 *            - For each character in the input string:
 *              * If it's 'A' or the vector is empty, push it.
 *              * Otherwise (i.e., current char is 'B' and vector is not empty):
 *                * If the top of vector is 'A', pop it (simulate removing "AB").
 *                * Else if top is 'B', pop it (simulate removing "BB").
 *            - The final size of the vector gives the minimum string length.
 *
 * Time Complexity: O(n) where n is the total length of all input strings combined.
 * Space Complexity: O(n) for storing the vector which can be up to the size of input string.
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::vector<char> v;
    for (long p = 0; p < s.size(); p++) {
      // If current char is 'A' or stack is empty, push it
      if (s[p] == 'A' || v.empty()) {
        v.push_back(s[p]);
      } else {
        // Current char is 'B', check top of stack
        v.pop_back(); // Remove the last character (simulate bomb operation)
      }
    }
    std::cout << v.size() << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/