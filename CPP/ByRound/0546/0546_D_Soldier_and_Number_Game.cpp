// Problem: CF 546 D - Soldier and Number Game
// https://codeforces.com/contest/546/problem/D

/*
 * Problem: Soldier and Number Game
 * Algorithm: Sieve of Eratosthenes + Preprocessing
 *
 * Purpose:
 *   Given n = a! / b! (where a >= b), find the maximum number of rounds
 *   in which we can divide n by a factor x > 1 until n becomes 1.
 *   Each round reduces n to n / x, where x is a factor of n.
 *
 * Approach:
 *   - Preprocess prime numbers up to 5,000,000 using sieve.
 *   - For each number i, compute how many times it can be divided by its
 * smallest prime factor.
 *   - Use prefix sums to efficiently compute the total operations for any range
 * [b+1, a].
 *
 * Time Complexity: O(N log log N + t), where N = 5,000,000 and t is number of
 * test cases Space Complexity: O(N), for arrays c and d of size N+4
 */

#include <cstdio>

const int N = 5000000;
int c[N + 4], d[N + 4];

int main() {
  // Sieve of Eratosthenes to find smallest prime factor for each number
  for (int i = 2; i <= N; ++i)
    if (!c[i])                        // If c[i] is 0, then i is a prime
      for (int j = i; j <= N; j += i) // Mark all multiples of i
        if (!c[j])                    // Only mark if not already marked
          c[j] = i;                   // Set smallest prime factor of j to i

  // Compute the number of prime factors (with repetition) for each number
  // c[i] stores number of steps to reduce i to 1 by dividing by smallest prime
  // factor
  for (int i = 2; i <= N; ++i)
    c[i] =
        1 + c[i / c[i]]; // Add 1 for current division, plus steps for quotient

  // Prefix sum to get cumulative count of operations up to each number
  for (int i = 1; i <= N; ++i)
    d[i] = c[i] + d[i - 1];

  int n, a, b;
  scanf("%d", &n);
  while (n-- > 0 && 2 == scanf("%d%d", &a, &b)) // Read test cases
    printf("%d\n", d[a] - d[b]); // Output difference for interval [b+1, a]
}

// https://github.com/VaHiX/CodeForces/