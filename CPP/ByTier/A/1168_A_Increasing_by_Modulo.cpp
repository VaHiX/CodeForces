// Problem: CF 1168 A - Increasing by Modulo
// https://codeforces.com/contest/1168/problem/A

/*
 * Problem: Making Array Non-Decreasing with Modular Operations
 * 
 * Algorithm/Techniques:
 * - Binary search on the answer (minimum number of operations)
 * - Greedy validation using a sliding window approach
 * 
 * Time Complexity: O(n * log m)
 * Space Complexity: O(n)
 * 
 * Approach:
 * - Use binary search to find minimum operations needed.
 * - For a given number of operations x, check if it's possible to make array non-decreasing.
 * - During validation, simulate how elements can increase modulo m while maintaining order.
 * - If an element is less than previous, we must increment it (if allowed by x).
 * - If an element is greater than previous, we may increment it to maintain non-decrease.
 */

#include <stdio.h>

int k, n, m;
const int N = 300005;
int a[N];
bool check(int x) {
  int res = 0;
  int pre = 0; // Track the current value (after increments) for comparison
  for (int i = 1; i <= n; ++i) {
    if (a[i] < pre) {
      // If current element is smaller than previous, we must increment it
      if (pre - a[i] > x) {
        return false; // Not enough operations to make it non-decreasing
      }
    } else if (a[i] > pre) {
      // If current element is larger than previous
      if (m - a[i] + pre > x) {
        // We can increment this element to keep the array non-decreasing
        pre = a[i];
      }
    }
  }
  return true;
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  int l = 0, r = m - 1, ans;
  while (l <= r) {
    int mid = (l + r) >> 1; // Mid is the number of operations to try
    if (check(mid)) {
      r = mid - 1;
      ans = mid;
    } else {
      l = mid + 1;
    }
  }
  printf("%d", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/