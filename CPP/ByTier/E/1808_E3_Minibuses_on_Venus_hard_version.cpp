// Problem: CF 1808 E3 - Minibuses on Venus (hard version)
// https://codeforces.com/contest/1808/problem/E3

/*
 * Purpose: This code computes the number of "lucky" tickets on Venus, where a
 * ticket is lucky if one of its digits equals the sum of the other digits
 * modulo k. The solution uses mathematical techniques including modular
 * exponentiation and generating functions.
 *
 * Algorithms/Techniques:
 *   - Modular exponentiation for fast computation of powers
 *   - Mathematical analysis of digit sums and modular arithmetic
 *   - Generating function approach with inclusion of symmetry for even k
 *
 * Time Complexity: O(k * log(n) + k^2)
 * Space Complexity: O(1)
 */
#include <iostream>
#include <stdio.h>
#include <utility>
#include <vector>

#define pb push_back
#define pob pop_back
#define endl '\n'
using namespace std;
template <typename hd, typename tl> void chkmin(hd &a, tl b) {
  if (b < a)
    a = b;
}
template <typename hd, typename tl> void chkmax(hd &a, tl b) {
  if (a < b)
    a = b;
}
typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<PII> VPII;
const int MX = 200005;
const int inf = 1000000008;
LL mod;
LL modexp(LL a, LL n) {
  a = a % mod;
  LL rlt = 1;
  for (; n; n /= 2) {
    if (n & 1)
      rlt = rlt * a % mod;
    a = a * a % mod;
  }
  return rlt;
}
LL calc(LL n, LL k) {
  if (k == 1)
    return 1;
  LL x = (k - 1) * modexp(k, mod - 2) % mod; // Modular inverse
  x = (modexp(x, n) - 1) * modexp(x - 1, mod - 2) %
      mod;                               // Geometric series formula
  LL rlt = x * modexp(k, n - 1) % mod;   // Compute the final result term
  rlt = (rlt - modexp(-1, n - 1)) % mod; // Adjust based on parity
  for (int m = 0; m < k; m++) {
    if (((n - 2) % k) * m % k == 0)          // Check condition for symmetry
      rlt = (rlt + modexp(-1, n - 1)) % mod; // Add symmetric contribution
  }
  return (rlt % mod + mod) % mod; // Ensure positive result
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  LL n, k;
  cin >> n >> k >> mod;
  if (k & 1) // If k is odd, directly calculate
    cout << calc(n, k) << endl;
  else { // If k is even, adjust using symmetry
    LL rlt = calc(n, k / 2) * modexp(2, n - 1) % mod;
    cout << rlt << endl;
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/