// Problem: CF 667 B - Coat of Anticubism
// https://codeforces.com/contest/667/problem/B

/*
 * Problem: B. Coat of Anticubism
 * 
 * Purpose: Given n rods of integer lengths, determine the minimum integer length
 *          of an additional rod such that all (n+1) rods can form a convex polygon
 *          with nonzero area.
 * 
 * Algorithm: 
 *   - For a set of n sides to form a convex polygon with nonzero area,
 *     the sum of all sides must be greater than twice the longest side.
 *   - Since the current configuration is not valid (impossible to make a polygon),
 *     we need to add a rod such that the new condition is satisfied.
 *   - Let 'max' be the maximum length among existing rods.
 *   - Let 'sum' be the total sum of all existing rod lengths.
 *   - The minimum required length of the new rod z is such that:
 *     sum + z > 2 * max
 *     => z > 2 * max - sum
 *     => z >= 2 * max - sum + 1
 * 
 * Time Complexity: O(n) - Single pass through the input
 * Space Complexity: O(1) - Only a few variables used
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld\n", &n);
  long max(0), sum(0);
  while (n--) {
    long len;
    scanf("%ld ", &len);
    sum += len;        // Accumulate total length
    max = (len > max) ? len : max;  // Track maximum length
  }
  printf("%ld\n", 2 * max - sum + 1);  // Compute minimum required rod length
  return 0;
}


// https://github.com/VaHiX/CodeForces/