// Problem: CF 496 A - Minimum Difficulty
// https://codeforces.com/contest/496/problem/A

/*
 * Problem: Minimum Difficulty in Rock Climbing
 * 
 * Approach:
 * - We are given a sequence of hold heights in increasing order.
 * - We must remove exactly one hold (not the first or last) to minimize the maximum difference between adjacent holds.
 * - For each possible hold to remove (from index 1 to n-2), compute:
 *   - The new maximum difference after removal.
 *   - The potential reduction in the maximum difference by removing that hold.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n) due to vector storing the heights.
 * 
 * Algorithm:
 *   We iterate through all removable positions (1 to n-2). 
 *   For each such position p:
 *     - Compute the difference between the hold just after (p+1) and just before (p-1) the removed one.
 *     - Update the minimum such difference.
 *     - Compute the maximum difference among the remaining adjacent pairs.
 *   Finally, we return the maximum of these two computed values.
 * 
 * Sample Input:
 *   5
 *   1 2 3 7 8
 *   Output: 4
 * 
 * Sample Input:
 *   3
 *   1 4 6
 *   Output: 5
 * 
 * Sample Input:
 *   5
 *   1 2 3 4 5
 *   Output: 2
 */

#include <cstdio>
#include <vector>
int main() {
  int n;
  scanf("%d\n", &n);
  std::vector<int> heights(n, 0);
  for (int p = 0; p < n; p++) {
    scanf("%d", &heights[p]);
  }
  int minNew = 1001;  // Initialize with a value larger than maximum possible difference
  int maxCur = heights[1] - heights[0];  // Initial maximum difference between first two holds
  for (int p = 1; p < n - 1; p++) {
    // If we remove hold at p, the gap between (p-1) and (p+1) becomes the new adjacent difference
    if (heights[p + 1] - heights[p - 1] < minNew) {
      minNew = heights[p + 1] - heights[p - 1];
    }
    // Keep track of the maximum difference among the remaining adjacent pairs
    if (heights[p + 1] - heights[p] > maxCur) {
      maxCur = heights[p + 1] - heights[p];
    }
  }
  int maxDif = maxCur;
  // Determine the final difficulty as maximum of:
  // 1. The largest existing gap (maxCur)
  // 2. The smallest new gap created by removing a hold (minNew)
  if (minNew > maxDif) {
    maxDif = minNew;
  }
  printf("%d\n", maxDif);
  return 0;
}


// https://github.com/VaHiX/CodeForces/