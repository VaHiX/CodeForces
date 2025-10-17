// Problem: CF 1762 C - Binary Strings are Fun
// https://codeforces.com/contest/1762/problem/C

#include <stdio.h>
#include <iostream>
#include <string>

typedef long long ll;
int main() {
  const ll MOD = 998244353;
  ll t;
  std::cin >> t;
  while (t--) {
    ll n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    ll cnt(0), cur(1);
    for (ll p = 0; p < s.size(); p++) {
      // If current character is same as previous, double the number of ways to form good extensions
      if (p && s[p - 1] == s[p]) {
        cur = 2 * cur % MOD;
      } else {
        // Reset count when character changes
        cur = 1;
      }
      // Add current number of ways to total count
      cnt = (cnt + cur) % MOD;
    }
    printf("%lld\n", cnt);
  }
}
/*
 * Problem: C. Binary Strings are Fun
 *
 * Description:
 * Given a binary string s of length n, compute the sum over all prefixes of s,
 * where each prefix contributes the number of "good" extensions of that prefix.
 * A good extension of a binary string of length k is one of length 2k-1 such that
 * each odd-indexed character (in the extension) equals the median of its prefix.
 *
 * Algorithm:
 * - Process the string from left to right
 * - For each position, maintain a running count (`cur`) of valid "good" extensions that can be formed ending at this point
 * - If two consecutive characters are the same, the number of valid extensions doubles (as we can choose either 0 or 1 for middle element in extension)
 * - Otherwise, reset to 1 since no additional choices are available
 * - Accumulate total count modulo 998244353
 *
 * Time Complexity: O(n), where n is the length of input string
 * Space Complexity: O(1) (not counting the input string storage)
 */

// https://github.com/VaHiX/codeForces/