// Problem: CF 1916 H1 - Matrix Rank (Easy Version)
// https://codeforces.com/contest/1916/problem/H1

/*
 * Problem: H1. Matrix Rank (Easy Version)
 * 
 * Purpose: Count the number of n×n matrices over the finite field GF(p) with rank exactly r, for r from 0 to k.
 * 
 * Algorithm:
 * - Uses combinatorial formulas involving the Gaussian binomial coefficients (q-analogue of binomial coefficients).
 * - The number of matrices of rank r is given by:
 *   (number of ways to choose r linearly independent rows) × (number of ways to complete to full rank matrix)
 * - For a field of size p, this can be computed using:
 *   (p^n - p^(n-1)) * (p^n - p^(n-2)) * ... * (p^n - p^0) / (p^r - p^0) * (p^r - p^1) * ... * (p^r - p^(r-1))
 * - This formula is simplified using precomputed powers of p and modular arithmetic.
 * 
 * Time Complexity: O(k)
 * Space Complexity: O(k)
 */

#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

// Fast exponentiation modulo MOD
ll fast_exp(ll base, ll exp, ll mod) {
  ll result = 1;
  base %= mod;
  while (exp > 0) {
    if (exp & 1)
      result = (result * base) % mod;
    base = (base * base) % mod;
    exp >>= 1;
  }
  return result;
}

// Modular multiplicative inverse using Fermat's little theorem (since MOD is prime)
ll mod_inverse(ll a, ll mod) { return fast_exp(a, mod - 2, mod); }

int main() {
  ll n, p, k;
  cin >> n >> p >> k;
  
  // Precompute powers of p up to k
  vector<ll> powers(k + 1, 1);
  for (ll m = 1; m <= k; ++m) {
    powers[m] = (powers[m - 1] * p) % MOD;
  }

  // Precompute p^n modulo MOD
  ll pn = fast_exp(p, n, MOD);
  
  // dpn[r]: numerator part of formula for rank r
  // dpd[r]: denominator part of formula for rank r
  vector<ll> dpn(k + 1, 1), dpd(k + 1, 1);

  for (ll r = 1; r <= k; ++r) {
    // (p^n - p^(r-1))^2 term in numerator
    ll ft = (pn - powers[r - 1] + MOD) % MOD;
    ft = ft * ft % MOD;
    dpn[r] = (dpn[r - 1] * (ft)) % MOD;
    
    // (p^r - 1) term in denominator
    ll fr = (powers[r] - 1 + MOD) % MOD;
    dpd[r] = dpd[r - 1] * (fr) % MOD;
    
    // Multiply by p^(r-1) for the full denominator term
    dpd[r] *= (powers[r - 1]);
    dpd[r] %= MOD;
  }

  // Final results for each rank r from 0 to k
  vector<ll> results(k + 1, 0);
  for (ll r = 0; r <= k; ++r) {
    results[r] = (dpn[r] * mod_inverse(dpd[r], MOD)) % MOD;
  }
  
  // Output results
  for (ll r = 0; r <= k; ++r) {
    cout << results[r] << " ";
  }
  cout << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/