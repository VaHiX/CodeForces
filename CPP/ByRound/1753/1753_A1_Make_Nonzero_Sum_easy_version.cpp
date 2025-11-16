// Problem: CF 1753 A1 - Make Nonzero Sum (easy version)
// https://codeforces.com/contest/1753/problem/A1

/*
Algorithm: Greedy approach to partition array into segments such that alternating sum of all segments is zero.
Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(n) for storing the partition points.

The idea:
- For arrays of odd length, it's impossible to have a valid partition (because the alternating sum of an odd-length segment cannot be zero).
- For even-length arrays:
  - Process segments in pairs greedily.
  - If two adjacent elements are the same, extend the current segment to include both.
  - If adjacent elements are different, split them into different segments.
- The final output is a list of segments with alternating sums that sum to zero.

This solution uses prefix logic to assign segments greedily and then outputs them.
*/

#include <cstdio>
#include <iosfwd>

using namespace std;
int n, T, a[200001], p[200001], cnt;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int _ = 0;
    cnt = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      // Skip processing for odd-length arrays or even indices as part of logic
      if (n & 1 || i & 1)
        continue;
      // If current and previous element are the same, merge them into a segment
      if (a[i] == a[i - 1])
        p[++cnt] = i;
      else
        // If elements differ, start new segment at previous index and continue at current
        p[++cnt] = i - 1, p[++cnt] = i;
    }
    // If array has odd length, no valid partition possible
    if (n & 1)
      printf("-1\n");
    else
      printf("%d\n", cnt);
    // Output all segments
    for (int i = 1; i <= cnt; i++)
      printf("%d %d\n", p[i - 1] + 1, p[i]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/