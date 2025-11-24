// Problem: CF 2089 A - Simple Permutation
// https://codeforces.com/contest/2089/problem/A

/*
 * Problem: Construct a permutation of length n such that among the ceiling averages c1, c2, ..., cn,
 * there are at least floor(n/3) - 1 prime numbers.
 *
 * Algorithm:
 * - For each test case, we construct a permutation by starting from the middle and expanding outwards.
 * - We use a helper function `pm` to check for primes.
 * - A helper function `wt` writes integers digit-by-digit into a buffer.
 * - The process starts at p = n/2, then moves up and down, ensuring all numbers are used exactly once.
 *
 * Time Complexity: O(n * sqrt(n)) per test case due to prime checks in the worst case.
 * Space Complexity: O(n) for the buffer and temporary arrays.
 */

#include <stdio.h>
#pragma GCC optimize("O3,unroll-loops")
const int N = 6e5;
char t[6], bf[N];
int main() {
  int T, po = 0;
  scanf("%d", &T);
  auto pm = [&](int n) { // Prime check function
    if (n < 2)
      return 0;
    for (int d = 2; d * d <= n; d++)
      if (n % d == 0)
        return 0;
    return 1;
  };
  auto wt = [&](int x) { // Write integer to buffer
    int tp = 0;
    while (x) {
      t[tp++] = '0' + (x % 10);
      x /= 10;
    }
    while (tp--)
      bf[po++] = t[tp];
    bf[po++] = ' ';
  };
  while (T--) {
    int n;
    scanf("%d", &n);
    int p = n / 2; // Start from the middle of the range
    while (!pm(p)) // Find next prime number >= p
      p++;
    int c = 0, R = p, L = p - 1; // Left and right pointers to build sequence
    while (c < n) {
      if (R <= n && c++ < n) // Add right element if valid
        wt(R++);
      if (L > 0 && c++ < n) // Add left element if valid
        wt(L--);
    }
    bf[po - 1] = '\n'; // Replace last space with newline
    fwrite(bf, 1, po, stdout); // Output buffer
    po = 0; // Reset buffer pointer for next test case
  }
}


// https://github.com/VaHiX/codeForces/