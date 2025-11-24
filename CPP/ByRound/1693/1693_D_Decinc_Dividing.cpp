// Problem: CF 1693 D - Decinc Dividing
// https://codeforces.com/contest/1693/problem/D

/*
 * Problem: Decinc Dividing
 * 
 * Purpose: Given a permutation of numbers from 1 to n, count the number of subarrays 
 *          that are "Decinc" (can be made increasing by removing a decreasing subsequence).
 * 
 * Algorithm/Technique:
 * - Dynamic Programming with reverse processing:
 *   For each starting index l from n down to 1, compute for each position i
 *   the minimum and maximum values that can be part of an increasing subsequence ending at i
 *   after removing one decreasing subsequence.
 * 
 * Time Complexity: O(n^2) in worst case due to nested loops, but optimized with early break.
 * Space Complexity: O(n) for the DP array f.
 * 
 * Approach:
 * - Process subarrays from right to left.
 * - For each l, compute f[i][0] (min value) and f[i][1] (max value) that can be part
 *   of valid increasing subsequences ending at i.
 * - Adjust r to ensure all elements from l to r are valid.
 * - Add count of valid intervals [l, r] to result.
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 2e5 + 5;
int n, a[N], f[N][2];  // f[i][0]: min value; f[i][1]: max value for increasing subseq ending at i
long long ans;
signed main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int l = n, r = n; l >= 1; l--) {
    f[l][0] = 1e9, f[l][1] = -1e9;  // Initialize for current l
    for (int i = l + 1; i <= n; i++) {
      int c0 = -1e9, c1 = 1e9;      // new candidate min and max
      if (a[i - 1] < a[i])          // if a[i-1] contributes to increasing subseq
        c0 = f[i - 1][0];
      if (f[i - 1][1] < a[i])       // if f[i-1][1] < a[i], a[i] can be added
        c0 = max(c0, a[i - 1]);     // extend min if needed
      if (a[i - 1] > a[i])          // if a[i-1] is greater than a[i], a[i] might be removed
        c1 = f[i - 1][1];           // propagate current max
      if (f[i - 1][0] > a[i])       // if a[i] is smaller than previous min
        c1 = min(c1, a[i - 1]);     // update max that can be part of increasing seq
      if (c0 == f[i][0] && c1 == f[i][1])  // no change, break early
        break;
      f[i][0] = c0, f[i][1] = c1;
    }
    while (r >= l && f[r][0] == -1e9 && f[r][1] == 1e9)  // adjust r to valid segment
      r--;
    ans += r - l + 1;  // add number of valid subarrays starting from l
  }
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/