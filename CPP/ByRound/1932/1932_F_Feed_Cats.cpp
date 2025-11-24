// Problem: CF 1932 F - Feed Cats
// https://codeforces.com/contest/1932/problem/F

/*
 * Problem: Feed Cats
 * Algorithm: Dynamic Programming with Sliding Window
 * 
 * Purpose:
 *   Given n steps and m cats, each cat is present from l[i] to r[i].
 *   At each step, we can choose to feed all present cats or do nothing.
 *   Goal: maximize the number of cats fed without feeding any cat more than once.
 * 
 * Approach:
 *   - Use a difference array technique to track how many cats are present at each step.
 *   - Use dynamic programming where f[i] represents the maximum number of cats that can be fed
 *     up to step i.
 *   - Maintain a sliding window to ensure no cat is fed twice.
 * 
 * Time Complexity: O(n + m)
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 1000010;
int T, n, m, f[N], r[N], cnt[N];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    // Initialize arrays
    for (int i = 1; i <= n; i++)
      r[i] = cnt[i] = 0;
    
    // Process each cat's presence interval
    for (int i = 1, x, y; i <= m; i++) {
      scanf("%d%d", &x, &y);
      r[x] = max(r[x], y); // Track the latest end time for each start point
      cnt[x]++;            // Increment count at start
      cnt[y + 1]--;        // Decrement count after end
    }
    
    // Build prefix sum of cat counts
    for (int i = 1, j = 1; i <= n; i++) {
      cnt[i] += cnt[i - 1]; // Calculate how many cats are present at step i
      
      // Maintain sliding window to ensure no overlap
      while (j < i && r[j] < i)
        j++;
      
      // DP transition: either don't feed at step i or feed and add to previous best
      f[i] = max(f[i - 1], f[j - 1] + cnt[i]);
    }
    
    printf("%d\n", f[n]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/