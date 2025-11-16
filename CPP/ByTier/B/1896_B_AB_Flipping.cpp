// Problem: CF 1896 B - AB Flipping
// https://codeforces.com/contest/1896/problem/B

/*
B. AB Flipping
Problem Description:
Given a string of 'A' and 'B', we can perform swaps between adjacent characters where s[i] = 'A' and s[i+1] = 'B'.
Each swap operation can be performed at most once per index.
Goal: Find the maximum number of such operations possible.

Algorithm:
- For each test case, iterate from left to right to count how many leading 'B's can be moved forward by swapping with preceding 'A's.
- Similarly, iterate from right to left to count how many trailing 'A's can be moved backward by swapping with succeeding 'B's.
- The total operations is the initial length minus these two counts.

Time Complexity: O(n) per test case
Space Complexity: O(1)
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
    long cnt(n - 1); // Initially, total possible adjacent swaps
    // Move from left to right, count leading 'B's that can be shifted by 'A's
    for (long p = 0; cnt > 0 && s[p] == 'B' && p < s.size(); p++) {
      --cnt; // Reduce counter as we can perform one operation on this position
    }
    // Move from right to left, count trailing 'A's that can be shifted by 'B's
    for (long p = n - 1; cnt > 0 && s[p] == 'A' && p >= 0; p--) {
      --cnt; // Reduce counter as we can perform one operation on this position
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/