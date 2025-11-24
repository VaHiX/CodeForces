// Problem: CF 1152 A - Neko Finds Grapes
// https://codeforces.com/contest/1152/problem/A

/*
 * Problem: A. Neko Finds Grapes
 * Purpose: Given n chests with values a_i and m keys with values b_j,
 *          determine the maximum number of chests that can be opened
 *          using the constraint that a_i + b_j must be odd (i.e., one is even, one is odd).
 *
 * Algorithm:
 *   1. Count how many even and odd numbers exist among chests and keys.
 *   2. To form an odd sum: one number must be even, the other odd.
 *   3. Match even-counted chests with odd-counted keys and vice versa.
 *   4. Take minimums to avoid overcounting.
 *
 * Time Complexity: O(n + m)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  long cv(0), cd(0), kv(0), kd(0); // cv: chests even, cd: chests odd, kv: keys even, kd: keys odd
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    (a % 2) ? (++cd) : (++cv); // Increment chest counter based on parity
  }
  for (long p = 0; p < m; p++) {
    long b;
    scanf("%ld", &b);
    (b % 2) ? (++kd) : (++kv); // Increment key counter based on parity
  }
  long cntA = (cv < kd) ? cv : kd; // Match even chests with odd keys
  long cntB = (cd < kv) ? cd : kv; // Match odd chests with even keys
  printf("%ld\n", cntA + cntB);    // Total matched pairs
  return 0;
}


// https://github.com/VaHiX/codeForces/