// Problem: CF 709 B - Checkpoints
// https://codeforces.com/contest/709/problem/B

/*
 * Problem: Checkpoints
 * Purpose: Find the minimum distance to visit at least n-1 checkpoints starting from position 'a'.
 * Algorithm: 
 *   - Sort checkpoints to allow greedy approach.
 *   - Consider two strategies:
 *     1. Start from 'a', go to the first checkpoint, then to the last checkpoint.
 *     2. Start from 'a', go to the last checkpoint, then to the first checkpoint.
 *   - But also consider skipping one checkpoint from either end to minimize total distance.
 *   - Evaluate all viable combinations after sorting.
 * 
 * Time Complexity: O(n log n) due to sorting; O(1) for the rest of operations.
 * Space Complexity: O(n) for storing the checkpoint positions.
 */

#include <algorithm>
#include <cstdio>
#include <vector>

long abs(long x) { return (x > 0) ? x : (-x); }
int main() {
  long n, a;
  scanf("%ld %ld\n", &n, &a);
  std::vector<long> v(n);
  for (int p = 0; p < n; p++) {
    scanf("%ld", &v[p]);
  }
  sort(v.begin(), v.end()); // Sort checkpoints to enable greedy strategy
  if (n == 1) {
    puts("0"); // Only one checkpoint, no travel needed
  } else {
    // Compute minimum of two possible paths:
    // 1. Start at a, go to first checkpoint, then proceed to second-to-last, then to last
    // 2. Start at a, go to last checkpoint, then proceed to second, then to first
    printf(
        "%ld\n",
        std::min(std::min(abs(v[0] - a), abs(v[n - 2] - a)) + v[n - 2] - v[0],
                 std::min(abs(v[1] - a), abs(v[n - 1] - a)) + v[n - 1] - v[1]));
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/