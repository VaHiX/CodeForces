// Problem: CF 1610 E - AmShZ and G.O.A.T.
// https://codeforces.com/contest/1610/problem/E

/*
Code Purpose:
This code solves the problem of finding the minimum number of elements to delete from an array to make it "good".
An array is "good" if none of its subsequences are "terrible".
A "terrible" array is one where the number of elements greater than the average is strictly greater than the number of elements less than the average (elements equal to the average do not count).

Algorithm:
- The approach uses a greedy method:
  1. For each group of equal elements, we determine how many elements
     we can include in a "good" subsequence.
  2. For a group of equal elements, we try to extend the subsequence
     by including elements such that the average remains valid.
  3. The maximum such valid subsequence length is tracked.
- To determine the maximum valid subsequence, for each starting element,
  we extend the sequence using the condition: for current element x and
  a previous element y, the next element must satisfy the average constraint.

Time Complexity: O(n log n) due to the sorting and binary search operations.
Space Complexity: O(1) excluding input storage, as we use only constant extra space.

*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 2e5 + 5;
int t, n, a[N], ans;

signed main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n), ans = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    for (int i = 1; i <= n;) {
      int res = 0;
      do {
        i++, res++;
      } while (i <= n && a[i] == a[i - 1]);
      // Process a group of equal elements, incrementing res for each element
      for (int j = i; j <= n;)
        res++, j = lower_bound(a + j, a + 1 + n, 2 * a[j] - a[i - 1]) - a;
      // Extend the subsequence by finding the next valid element using binary search
      ans = max(ans, res);
    }
    printf("%d\n", n - ans);
    // Output the number of deletions needed
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/