// Problem: CF 1879 C - Make it Alternating
// https://codeforces.com/contest/1879/problem/C

/*
C. Make it Alternating
Algorithms/Techniques: String processing, combinatorics, counting operations to make alternating string.

Time Complexity: O(n) where n is the length of the input string s (linear pass through string and computation)
Space Complexity: O(1) - only using a few variables for computation

Task:
Given a binary string s, find:
1. Minimum number of operations to make it alternating (delete characters)
2. Number of different shortest sequences of such operations modulo 998244353

Approach:
- For each group of consecutive identical characters, we can keep one and delete the rest.
- The minimum operations = total length - number of unique groups + 1
- To compute number of ways:
  - For each group of size cnt, there are cnt choices for which element to keep
  - Multiply all such choices together
  - Then multiply by factorial of (sum of deletions) because we can delete in any order among deletion operations
*/

#include <iostream>
#include <string>

typedef long long ll;
int main() {
  const ll MOD = 998244353;
  ll t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    s += "_"; // add sentinel to simplify loop logic
    ll cnt(1), sum(0), prod(1);
    for (long p = 1; p < s.size(); p++) {
      if (s[p - 1] == s[p]) {
        ++cnt;
        continue;
      }
      // When character changes:
      // - add (cnt - 1) to sum (number of deletions in this group)
      // - multiply prod by cnt (choices for which character to keep)
      sum += (cnt - 1);
      prod = (prod * cnt) % MOD;
      cnt = 1;
    }
    // Multiply result by factorial of number of deletions
    for (int p = 2; p <= sum; p++) {
      prod = (prod * p) % MOD;
    }
    std::cout << sum << " " << prod << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/