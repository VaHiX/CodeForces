// Problem: CF 1821 B - Sort the Subarray
// https://codeforces.com/contest/1821/problem/B

/*
B. Sort the Subarray
time limit per test2 seconds
memory limit per test512 megabytes

Algorithm:
The problem is to find a subarray that, when sorted, transforms array `a` into array `a'`.
- We compare the two arrays and identify the leftmost and rightmost positions where they differ.
- These positions define the boundaries of the subarray that needs sorting.
- After identifying potential boundaries, we expand them to the left and right as long as the order is maintained (to ensure we are sorting a valid subarray).

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the input arrays

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long left(-1), right(-1);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x == a[p]) {
        continue;
      }
      // If this is the first difference, set `left` to current position
      left = (left < 0 ? p : left);
      // Keep updating `right` to current position since we're looking for last diff
      right = p;
      a[p] = x;  // Update element in original array to match target
    }
    // Expand `left` to the left while order is maintained
    while (left > 0 && a[left - 1] <= a[left]) {
      --left;
    }
    // Expand `right` to the right while order is maintained
    while (right + 1 < n && a[right] <= a[right + 1]) {
      ++right;
    }
    printf("%ld %ld\n", left + 1, right + 1);  // Output 1-indexed positions
  }
}


// https://github.com/VaHiX/codeForces/