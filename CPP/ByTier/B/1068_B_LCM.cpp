// Problem: CF 1068 B - LCM
// https://codeforces.com/contest/1068/problem/B

/*
 * Problem: B. LCM
 * Purpose: Find the number of distinct values of lcm(a, b) / a for all a in [1, 10^18]
 * Algorithm: 
 *   - For each divisor d of b, we compute how many times d divides b.
 *   - The number of distinct values is equal to the product of (1 + count of each prime factor).
 *   - This works because lcm(a, b) / a = b / gcd(a, b), and for different values of gcd(a, b),
 *     we have different results. These correspond to divisors of b.
 * 
 * Time Complexity: O(sqrt(b))
 * Space Complexity: O(log b)
 */

#include <cstdio>
#include <map>
#include <utility>

typedef long long ll;

int main() {
  ll b;
  scanf("%lld", &b);
  std::map<ll, ll> m; // Map to store prime factors and their counts
  ll upper = b;
  for (ll p = 2; p * p <= upper; p++) { // Iterate up to sqrt(b)
    while (b % p == 0) { // While p divides b
      ++m[p]; // Increment count of prime factor p
      b /= p; // Divide b by p
    }
  }
  if (b > 1) { // If b is still greater than 1, then it's a prime factor
    ++m[b];
  }
  ll total(1); // Result to be computed
  for (std::map<ll, ll>::iterator it = m.begin(); it != m.end(); it++) {
    total *= (1 + it->second); // Multiply by (1 + count of each prime factor)
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/codeForces/