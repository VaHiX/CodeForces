// Problem: CF 2025 B - Binomial Coefficients, Kind Of
// https://codeforces.com/contest/2025/problem/B

/*
B. Binomial Coefficients, Kind Of
Algorithms/Techniques: Precomputed powers of 2 using dynamic programming
Time Complexity: O(max(n)) for precomputation + O(t) for queries
Space Complexity: O(max(n)) for storing precomputed values

The problem involves computing "wrong" binomial coefficients based on a faulty recurrence relation:
C[n][k] = C[n][k-1] + C[n-1][k-1] (instead of the correct C[n][k] = C[n-1][k] + C[n-1][k-1])

This leads to a pattern where C[n][k] = 2^k for k < n, and C[n][n] = 1.
We precompute powers of 2 modulo 1e9+7 to answer queries efficiently.
*/

#include <cstdio>
#include <vector>
int main() {
  const long MOD = 1e9 + 7;
  std::vector<long> v(1e5 + 7, 1); // Precompute powers of 2
  for (long p = 1; p < v.size(); p++) {
    v[p] = (2 * v[p - 1]) % MOD; // Compute 2^p mod MOD
  }
  long t;
  scanf("%ld", &t);
  std::vector<long> wn(t), wk(t); // Read input pairs
  for (long p = 0; p < t; p++) {
    scanf("%ld", &wn[p]);
  }
  for (long p = 0; p < t; p++) {
    scanf("%ld", &wk[p]);
  }
  for (long p = 0; p < t; p++) {
    // If k < n, result is 2^k; otherwise it's 1
    printf("%ld\n", (wk[p] < wn[p]) ? v[wk[p]] : 1);
  }
  puts("");
}


// https://github.com/VaHiX/codeForces/