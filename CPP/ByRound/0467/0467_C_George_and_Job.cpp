// Problem: CF 467 C - George and Job
// https://codeforces.com/contest/467/problem/C

/*
 * Problem: George and Job
 * Algorithm: Dynamic Programming with Sliding Window Optimization
 * 
 * Purpose:
 *   Given a sequence of n integers and parameters m and k, the goal is to select k 
 *   non-overlapping subarrays of length exactly m such that the sum of all elements 
 *   in these subarrays is maximized.
 * 
 * Approach:
 *   - Use dynamic programming with two states: dp[j][i & 1] and dp[j][i & 1 ^ 1].
 *   - dp[j][i] represents the maximum sum achievable by selecting exactly i subarrays
 *     ending at or before position j.
 *   - We iterate through the array and for each position j, we consider:
 *     1. Not including a new subarray ending at j (take dp[j - 1][i & 1])
 *     2. Including a new subarray ending at j (add value of subarray [j - m + 1, j])
 * 
 * Time Complexity: O(n * k)
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <algorithm>

long long a[5003], dp[5003][2];
int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1, x; i <= n; ++i)
    scanf("%d", &x), a[i] = a[i - 1] + x; // Compute prefix sums
  for (int i = 1; i <= k; ++i)
    for (int j = i * m; j <= n; ++j)
      // For each position j, decide whether to include a new subarray ending here
      dp[j][i & 1] =
          std::max(dp[j - 1][i & 1], dp[j - m][i & 1 ^ 1] + a[j] - a[j - m]);
  printf("%lld\n", dp[n][k & 1]); // Output result for k subarrays ending at n
}


// https://github.com/VaHiX/CodeForces/