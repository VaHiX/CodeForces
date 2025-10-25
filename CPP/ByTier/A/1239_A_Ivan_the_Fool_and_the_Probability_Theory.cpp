// Problem: CF 1239 A - Ivan the Fool and the Probability Theory
// https://codeforces.com/contest/1239/problem/A

#include <stdio.h>
// Problem: Count the number of random pictures of n rows and m columns.
// A picture is random if each cell has at most one adjacent cell of the same color.
// This problem uses dynamic programming on rows, with Fibonacci-like transitions.
// Time Complexity: O(n + m)
// Space Complexity: O(max(n, m))
long long int f[100001] = {0, 1, 2}, i, m, n;
int main() {
  // Precompute Fibonacci-like sequence for row transitions
  for (i = 3; i <= 100000; i++) {
    f[i] = (f[i - 1] + f[i - 2]) % 1000000007;
  }
  scanf("%lld%lld", &m, &n);
  // The formula for the result is: 2 * (f[m] + f[n] - 1) mod 10^9 + 7
  printf("%lld", 2 * (f[m] + f[n] - 1) % 1000000007);
}

// https://github.com/VaHiX/codeForces/