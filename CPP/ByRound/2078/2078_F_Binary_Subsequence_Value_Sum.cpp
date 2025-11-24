// Problem: CF 2078 F - Binary Subsequence Value Sum
// https://codeforces.com/contest/2078/problem/F

/*
F. Binary Subsequence Value Sum
Algorithms/Techniques: Math, Prefix Sums, Modular Arithmetic, Efficient Updates

Time Complexity: O(n + q) per test case, where n is length of string and q is number of queries.
Space Complexity: O(n) for storing the string and auxiliary variables.

The problem uses a mathematical approach to count the contribution of each subsequence
to the total score sum. It precomputes initial value using formula:
cur = n*(n+1)/2 + 2*cnt*(cnt - n) - 1
where cnt is number of zeros in string.
Each query updates this value efficiently by tracking how changing a bit affects the computation.
The modular inverse INV4 is computed to avoid division.

Key formulas used:
- F(v, l, r) = (r - l + 1) - 2 * zero_count
- Score of subsequence = max(F(v, 1, i) * F(v, i+1, |v|))
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;
const int MOD = 998244353;
// Precomputed inverse of 4 modulo MOD
const int INV4 = 1LL * (MOD + 1) * (MOD + 1) / 4 % MOD;
int t;
int n, q;
string s;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  for (cin >> t; t--;) {
    cin >> n >> q;
    cin >> s;
    // Count number of zeros in initial string
    int cnt = count(begin(s), end(s), '0');
    // Compute initial sum using derived formula
    long long cur = 1LL * n * (n + 1) / 2 + 2LL * cnt * (cnt - n) - 1;
    // Precompute 2^(n-1) % MOD for final scaling factor
    int p2 = 1;
    for (int i = 1; i < n; i++)
      if ((p2 += p2) >= MOD)
        p2 -= MOD;
    for (int i = 1, x; i <= q; i++) {
      cin >> x;
      // Flip the character at index x-1 (0-based indexing)
      if ((s[--x] ^= 1) == '0')
        cur += 4 * cnt++ - 2 * (n - 1);   // Update cur when a 0 is added
      else
        cur -= 4 * cnt-- - 2 * (n + 1);   // Update cur when a 0 is removed
      // Output result after applying inverse and modular scaling
      cout << cur % MOD * p2 % MOD * INV4 % MOD << '\n';
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/