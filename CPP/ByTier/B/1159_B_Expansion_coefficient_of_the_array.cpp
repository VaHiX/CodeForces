// Problem: CF 1159 B - Expansion coefficient of the array
// https://codeforces.com/contest/1159/problem/B

/*
B. Expansion coefficient of the array
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
Let's call an array of non-negative integers a k-extension for some non-negative integer k if for all possible pairs of indices 1 <= i, j <= n the inequality k * |i - j| <= min(a_i, a_j) is satisfied. The expansion coefficient of the array a is the maximal integer k such that the array a is a k-extension. Any array is a 0-expansion, so the expansion coefficient always exists.
You are given an array of non-negative integers a_1, a_2, ..., a_n. Find its expansion coefficient.

Algorithm: 
We use a brute-force approach with optimization:
For each element at position p, we compute two values:
- f = a[p] / (p - 1) if p > 1 (from the left side)
- g = a[p] / (n - p) if p < n (from the right side)

The minimal of these computed bounds gives us the maximum possible k such that the array is a k-extension.

Time Complexity: O(n)
Space Complexity: O(n)

*/
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 1, 0); // Initialize vector with n+1 elements, all zero
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &a[p]); // Read array elements starting from index 1
  }
  long ans(1e9 + 7); // Initialize answer with a large value (infinity)
  for (long p = 1; p <= n; p++) {
    if (p > 1) { // Check left neighbor constraint
      long f = a[p] / (p - 1); // Compute lower bound from left side
      ans = (ans < f) ? ans : f; // Update minimal bound
    }
    if (p < n) { // Check right neighbor constraint
      long g = a[p] / (n - p); // Compute lower bound from right side
      ans = (ans < g) ? ans : g; // Update minimal bound
    }
  }
  printf("%ld\n", ans); // Print result
  return 0;
}


// https://github.com/VaHiX/codeForces/