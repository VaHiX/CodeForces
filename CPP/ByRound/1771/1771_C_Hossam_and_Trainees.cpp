// Problem: CF 1771 C - Hossam and Trainees
// https://codeforces.com/contest/1771/problem/C

/*
 * Problem: C. Hossam and Trainees
 * 
 * Algorithm/Techniques: 
 * - Precompute all primes up to sqrt(10^9) ≈ 32166 using Sieve of Eratosthenes.
 * - For each number, find its prime factors and check if any prime factor has been seen before.
 * - If yes, then there exists a common divisor >= 2, so answer is "YES".
 * - Time Complexity: O(n * sqrt(max_a)) per test case, where max_a <= 1e9.
 * - Space Complexity: O(π(sqrt(max_a)) + n) where π(x) denotes the number of primes <= x.
 *
 * The approach is based on the observation that two numbers have a common divisor >= 2
 * if and only if they share at least one prime factor.
 */

#include <stdio.h>
#include <set>
#include <utility>

using namespace std;
int n;
set<int> mp;
int prime[32170], tot;

void run() {
  mp.clear();
  scanf("%d", &n);
  bool f = false;
  for (int i = 1, x; i <= n; i++) {
    scanf("%d", &x);
    // Iterate through precomputed primes up to sqrt(x)
    for (int j = 1; j <= tot && prime[j] <= x / prime[j]; j++)
      if (x % prime[j] == 0) {
        // If we've already seen this prime factor, the answer is YES
        f |= !mp.insert(prime[j]).second;
        // Remove all occurrences of this prime from x
        while (x % prime[j] == 0)
          x /= prime[j];
      }
    // If x > 1 after factorization, it's a prime factor itself
    if (x > 1)
      f |= !mp.insert(x).second;
  }
  printf("%s\n", f ? "YES" : "NO");
}

int main() {
  // Precompute all primes up to sqrt(10^9)
  for (int i = 2; i <= 32166; i++) {
    bool f = true;
    for (int j = 2; j <= i / j; j++)
      if (i % j == 0)
        f = false;
    if (f)
      prime[++tot] = i;
  }
  int t;
  scanf("%d", &t);
  while (t--)
    run();
  return 0;
}


// https://github.com/VaHiX/CodeForces/