// Problem: CF 2156 A - Pizza Time
// https://codeforces.com/contest/2156/problem/A

/*
 * Problem: Pizza Time
 * 
 * Purpose: Determine the maximum number of pizza slices Hao can eat when
 *          he optimally splits the slices each day according to given rules.
 * 
 * Algorithm/Techniques:
 *   - Mathematical pattern recognition from recursive behavior.
 *   - Observing that for any n >= 3, the optimal strategy leads to a predictable result:
 *     - If n is odd, Hao eats n/2 slices.
 *     - If n is even, Hao eats (n/2 - 1) slices.
 * 
 * Time Complexity: O(t), where t is the number of test cases. Each test case is processed in O(1).
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <stdio.h>

int main() {
  int t, i;
  scanf("%d", &t);
  for (i = 0; i < t; i++) {
    long long int a;
    scanf("%lld", &a);
    if (a % 2)
      printf("%lld\n", a / 2);  // For odd n, Hao eats n/2 slices
    else
      printf("%lld\n", a / 2 - 1);  // For even n, Hao eats n/2 - 1 slices
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/