// Problem: CF 2030 B - Minimise Oneness
// https://codeforces.com/contest/2030/problem/B

/*
 * Problem: Minimise Oneness
 * 
 * Purpose: Given a positive integer n, find a binary string of length n such that 
 * the oneness (absolute difference between f(t) and g(t)) is minimized.
 * 
 * Algorithm/Techniques:
 * - For any string, f(t) counts subsequences with only 0s and g(t) counts those with at least one 1.
 * - To minimize |f(t) - g(t)|, we want f(t) and g(t) to be as close as possible.
 * - A pattern that works well is starting with '1' followed by all '0's.
 *   This ensures g(t) = 1 (only the '1' itself), and f(t) = 2^(n-1) - 1 (all non-empty subsequences of 0s).
 *   The difference is minimized with this approach.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) excluding output
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("1"); // Start with '1' to minimize difference
    for (long p = 1; p < n; p++) {
      printf("0"); // Append all zeros
    }
    puts(""); // Print newline
  }
}


// https://github.com/VaHiX/CodeForces/