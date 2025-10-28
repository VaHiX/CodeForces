// Problem: CF 1062 B - Math
// https://codeforces.com/contest/1062/problem/B

/*
B. Math
Algorithm: Prime factorization and optimal operation counting
Time Complexity: O(sqrt(n))
Space Complexity: O(log n)

The problem requires finding the minimum value of n using multiplication and square root operations,
and the minimum number of such operations to achieve it.

Approach:
1. Factorize n into prime factors.
2. For each prime factor p with exponent e, we can reduce the exponent by taking sqrt operations
   (since sqrt(p^e) = p^(e/2)).
3. To minimize n, we want all exponents to be 1 after operations. The number of operations needed
   is based on how many times we need to take sqrts to get each exponent down to 1.
4. Then calculate the final result as product of primes with exponent 1.

Key steps in code:
- Factor n into prime factors and count respective exponents
- Compute minimum value (product of distinct primes)
- Determine minimum operations needed based on max exponent
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> div, h; // div stores prime factors, h stores their exponents
  long m(n);
  for (long p = 2; m > 1 && p <= n; p++) {
    if (m % p) {
      continue;
    }
    long cnt(0);
    while (m % p == 0) {
      m /= p;
      ++cnt;
    }
    div.push_back(p);
    h.push_back(cnt);
  }
  long res(1);
  for (long p = 0; p < div.size(); p++) {
    res *= div[p];
  }
  long cnt(0), z(h.size() ? h[0] : 1), w(1);
  bool same(true);
  for (long p = 1; p < h.size(); p++) {
    if (h[p] != h[p - 1]) {
      same = false;
    }
    z = (z > h[p]) ? z : h[p];
  }
  long moves(0);
  while (w < z) {
    w *= 2;
    ++moves;
  }
  moves += (!same || w != z); // Add move if there are different exponents or final exponent wasn't reached
  printf("%ld %ld\n", res, moves);
  return 0;
}


// https://github.com/VaHiX/codeForces/