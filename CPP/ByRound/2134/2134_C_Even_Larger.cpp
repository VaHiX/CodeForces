// Problem: CF 2134 C - Even Larger
// https://codeforces.com/contest/2134/problem/C

/*
C. Even Larger
Algorithm: Greedy approach with prefix adjustment
Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input array

Description:
This code finds the minimum number of operations to make an array "good".
An array is good if, for every subarray of length >= 2,
the sum of elements at even indices (1-indexed) >= sum of elements at odd indices.
We process the array from left to right, adjusting elements to satisfy the condition greedily
by reducing values in a way that avoids violating earlier conditions.

Approach:
- For each pair of indices (i, i+1), where i is even (1-indexed):
  - Calculate how much we can safely reduce a[i+1] such that 
    a[i-1] + a[i+1] - a[i] >= 0 (ensuring subarray condition is met)
  - Add this amount to the total operation count
  - Adjust the value of a[i+1], and propagate any deficit back to a[i-1]

This ensures minimal operations while maintaining valid state.
*/

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 200005;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long t, n, a[N], i, x, ans;
  cin >> t;
  while (t--) {
    cin >> n;
    for (i = 1; i <= n; i++)
      cin >> a[i];
    a[n + 1] = 0; // Sentinel to avoid out-of-bounds access
    ans = 0;
    for (i = 2; i <= n; i += 2) { // Process pairs starting at even indices (1-indexed)
      x = max(a[i - 1] + a[i + 1] - a[i], 0LL); // Compute how much can be reduced from a[i+1]
      ans += x;
      a[i + 1] -= x; // Reduce a[i+1] by x
      if (a[i + 1] < 0) { // If reduction causes negative value
        a[i - 1] += a[i + 1]; // Propagate deficit to left neighbor
        a[i + 1] = 0; // Reset to zero
      }
    }
    cout << ans << '\n';
  }
}


// https://github.com/VaHiX/codeForces/