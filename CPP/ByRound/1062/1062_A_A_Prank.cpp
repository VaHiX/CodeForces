// Problem: CF 1062 A - A Prank
// https://codeforces.com/contest/1062/problem/A

/*
 * Problem: A. A Prank
 * Algorithm: Sliding window approach to find the maximum number of consecutive
 *            elements that can be erased while maintaining a unique restoration.
 *
 * Time Complexity: O(n), where n is the size of the input array.
 * Space Complexity: O(n), due to the vector storage for the array.
 *
 * Description:
 * JATC wants to erase the maximum number of consecutive elements from an increasing
 * array such that the remaining elements allow unique reconstruction of the array,
 * given that all elements are integers in [1, 1000].
 *
 * The approach:
 * - Add sentinel values at both ends (0 and 1001) to simplify boundary handling.
 * - Traverse the modified array to track the longest consecutive sequence.
 * - For each element, if it's one more than the previous (i.e., part of a consecutive
 *   sequence), increment the current count. Otherwise reset the count.
 * - The maximum count minus 2 gives the number of elements that can be erased,
 *   since at least two elements must remain to define the gap.
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 2);  // Extra space for sentinels at both ends
  a[0] = 0;                    // Left sentinel
  a[n + 1] = 1001;             // Right sentinel
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &a[p]);       // Read the input array
  }
  long cnt(1), mx(0);          // cnt: current consecutive count, mx: max count so far
  for (long p = 1; p < a.size(); p++) {
    if (a[p - 1] + 1 == a[p]) { // Check if current element continues the sequence
      ++cnt;
    } else {
      cnt = 1;                   // Reset count if sequence breaks
    }
    mx = (mx > cnt) ? mx : cnt;   // Update max count
  }
  printf("%ld\n", mx > 1 ? (mx - 2) : 0);  // Output result, or 0 if no erasable elements
  return 0;
}


// https://github.com/VaHiX/codeForces/