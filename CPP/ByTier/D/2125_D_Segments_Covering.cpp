// Problem: CF 2125 D - Segments Covering
// https://codeforces.com/contest/2125/problem/D

/*
D. Segments Covering
Algorithms/Techniques: Dynamic Programming with Segment Coverage Probability Computation
Time Complexity: O(n * log(mod) + m)
Space Complexity: O(n + m)

This code computes the probability that each cell in a linear strip of size m is covered by exactly one segment.
Segments are defined with start/end points and a probability of existence. The approach uses dynamic programming
with inclusion-exclusion principles applied through preprocessing and modular arithmetic for efficient computation.

The algorithm:
1. Preprocess each segment's contribution to coverage probability using inclusion-exclusion logic.
2. Use dynamic programming: f[i] represents the probability that cell i is covered by exactly one segment.
3. Multiply final result by overall probability of all segments being active (mul).

*/

#include <cstdio>
#include <utility>
#include <vector>
int n, m, mod = 998244353, p, q, ll, rr, mul = 1, f[200005];
int qpow(int a, int x) {
  int s = 1;
  for (; x; x >>= 1, a = 1ll * a * a % mod)
    if (x & 1)
      s = 1ll * s * a % mod;
  return s;
}
std::vector<std::pair<int, int>> g[200005];
int main() {
  scanf("%d%d", &m, &n);
  while (m--) {
    scanf("%d%d%d%d", &ll, &rr, &p, &q);
    p = 1ll * p * qpow(q, mod - 2) % mod; // Normalize probability p/q
    g[rr].push_back({ll, 1ll * p * qpow((mod + 1 - p) % mod, mod - 2) % mod}); // Add segment contribution
    mul = 1ll * mul * (mod + 1 - p) % mod; // Accumulate probability of segments not conflicting
  }
  f[0] = 1;
  for (int i = 1; i <= n; i++)
    for (std::pair<int, int> j : g[i])
      f[i] = (f[i] + 1ll * j.second * f[j.first - 1]) % mod; // Dynamic programming step
  printf("%lld", 1ll * mul * f[n] % mod); // Final result
}


// https://github.com/VaHiX/codeForces/