// Problem: CF 733 B - Parade
// https://codeforces.com/contest/733/problem/B

#include <cstdio>
#include <vector>
/*
 * Problem: Parade
 * 
 * Purpose: To find the column whose soldiers should switch their starting leg 
 *          to maximize the beauty of the parade. Beauty is defined as the 
 *          absolute difference between total left and right leg marchers.
 * 
 * Algorithm:
 *   1. For each column, calculate the difference (l_i - r_i) and store it as 2*(l_i - r_i)
 *      to facilitate quick computation when switching columns.
 *   2. Compute initial total left and right marchers and their absolute difference.
 *   3. For each column, simulate switching its leg preference and compute the new 
 *      absolute difference. Track the maximum difference and the associated column.
 *   4. Output the best column index or 0 if no switch improves the current beauty.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> diff(n, 0);  // Stores 2*(l_i - r_i) for each column
  long left(0), right(0);        // Running totals of left and right leg soldiers
  for (int p = 0; p < n; p++) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    diff[p] = 2 * (a - b);       // Precompute the change in difference if we switch column p
    left += a;
    right += b;
  }
  long init(left - right);       // Initial difference between left and right marchers
  long col(0);                   // Column index to switch (0 means no switch)
  long maxDiff(init);            // Maximum beauty so far
  if (maxDiff < 0) {
    maxDiff = -maxDiff;          // Ensure maxDiff is positive
  }
  for (int p = 0; p < n; p++) {
    long cand = init - diff[p];  // Simulate switching column p
    if (cand < 0) {
      cand = -cand;              // Ensure candidate is positive
    }
    if (cand > maxDiff) {        // Update if the new beauty is better
      col = p + 1;               // Column index is 1-based
      maxDiff = cand;
    }
  }
  printf("%ld\n", col);
  return 0;
}


// https://github.com/VaHiX/CodeForces/