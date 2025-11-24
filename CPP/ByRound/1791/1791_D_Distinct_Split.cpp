// Problem: CF 1791 D - Distinct Split
// https://codeforces.com/contest/1791/problem/D

/*
D. Distinct Split
Algorithm: Preprocessing + Two Pointers
Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) for storing prefix and suffix arrays.

The problem requires splitting a string into two non-empty parts such that 
the sum of distinct characters in both parts is maximized.

Approach:
1. Precompute prefix array 'left' where left[i] = number of distinct characters from start to i.
2. Precompute suffix array 'right' where right[i] = number of distinct characters from i to end.
3. For each valid split point (from 1 to n-1), compute sum of left[p-1] + right[p].
4. Return the maximum such sum.

This solution uses two passes through the string to build prefix and suffix arrays,
and one pass to find the optimal split, resulting in linear time complexity.
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
    // left[p] stores the count of distinct characters from index 0 to p
    std::vector<long> left(s.size(), 0), right(s.size(), 0);
    long cnt(0);
    // v tracks which characters have been seen
    std::vector<bool> v(26, false);
    
    // Build prefix array: left[p] = distinct chars from 0 to p
    for (long p = 0; p < s.size(); p++) {
      int cur = s[p] - 'a';
      if (!v[cur]) {
        ++cnt;
        v[cur] = true;
      }
      left[p] = cnt;
    }

    // Reset and build suffix array: right[p] = distinct chars from p to end
    cnt = 0;
    v = std::vector<bool>(26, false);
    for (long p = s.size() - 1; p >= 0; p--) {
      int cur = s[p] - 'a';
      if (!v[cur]) {
        ++cnt;
        v[cur] = true;
      }
      right[p] = cnt;
    }

    // Find maximum f(a) + f(b) for valid split points
    long res(0);
    for (long p = 1; p < s.size(); p++) {
      long tst = left[p - 1] + right[p];
      res = (res > tst) ? res : tst;
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/