// Problem: CF 870 B - Maximum of Maximums of Minimums
// https://codeforces.com/contest/870/problem/B

/*
 * Problem: Maximum of Maximums of Minimums
 * 
 * Algorithm/Technique: 
 * - The problem asks to split an array into exactly k non-empty subsegments,
 *   compute the minimum of each subsegment, and then find the maximum of those
 *   minimums. The key insight is that for k = 1, we must take the entire array
 *   and return the minimum of the whole array.
 * - For k = 2, the optimal strategy is to split the array into two parts, and
 *   the maximum of the minimums is the larger of the first and last elements.
 * - For k > 2, we can optimize by placing one subsegment as a single element,
 *   and the rest as a single large segment, allowing us the flexibility to
 *   choose the maximum element as the result.
 * 
 * Time Complexity: O(n) - We scan the array once to find min, max, first, and last.
 * Space Complexity: O(1) - We use only a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  long min(2e9), max(-2e9), first(0), last(0);
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    if (p == 0) {
      first = x;  // Store the first element
    } else if (p == n - 1) {
      last = x;   // Store the last element
    }
    min = (min < x) ? min : x;  // Update the global minimum
    max = (max > x) ? max : x;  // Update the global maximum
  }
  if (k == 1) {
    printf("%ld\n", min);       // If only one segment, min of entire array is the answer
  } else if (k == 2) {
    printf("%ld\n", (first > last) ? first : last);  // If two segments, take max of first and last
  } else {
    printf("%ld\n", max);       // For k > 2, the best is the maximum element in array
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/