// Problem: CF 2135 E2 - Beyond the Palindrome (Hard Version)
// https://codeforces.com/contest/2135/problem/E2

/*
E2. Beyond the Palindrome (Hard Version)
Purpose:
  Computes the number of distinct almost-palindrome binary strings of length n modulo 998244353.
  An almost-palindrome is a string where f(s) == f(reverse(s)), where f removes all "10" substrings
  from s repeatedly until none remain.

Algorithms:
  - Sieve of Euler for computing F and G functions for numbers up to 2*1e7
  - Preprocessing factorials and inverse factorials using modular exponentiation
  - Combinatorial counting with inclusion-exclusion principle

Time Complexity: O(n log log n + n) amortized over all test cases
Space Complexity: O(n) for arrays F, G, prime, fact, invfact

Techniques:
  - Modular arithmetic with custom add/sub functions
  - Fast exponentiation
  - Combinatorics with precomputed factorials
  - Euler sieve for number-theoretic functions
*/

#include <stdlib.h>
#include <iostream>

using namespace std;
using LL = long long;
const int MOD = 998244353;
const int LIM = 20000000 + 10;

inline int addmod(int a, int b) {
  a += b;
  return a >= MOD ? a - MOD : a;
}
inline int submod(int a, int b) {
  a -= b;
  return a < 0 ? a + MOD : a;
}
inline void inc(int &a, int b) {
  a += b;
  if (a >= MOD)
    a -= MOD;
}
inline void dec(int &a, int b) {
  a -= b;
  if (a < 0)
    a += MOD;
}

int prime[LIM], tot;                    // Store primes and count of primes
int F[LIM], G[LIM];                     // F[i] is the "reduced" or "final" value after processing
int fact[LIM], invfact[LIM];            // Precomputed factorials and inverse factorials

// Modular exponentiation function to compute b^e mod MOD
int modexp(int b, int e) {
  int res = 1;
  while (e) {
    if (e & 1)
      res = (LL)res * b % MOD;
    b = (LL)b * b % MOD;
    e >>= 1;
  }
  return res;
}

// Preprocessing step to calculate F and G arrays using sieve-like method
void preprocess(int n) {
  F[1] = 1;                             // Base case for F function
  for (int i = 2; i <= n; i++) {
    if (!F[i]) {
      prime[++tot] = i;                 // Mark new prime
      F[i] = G[i] = i + (i > 2);        // Initialize F and G values for primes
    }
    for (int j = 1; j <= tot; j++) {
      int p = prime[j];
      if (1LL * i * p > n)
        break;
      if (i % p == 0) {
        G[i * p] = G[i] * p + (j > 1);  // Update G using previous value
        F[i * p] = F[i] / G[i] * G[i * p]; // Update F based on G
        break;
      }
      F[i * p] = F[i] * (p + (j > 1));   // Multiply by prime plus correction term
      G[i * p] = p + (j > 1);            // Set G value for composite
    }
  }
  
  // Precompute factorials and inverse factorials
  fact[0] = 1;
  for (int i = 1; i <= n; i++)
    fact[i] = (LL)fact[i - 1] * i % MOD;
  invfact[n] = modexp(fact[n], MOD - 2); // Inverse of last factorial
  for (int i = n; i >= 1; i--)
    invfact[i - 1] = (LL)invfact[i] * i % MOD;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int T;
  cin >> T;
  preprocess(20000001); // Precompute up to max possible n

  while (T--) {
    int n;
    cin >> n;
    
    int res = 0;
    // Loop over all possible values of i used in combination with multinomial coefficients
    for (int i = 0; i <= n; i++) {
      int coef = (LL)invfact[i] * invfact[n - i] % MOD;     // Multinomial coefficient
      int diff = submod(F[abs(n - 2 * i - 1)], F[abs(n - 2 * i)]); // Difference of two F values
      res = (res + (LL)coef * diff) % MOD;
    }
    
    res = (LL)res * fact[n] % MOD; // Multiply by n! 
    
    // Double the result to account for symmetry
    res = addmod(res, res); 

    // Adjust final result according to whether n is odd or even
    if (n & 1)
      inc(res, modexp(2, n));   // Add 2^n if odd
    else
      dec(res, modexp(2, n));   // Subtract 2^n if even
    
    cout << res << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/