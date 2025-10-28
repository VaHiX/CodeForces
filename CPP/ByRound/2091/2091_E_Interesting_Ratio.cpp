// Problem: CF 2091 E - Interesting Ratio
// https://codeforces.com/contest/2091/problem/E

// ==================================================================
// Problem: E. Interesting Ratio
// Purpose: Count pairs (a, b) such that 1 <= a < b <= n and F(a,b) = lcm(a,b)/gcd(a,b) is prime.
// Algorithm: Sieve of Eratosthenes to precompute primes, then for each query,
//            iterate through primes p and count how many multiples of p are <= n.
// Time Complexity: O(N log log N + T * pi(N)) where pi(N) is the number of primes <= N.
// Space Complexity: O(N)
// ==================================================================

#include <cstdio>
#include <vector>
int main() {
  const long N = 1e7 + 7;
  std::vector<bool> vb(N, 1); // Sieve array to mark primes
  vb[0] = vb[1] = 0;          // 0 and 1 are not primes
  for (long p = 2; p < vb.size(); p++) {
    if (!vb[p]) {
      continue; // Skip non-primes
    }
    for (long q = 2 * p; q < vb.size(); q += p) {
      vb[q] = 0; // Mark multiples of p as not prime
    }
  }
  std::vector<long> w; // Vector to store all primes up to N
  for (long p = 0; p < vb.size(); p++) {
    if (vb[p]) {
      w.push_back(p);
    }
  }
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long long cnt(0);
    for (long p = 0; p < w.size(); p++) {
      if (w[p] > n) {
        break; // No more primes <= n
      }
      cnt += n / w[p]; // Count how many multiples of prime p are <= n
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/