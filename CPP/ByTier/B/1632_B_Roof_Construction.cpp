// Problem: CF 1632 B - Roof Construction
// https://codeforces.com/contest/1632/problem/B

/*
Code Purpose:
This code solves the problem of constructing a sequence of pillar heights that minimizes the maximum XOR value
between adjacent pillars. The approach is based on observing that the optimal permutation can be constructed
by splitting the range [0, n-1] into two parts such that the maximum XOR between adjacent elements is minimized.

Algorithm:
1. For a given n, find the highest bit k such that 2^k <= n-1 < 2^(k+1).
2. Output all numbers from (2^k - 1) down to 0.
3. Then output all numbers from 2^k to n-1.
This ordering ensures that the maximum XOR between adjacent elements is minimized.

Time Complexity: O(n) per test case, since we iterate through the range once.
Space Complexity: O(1) additional space, not counting the input/output.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long k(0);
    // Find the highest bit k such that 2^k <= n - 1
    while ((1 << (k + 1)) <= n - 1) {
      ++k;
    }
    // Output numbers from (2^k - 1) down to 0
    for (long p = (1 << k) - 1; p >= 0; p--) {
      printf("%ld ", p);
    }
    // Output numbers from 2^k to n - 1
    for (long p = (1 << k); p < n; p++) {
      printf("%ld ", p);
    }
    puts(""); // Print newline at the end
  }
}


// https://github.com/VaHiX/CodeForces/