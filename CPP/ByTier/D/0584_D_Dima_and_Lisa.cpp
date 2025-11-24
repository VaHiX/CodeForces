// Problem: CF 584 D - Dima and Lisa
// https://codeforces.com/contest/584/problem/D

/*
 * Problem: D. Dima and Lisa
 * Purpose: Represent an odd number n as the sum of at most 3 primes.
 * Algorithm:
 *   - If n is prime, output it as a single prime.
 *   - If n - 2 is prime, output 2 and n - 2.
 *   - Otherwise, search for two primes p and q such that n - p and q are primes,
 *     and p - q is also prime. This ensures n = (n - p) + (p - q) + q.
 * Time Complexity: O(sqrt(n) * n) in worst case due to nested loops and checks.
 * Space Complexity: O(1) - only using a few variables.
 */

#include <cmath>
#include <cstdio>
bool isPrime(long x) {
  if (x <= 1) {
    return 0;
  }
  long a = sqrt(x);
  for (long p = 2; p <= a; p++) {
    if (x % p == 0) {
      return false;
    }
  }
  return true;
}
int main() {
  long n;
  scanf("%ld\n", &n);
  if (isPrime(n)) {
    printf("1\n%ld\n", n);
    return 0;
  }
  if (isPrime(n - 2)) {
    printf("2\n2 %ld\n", n - 2);
    return 0;
  }
  for (long p = 2; p < n; p += 2) {
    if (!isPrime(n - p)) {
      continue;
    }
    for (long q = 2; q < p; q++) {
      if (!isPrime(q) || !isPrime(p - q)) {
        continue;
      }
      printf("3\n%ld %ld %ld\n", n - p, p - q, q);
      return 0;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/