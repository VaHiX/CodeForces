// Problem: CF 1850 D - Balanced Round
// https://codeforces.com/contest/1850/problem/D

/*
 * Problem: D. Balanced Round
 * Purpose: Given n problems with difficulties a[i], find the minimum number of problems to remove
 *          so that the remaining problems can be arranged in a balanced order where the absolute
 *          difference between any two consecutive problems is at most k.
 *
 * Algorithm:
 * - Sort the array of difficulties.
 * - Use a sliding window technique to find the longest subsequence where all adjacent elements
 *   differ by at most k.
 * - The result is total number of problems minus the length of this longest valid subsequence.
 *
 * Time Complexity: O(n * log(n)) due to sorting; each test case processed in O(n) after sorting.
 * Space Complexity: O(n) for storing the vector of difficulties.
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end()); // Sort the array to enable sliding window approach
    long cur(1), mx(1);       // cur tracks current length of valid sequence, mx tracks maximum
    for (long p = 1; p < n; p++) {
      if (a[p] <= a[p - 1] + k) {  // If current element is within allowed difference
        ++cur;                     // Extend the current sequence
        mx = (mx > cur ? mx : cur); // Update maximum length found so far
      } else {
        cur = 1;  // Start new sequence from current element
      }
    }
    printf("%ld\n", n - mx); // Minimum problems to remove = total - longest valid subsequence
  }
}


// https://github.com/VaHiX/codeForces/