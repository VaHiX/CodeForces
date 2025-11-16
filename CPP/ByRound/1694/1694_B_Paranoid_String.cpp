// Problem: CF 1694 B - Paranoid String
// https://codeforces.com/contest/1694/problem/B

/*
B. Paranoid String
Algorithm: For each position, we calculate how many substrings ending at this position are paranoid.
Time Complexity: O(n) per test case
Space Complexity: O(1)

A string is paranoid if it can be reduced to a single character using:
- Replace "01" with "1"
- Replace "10" with "0"

Key insight: A substring is paranoid if and only if it has no two consecutive identical characters,
and the total number of such substrings can be computed incrementally.
*/

#include <iostream>
#include <string>

typedef long long ll;
int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    ll res(n); // Every single character is paranoid, so start with n
    for (long p = 1; p < n; p++) {
      // If adjacent characters differ, add the position index to result
      // This accounts for all substrings ending at p that are paranoid
      res += (s[p - 1] != s[p]) * p;
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/