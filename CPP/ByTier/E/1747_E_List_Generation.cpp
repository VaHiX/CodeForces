// Problem: CF 1747 E - List Generation
// https://codeforces.com/contest/1747/problem/E

/*
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(N) preprocessing + O(min(n,m)) per query, where N = 5*10^6
Space Complexity: O(N)

This problem asks to compute the sum of lengths of all valid pairs of arrays (a, b)
that satisfy specific constraints. The solution uses combinatorics and precomputed
factorials and powers of 2 to efficiently calculate the result.

The key idea is that for each valid pair (a,b), the difference between consecutive
elements (a[i] - a[i-1], b[i] - b[i-1]) must be non-decreasing and their sum must be
different from the previous step. This can be modeled in terms of choosing positions
where the increment in a or b happens.

We use the formula derived using inclusion-exclusion and combinations:
For each i (0 <= i <= min(n,m)), we compute:
C(n, i) * C(m, i) * (s * 2^(s-1) + (i+2) * 2^s) % mod, 
where s = n + m - i - 1.

Preprocessing is done to compute factorials, inverse factorials and powers of 2.
*/

#include <stdio.h>
#include <algorithm>

const int N = 1e7 + 5, mod = 1e9 + 7;
long long t, n, m, po2[N], po[N], ipo[N];

// Compute combination C(n, m)
long long c(long long n, long long m) {
  return po[n] * ipo[m] % mod * ipo[n - m] % mod;
}

// Fast exponentiation
long long qpow(long long a, long long b) {
  long long ans = 1;
  while (b) {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod, b >>= 1;
  }
  return ans;
}

int main() {
  // Precompute factorials and powers of 2
  po[0] = 1, ipo[1] = 1, po2[0] = 1;
  for (long long i = 1; i < N; i++)
    po[i] = po[i - 1] * i % mod, po2[i] = po2[i - 1] * 2 % mod;
  // Precompute inverse factorials
  ipo[N - 1] = qpow(po[N - 1], mod - 2);
  for (int i = N - 2; i >= 0; i--)
    ipo[i] = (ipo[i + 1] * (i + 1)) % mod;
  
  scanf("%lld", &t);
  while (t--) {
    scanf("%lld%lld", &n, &m);
    long long ans = 0;
    for (long long i = 0; i <= std::min(n, m); i++) {
      long long s = n + m - i - 1;
      ans = (ans + c(n, i) * c(m, i) % mod *
                       (s * po2[s - 1] % mod + (i + 2) * po2[s] % mod) % mod) %
            mod;
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/