// Problem: CF 1866 B - Battling with Numbers
// https://codeforces.com/contest/1866/problem/B

/*
B. Battling with Numbers

Task:
Given prime factorizations of two positive integers X and Y, compute the number of pairs (p, q) such that:
LCM(p, q) = X and GCD(p, q) = Y.

Approach:
- Both X and Y are given in their prime factorization forms.
- For any valid pair (p, q), let's denote:
    - p = ∏ p_i^(a_i)
    - q = ∏ p_i^(b_i)
  where each prime p_i is present in either X, Y, or both.

Key Insight:
- Let's define for each prime i:
    - x_i = exponent of prime i in X
    - y_i = exponent of prime i in Y
- From constraints on LCM and GCD:
    - max(a_i, b_i) = x_i (from LCM)
    - min(a_i, b_i) = y_i (from GCD)

So for prime i:
  a_i + b_i = x_i + y_i
  max(a_i, b_i) = x_i
  min(a_i, b_i) = y_i

This implies there are exactly 2 possibilities:
  1. a_i = x_i and b_i = y_i
  2. a_i = y_i and b_i = x_i

Therefore, if prime i is in both X and Y, then for that prime:
    - There are two possible combinations (either p or q get the larger power).
    - If x_i < y_i, it's impossible → return 0.

Time Complexity: O(N + M)
Space Complexity: O(N + M)

Algorithms/Techniques: Map-based prime exponent handling.
*/

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

int main() {
  const long long MOD = 998244353;
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::map<long, long> mx; // Maps primes from X to their exponents
  for (long p = 0; p < n; p++) {
    long k;
    scanf("%ld", &k);
    mx[a[p]] = k;
  }
  long m;
  scanf("%ld", &m);
  std::vector<long> b(m);
  bool possible(true);
  for (long p = 0; p < m; p++) {
    scanf("%ld", &b[p]);
  }
  std::map<long, long> my; // Maps primes from Y to their exponents
  for (long p = 0; p < m; p++) {
    long k;
    scanf("%ld", &k);
    my[b[p]] = k;
    if (!mx.count(b[p]) || my[b[p]] > mx[b[p]]) {
      possible = false;
    }
  }
  long long res(possible ? 1 : 0); // Start result as 1 if valid, else 0
  for (std::map<long, long>::iterator it = mx.begin();
       possible && it != mx.end(); it++) {
    long key = it->first;
    long val = it->second;
    if (!my.count(key) || my[key] < val) {
      res *= 2; // For primes in X only, two combinations
      res %= MOD;
    }
  }
  printf("%lld\n", res);
}


// https://github.com/VaHiX/codeForces/