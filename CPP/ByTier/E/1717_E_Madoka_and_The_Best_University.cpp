// Problem: CF 1717 E - Madoka and The Best University
// https://codeforces.com/contest/1717/problem/E

/*
 * Problem: E. Madoka and The Best University
 * 
 * Purpose: Calculate sum of lcm(c, gcd(a, b)) for all triples (a, b, c) where a + b + c = n.
 * 
 * Algorithms/Techniques:
 * - Modular arithmetic with precomputed Euler's totient function
 * - Mathematical optimization using properties of gcd and lcm
 * - Efficient iteration over divisors and their multiples
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N)
 * 
 * The solution uses the identity that:
 * sum of lcm(c, gcd(a, b)) over all valid (a,b,c) with a+b+c = n
 * can be rewritten using divisor sums involving Euler's totient function.
 * 
 * Key observations:
 * 1. For fixed d = gcd(a,b), we can express a = d*a', b = d*b' where gcd(a',b')=1.
 * 2. Then c = n - a - b = n - d*(a'+b')
 * 3. The sum is rewritten in terms of divisors of n and applies Euler's totient function.
 * 
 * The code computes:
 * - Euler's totient function phi for all numbers up to N
 * - Then iterates over divisors d and multiples k of 2*d, accumulating the result
 * 
 * Input:
 *   Single integer N (3 <= N <= 10^5)
 * Output:
 *   Sum modulo 10^9 + 7
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
using ll = long long;
int main() {
  ios_base::sync_with_stdio(0);
  const ll mod = 1e9 + 7;
  ll N;
  cin >> N;
  vector<ll> phi(N);
  rep(i, 1, N) phi[i] = i;
  rep(d, 2, N) if (phi[d] == d) for (ll i = d; i < N; i += d) phi[i] -=
      phi[i] / d;
  ll ans = 0;
  rep(d, 1, N) for (ll k = 2 * d; k < N; k += d) ans =
      (ans + lcm(N - k, d) % mod * phi[k / d] % mod) % mod;
  cout << ans << "\n";
}


// https://github.com/VaHiX/CodeForces/