// Problem: CF 2135 E2 - Beyond the Palindrome (Hard Version)
// https://codeforces.com/contest/2135/problem/E2

/*
E2. Beyond the Palindrome (Hard Version)

Algorithms/Techniques:
- Number theory sieve for computing F[n] values using multiplicative functions
- Fast exponentiation with modular arithmetic
- Preprocessing factorial and inverse factorial arrays for combinations
- Dynamic programming with inclusion-exclusion principle

Time Complexity: O(n log log n + T * n)
Space Complexity: O(n)

This problem counts the number of "almost-palindromes" — binary strings s where f(s) == f(reverse(s)).
The function f removes all "10" patterns simultaneously until none remain.
We use a sieve approach to compute F[i] which represents some function related to f(i).
Then we do inclusion-exclusion over the parity of positions, using combinations and precalculated factorials.
*/

#include <iostream>
#include <stdlib.h>
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

int prime[LIM], tot; // Store primes and their count
int F[LIM], G[LIM];   // Computed values related to sieve-based function F[i]
int fact[LIM], invfact[LIM]; // Precomputed factorials and inverse factorials

// Fast modular exponentiation
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

// Precompute F[i] and G[i] using sieve method
void preprocess(int n) {
  F[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!F[i]) {
      prime[++tot] = i;
      F[i] = G[i] = i + (i > 2); // Initialize F and G based on prime property
    }
    for (int j = 1; j <= tot; j++) {
      int p = prime[j];
      if (1LL * i * p > n)
        break;
      if (i % p == 0) {
        G[i * p] = G[i] * p + (j > 1); // Compute G for composite numbers
        F[i * p] = F[i] / G[i] * G[i * p]; // Update F based on earlier computed values
        break;
      }
      F[i * p] = F[i] * (p + (j > 1)); // Compute F for new primes
      G[i * p] = p + (j > 1);          // Set G accordingly
    }
  }
  fact[0] = 1;
  for (int i = 1; i <= n; i++)
    fact[i] = (LL)fact[i - 1] * i % MOD; // Compute factorials mod MOD

  invfact[n] = modexp(fact[n], MOD - 2); // Inverse of last factorial
  for (int i = n; i >= 1; i--)
    invfact[i - 1] = (LL)invfact[i] * i % MOD; // Compute inverse factorials in reverse
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  preprocess(20000001); // Initialize sieve and arrays for up to 2e7 elements

  while (T--) {
    int n;
    cin >> n;
    int res = 0;

    // Include contribution of all pairs via combination
    for (int i = 0; i <= n; i++) {
      int coef = (LL)invfact[i] * invfact[n - i] % MOD;          // Binomial coefficient mod MOD
      int diff = submod(F[abs(n - 2 * i - 1)], F[abs(n - 2 * i)]); // Difference in F-values
      res = (res + (LL)coef * diff) % MOD;                      // Accumulate weighted difference
    }

    res = (LL)res * fact[n] % MOD; // Scale by n!

    res = addmod(res, res);     // Double the result due to inclusion-exclusion step

    if (n & 1)
      inc(res, modexp(2, n));   // If odd: Add 2^n contribution
    else
      dec(res, modexp(2, n));   // If even: Subtract 2^n contribution

    cout << res << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/