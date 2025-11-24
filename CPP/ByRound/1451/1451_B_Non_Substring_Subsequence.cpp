// Problem: CF 1451 B - Non-Substring Subsequence
// https://codeforces.com/contest/1451/problem/B

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, q;
    std::cin >> n >> q;
    std::string s;
    std::cin >> s;
    while (q--) {
      long left, right;
      std::cin >> left >> right;
      --left;
      --right;
      char first(s[left]), last(s[right]);
      bool possible(false);
      // Check if there's a character equal to first before left index
      for (long p = 0; p < left && !possible; p++) {
        if (s[p] == first) {
          possible = true;
        }
      }
      // Check if there's a character equal to last after right index
      for (long p = right + 1; p < s.size() && !possible; p++) {
        if (s[p] == last) {
          possible = true;
        }
      }
      std::cout << (possible ? "YES" : "NO") << std::endl;
    }
  }
}
/*
B. Non-Substring Subsequence

Purpose:
This program determines whether there exists a good subsequence in a binary string that matches a given substring.
A good subsequence is defined as a subsequence that is not contiguous and has length at least 2.

Algorithms/Techniques:
- Brute force approach for each query
- For each queried substring s[left..right], we check if the first character of the substring appears before index 'left'
  OR if the last character of the substring appears after index 'right'.
- If either condition is satisfied, then a good subsequence exists.

Time Complexity:
O(t * n * q) where t is number of test cases, n is length of string and q is number of queries.
In worst case, for each query we may traverse the full string in both directions (left and right).
Each string traversal can take O(n) time for a single query.

Space Complexity:
O(1) excluding input/output storage, since only a few variables are used for computation.

Input Format:
- First line: number of test cases t
- For each test case:
  - Line 1: n and q (length of string, number of queries)
  - Line 2: binary string s
  - Next q lines: pairs of integers l and r representing query ranges

Output Format:
- For each query: "YES" if a good subsequence exists, otherwise "NO"
*/

// https://github.com/VaHiX/codeForces/