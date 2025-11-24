// Problem: CF 1034 A - Enlarge GCD
// https://codeforces.com/contest/1034/problem/A

/*
 * Problem: Enlarge GCD
 * Purpose: Given a list of positive integers, find the minimum number of elements to remove 
 *          such that the GCD of the remaining elements is strictly greater than the original GCD.
 * 
 * Algorithms/Techniques:
 *   - Sieve of Eratosthenes for prime factorization
 *   - Prime factorization and counting for each prime divisor
 *   - Greedy approach to find maximum count of any prime divisors among all elements
 * 
 * Time Complexity: O(M log log M + n * log(max(a_i)))
 *   - M = 15,000,000 (max possible value of a[i])
 *   - Preprocessing primes via sieve: O(M log log M)
 *   - For each element, factorizing and counting prime factors: O(n * log(max(a_i)))
 * 
 * Space Complexity: O(M)
 *   - Arrays to store primes and prime factorization information: O(M)
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
#define MN 300000
#define MX 15000000

int a[MN + 5], u[MX + 5], p[MX + 5], pn, s[MX + 5];

// Standard GCD implementation using Euclidean algorithm
int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

int main() {
  int n, i, j, g, x, ans = 0;

  // Sieve of Eratosthenes to precompute smallest prime factor for each number up to MX
  for (i = 2; i <= MX; ++i) {
    if (!u[i])
      u[i] = p[++pn] = i;        // If u[i] is 0, then i is a prime
    for (j = 1; i * p[j] <= MX; ++j) {
      u[i * p[j]] = p[j];        // Mark smallest prime factor of i*p[j]
      if (i % p[j] == 0)
        break;                   // Break to avoid duplicate factors
    }
  }

  scanf("%d", &n);
  for (g = 0, i = 1; i <= n; ++i)
    scanf("%d", &a[i]), g = gcd(g, a[i]);  // Compute overall GCD of array

  // For each number in the array, decompose it into prime factors and count how many times
  // each prime occurs as a factor (after dividing by initial GCD)
  for (i = 1; i <= n; ++i)
    for (j = a[i] / g; j > 1;)       // Divide by current GCD to normalize values
      for (++s[x = u[j]]; u[j] == x;) // Increment count of prime factor x
        j /= u[j];                     // Remove the prime factor from j

  // Find the maximum number of times any prime appears as a common factor
  for (i = 1; i <= MX; ++i)
    ans = max(ans, s[i]);

  // Output result:
  // If no prime appeared more than once, no improvement is possible (-1)
  // Else, remove all numbers that don't contain the most frequent prime factor
  printf("%d", ans ? n - ans : -1);

  return 0;
}


// https://github.com/VaHiX/codeForces/