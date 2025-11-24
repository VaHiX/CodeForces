// Problem: CF 1454 D - Number into Sequence
// https://codeforces.com/contest/1454/problem/D

/*
 * Problem: D. Number into Sequence
 *
 * Purpose:
 *   Given an integer n > 1, decompose it into a sequence of integers such that:
 *   - Each element is greater than 1.
 *   - Product of the sequence equals n.
 *   - Each element divides the next one (i.e., a[i+1] % a[i] == 0).
 *   - Maximize the length of the sequence.
 *
 * Algorithm:
 *   - Factorize n into prime factors.
 *   - For each prime factor p with exponent e, we can create a subsequence:
 *     p, p^2, ..., p^e.
 *   - The goal is to maximize k (number of elements) in the final sequence.
 *   - To do that:
 *     1. Find prime factorization of n.
 *     2. For each prime factor p with power e:
 *        - Add p, p^2, ..., p^(e−1), p^e to result list.
 *     3. This gives a valid sequence where the last element is always divisible
 *        by the previous one since all are powers of the same base.
 *     4. The maximum number of elements is simply the number of prime factors (counted with multiplicity).
 *
 * Time Complexity:
 *   For each n, O(sqrt(n)) for factorization.
 *   Since sum of n is bounded to 10^10, and t <= 5000,
 *   total time complexity is acceptable within constraints.
 *
 * Space Complexity:
 *   O(log n) due to storing the factor map (at most log n distinct prime factors).
 */

#include <cstdio>
#include <map>
#include <utility>

typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::map<ll, ll> factors; // Store prime factor -> exponent mappings
    ll rem(n);                // Copy of n for factorization
    for (ll p = 2; p * p <= n; p++) {
      if (p * p > rem) {      // Early termination optimization
        break;
      }
      if (rem % p) {          // Not a divisor, skip
        continue;
      }
      while (rem % p == 0) {  // Count exponent of p in n
        ++factors[p];
        rem /= p;
      }
    }
    if (rem > 0) {            // Handle remaining prime factor > sqrt(n)
      factors[rem] = 1;
    }

    ll mx(0), div(1);
    // Find the prime with maximum exponent (this will be used to form subsequence)
    for (std::map<ll, ll>::iterator it = factors.begin(); it != factors.end();
         it++) {
      ll key = it->first;
      ll val = it->second;
      if (val > mx) {
        mx = val;
        div = key;
      }
    }
    // Output the number of terms in final sequence
    printf("%lld\n", mx);
    // Generate the required sequence by repeatedly dividing n by 'div'
    for (ll p = 1; p < mx; p++) {
      printf("%lld ", div);
      n /= div;
    }
    printf("%lld\n", n);  // Final term
  }
}


// https://github.com/VaHiX/codeForces/