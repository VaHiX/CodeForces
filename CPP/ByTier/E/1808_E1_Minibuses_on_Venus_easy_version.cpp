// Problem: CF 1808 E1 - Minibuses on Venus (easy version)
// https://codeforces.com/contest/1808/problem/E1

/*
Purpose: This code computes the number of "lucky" tickets on Venus, where a
ticket is lucky if one of its digits equals the sum of all other digits modulo
k. The algorithm uses mathematical transformations and modular exponentiation
for efficient computation.

Algorithms/Techniques:
- Modular exponentiation (fast power)
- Mathematical transformation using geometric series
- Handling even and odd k cases separately
- Fermat's little theorem for modular inverse when k is odd
- Inclusion of modular arithmetic to avoid overflow

Time Complexity: O(k * log(mod)) due to modular exponentiations and loop over k
digits. Space Complexity: O(1) as we only use a constant amount of extra space.
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

// Fast modular exponentiation: computes (a^n) % mod efficiently
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

// Calculates the number of lucky tickets for given n and k
LL calc(LL n, LL k) {
  if (k == 1)
    return 1;
  LL x = (k - 1) * modexp(k, mod - 2) % mod; // Modular inverse of k
  x = (modexp(x, n) - 1) * modexp(x - 1, mod - 2) %
      mod;                               // Geometric series result
  LL rlt = x * modexp(k, n - 1) % mod;   // Multiply by k^(n-1)
  rlt = (rlt - modexp(-1, n - 1)) % mod; // Subtract (-1)^(n-1)

  // Loop for checking if sum of remaining digits matches one digit
  for (int m = 0; m < k; m++) {
    if (((n - 2) % k) * m % k == 0)
      rlt = (rlt + modexp(-1, n - 1)) % mod;
  }
  return (rlt % mod + mod) % mod; // Ensure positive result
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  LL n, k;
  cin >> n >> k >> mod;

  // If k is odd, directly compute using calc
  if (k & 1)
    cout << calc(n, k) << endl;
  else {
    // If k is even, reduce to half the base and adjust for powers of 2
    LL rlt = calc(n, k / 2) * modexp(2, n - 1) % mod;
    cout << rlt << endl;
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/