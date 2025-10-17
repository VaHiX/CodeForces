// Problem: CF 2014 D - Robert Hood and Mrs Hood
// https://codeforces.com/contest/2014/problem/D

/*
D. Robert Hood and Mrs Hood

Algorithm: Difference Array + Sliding Window
Time Complexity: O(n) per test case (amortized)
Space Complexity: O(n) per test case

This problem involves finding optimal start days for two visits of duration d,
such that one visit overlaps with maximum jobs and the other with minimum jobs.
We use a difference array technique to efficiently calculate how many jobs each
possible visit day overlaps with, then find the max and min values in sliding windows.

Key Steps:
1. For each job [l, r], we increment the start of overlap range and decrement after it.
2. Use prefix sum to compute total overlaps for each possible visit day.
3. Find the day with maximum and minimum overlaps.

*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, d, k;
    scanf("%d%d%d", &n, &d, &k);
    vector<int> a(n + 2);  // Difference array, size n+2 to avoid boundary checks
    for (int i = 1, l, r; i <= k; i++) {
      scanf("%d%d", &l, &r);
      ++a[max(1, l - d + 1)];  // Start of overlap range: adjust for visit duration
      --a[r + 1];              // End of overlap range
    }
    int mi = 1, mx = 1;        // Initialize indices for min and max
    for (int i = 1; i <= n - d + 1; i++) {
      a[i] += a[i - 1];        // Compute prefix sum to get actual overlaps per day
      if (a[i] < a[mi])        // Update minimum overlap index
        mi = i;
      if (a[i] > a[mx])        // Update maximum overlap index
        mx = i;
    }
    printf("%d %d\n", mx, mi);  // Output the best days for brother and mother
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/