// Problem: CF 1364 A - XXXXX
// https://codeforces.com/contest/1364/problem/A

/*
Problem: Find the length of the longest subarray whose sum is not divisible by x.

Algorithm:
- For each element in the array, compute its modulo with x.
- Compute the prefix sum mod x.
- If total sum is divisible by x:
  - Try to remove leftmost or rightmost zeros (since they don't affect the sum mod x).
  - The longest subarray will be the original length minus the number of leading/trailing zeros.
- If total sum is not divisible by x, return the full length.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array

Techniques:
- Prefix sum with modular arithmetic
- Greedy approach to handle cases where total sum is divisible by x
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    std::vector<long> a(n);
    long s(0); // Running sum mod x
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      a[p] %= x; // Store remainder
      s += a[p];
      s %= x;
    }
    long ans(n);
    if (s % x == 0) { // If total sum is divisible by x
      long left(0);
      while (left < n && a[left] == 0) {
        ++left;
      }
      long right(0);
      while (right < n && a[n - 1 - right] == 0) {
        ++right;
      }
      long mn = (left < right) ? left : right;
      ans -= mn + 1; // Subtract minimum number of zeros to exclude
    }
    printf("%ld\n", ans);
    continue;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/