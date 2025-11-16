// Problem: CF 732 B - Cormen --- The Best Friend Of a Man
// https://codeforces.com/contest/732/problem/B

/*
 * Problem: Cormen — The Best Friend Of a Man
 * 
 * Algorithm/Technique: Greedy Approach
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * The solution ensures that for every pair of consecutive days, the total number of walks is at least k.
 * We process the days sequentially and adjust the number of walks for each day to meet the constraint,
 * minimizing the total additional walks needed.
 * 
 * Input: 
 *   - n: number of days
 *   - k: minimum walks required for any two consecutive days
 *   - a: array of planned walks for each day
 * 
 * Output:
 *   - Minimum additional walks
 *   - Sequence of total walks (including adjustments)
 */

#include <cstdio>
#include <vector>
int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  std::vector<int> a(n + 1); // Use 1-based indexing for easier processing
  a[0] = k; // Previous day's walks (assumed to be k)
  for (int p = 1; p < n + 1; p++) {
    scanf("%d", &a[p]);
  }
  long total(0); // Total additional walks needed
  for (int p = 1; p < n + 1; p++) {
    int s = a[p - 1] + a[p]; // Sum of walks from previous and current day
    if (s < k) { // If the sum is less than required
      a[p] += (k - s); // Increase current day's walks to meet the constraint
      total += (k - s); // Add to total additional walks
    }
  }
  printf("%ld\n", total);
  for (int p = 1; p < n + 1; p++) {
    printf("%d ", a[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/