// Problem: CF 1163 A - Eating Soup
// https://codeforces.com/contest/1163/problem/A

/*
 * Problem: Eating Soup
 * Algorithms/Techniques: Mathematical approach to maximize number of groups
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * When m cats leave a circle of n cats, the maximum number of groups is determined by:
 * - If m is small enough to allow all remaining cats to form separate groups (m < n-m),
 *   then we have m+1 groups (each leaving cat splits the circle into one more group).
 * - Otherwise, if removing m cats leaves at least one contiguous segment,
 *   we simply have n-m segments.
 *
 * The formula uses: (m < n - m) ? (m > 0 ? m : 1) : (n - m)
 * - First branch: m < n - m implies that splitting into more groups is beneficial
 * - Second branch: otherwise, we get only n - m groups
 */

#include <cstdio>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  printf("%ld\n", (m < n - m) ? (m > 0 ? m : 1) : (n - m)); // Compute and print maximum number of groups
  return 0;
}


// https://github.com/VaHiX/codeForces/