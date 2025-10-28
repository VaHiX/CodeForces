// Problem: CF 2084 A - Max and Mod
// https://codeforces.com/contest/2084/problem/A

#include <cstdio>

/*
 * Problem: A. Max and Mod
 *
 * Purpose: Find a permutation of length n such that for all i from 2 to n,
 *          max(p[i-1], p[i]) % i = i - 1. If impossible, output -1.
 *
 * Algorithm:
 * - For even n, it's impossible because the condition requires odd-length permutations
 *   to satisfy modular arithmetic constraints.
 * - For odd n > 2:
 *   - Construct a specific pattern: [n, n-1, ..., 1] for n elements, but modify it slightly.
 *   - Start with n, then place numbers in decreasing order from n-1 down to 1.
 *   - Special handling for i = 2 where max(p[1], p[2]) % 2 == 1.
 *
 * Time Complexity: O(n) per test case — we just iterate through n elements once.
 * Space Complexity: O(n) — storing the output permutation.
 */

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n % 2 == 0) {  // If n is even, no valid permutation exists
      puts("-1");
      continue;
    }
    printf("%ld ", n);  // Start with n as first element for pattern consistency
    for (long p = 1; p < n; p++) {  // Print from 1 to n-1 in order
      printf("%ld ", p);
    }
    puts("");  // New line after each permutation
  }
}

// https://github.com/VaHiX/codeForces/