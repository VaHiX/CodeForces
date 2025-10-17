// Problem: CF 1920 B - Summation Game
// https://codeforces.com/contest/1920/problem/B

/*
B. Summation Game

Algorithm:
- Sort the array in descending order.
- Compute prefix sums to efficiently calculate sum of first i elements.
- Try all valid combinations of:
  - Number of elements Alice removes (up to k),
  - Number of elements Bob multiplies by -1 (exactly x).
- For each try, compute resulting sum and keep maximum.

Time Complexity: O(n log n + nk) per test case due to sorting and checking up to k options.
Space Complexity: O(n) for storing the array and prefix sums.

*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k, x;
    scanf("%ld %ld %ld", &n, &k, &x);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.rbegin(), a.rend()); // Sort in descending order
    for (long p = 1; p < n; p++) {
      a[p] += a[p - 1]; // Compute prefix sums
    }
    long res(a.back() - 2 * a[x - 1]); // Initial result: remove x smallest and flip signs of largest x
    for (long p = 0; p < k; p++) {
      long idxB = p + x;
      idxB = (idxB < n - 1 ? idxB : n - 1); // Adjust index to avoid overflow
      long cur = a.back() - 2 * a[idxB] + a[p]; // Calculate current configuration
      res = (res > cur ? res : cur); // Keep maximum
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/