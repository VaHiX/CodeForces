// Problem: CF 2101 D - Mani and Segments
// https://codeforces.com/contest/2101/problem/D

/*
 * Problem: D. Mani and Segments
 * Algorithm: Two-pass sliding window technique with prefix/suffix arrays to count cute subarrays.
 *
 * Key Insight:
 * An array is "cute" if LIS(b) + LDS(b) = |b| + 1.
 * For a permutation, this condition holds exactly when the subarray is a concatenation of at most one increasing segment and one decreasing segment (or vice versa).
 * The algorithm uses two passes over the array:
 *   1. Forward pass: compute for each position how far we can extend an increasing/decreasing sequence.
 *   2. Backward pass: use similar logic with suffix arrays to avoid double counting.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) due to arrays f and g of size n
 */

#include <stdio.h>
#include <algorithm>

#define ll long long
using namespace std;

int t, n, a[200005], f[200005], g[200005];
ll ans;

int main() {
  scanf("%d", &t);
  while (t--) {
    ans = 1; // Every single element array is cute
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);

    // Forward pass: compute max end position for increasing/decreasing segments starting at each index
    int minp = 1, maxp = 1;
    for (int i = 1, j = 1; i <= n;) {
      while (j < n) {
        if (a[j + 1] > a[maxp])
          maxp = ++j; // Update max position if current element is larger
        else if (a[j + 1] < a[minp])
          minp = ++j; // Update min position if current element is smaller
        else
          break; // Stop if element is in between, can't extend increasing/decreasing segment
      }
      while (i <= min(maxp, minp)) // Assign farthest extendable index to f[i]
        f[i++] = j;
      if (maxp < minp)   // Adjust pointers for next iteration
        maxp = i;
      else
        minp = i;
    }

    // Backward pass: symmetric but from right to left
    minp = maxp = n;
    for (int i = n, j = n; i >= 1;) {
      while (j > 1) {
        if (a[j - 1] > a[maxp])
          maxp = --j; // Update max position moving backwards
        else if (a[j - 1] < a[minp])
          minp = --j; // Update min position moving backwards
        else
          break;
        ans += (f[i] - j + 1); // Add valid subarrays ending at i and starting at or after j
      }
      while (i >= max(maxp, minp)) // Assign farthest extendable index to g[i]
        g[i--] = j;
      if (maxp > minp)   // Adjust pointers for next iteration
        maxp = i;
      else
        minp = i;
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/