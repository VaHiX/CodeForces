// Problem: CF 1252 A - Copying Homework
// https://codeforces.com/contest/1252/problem/A

/*
 * Problem: A. Copying Homework
 * Algorithms/Techniques: Simple permutation reversal approach to maximize difference
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1) - excluding input/output storage
 *
 * The goal is to construct a permutation B such that diff(A, B) >= N.
 * To maximize the difference, we want to pair each element A[i] with a value
 * as far away from it as possible. A simple greedy approach is to reverse the array,
 * which ensures maximum disparity between corresponding elements.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    // For each input element x, output (n + 1 - x)
    // This maps elements to their "anti-symmetric" counterparts
    printf("%ld ", (n + 1 - x));
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/