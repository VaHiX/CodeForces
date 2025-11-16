// Problem: CF 1191 C - Tokitsukaze and Discard Items
// https://codeforces.com/contest/1191/problem/C

/*
C. Tokitsukaze and Discard Items
Algorithms/Techniques: Simulation with page-based operations, greedy approach

Time Complexity: O(m * log(n)) - The algorithm processes each special item once,
and uses binary search-like logic to determine page boundaries.

Space Complexity: O(1) - Only a few variables are used, independent of input size.

Recently, Tokitsukaze found an interesting game. Tokitsukaze had n items at the beginning of this game. However, she thought there were too many items, so now she wants to discard m special items of them.
These n items are marked with indices from 1 to n. Items are divided into several pages orderly, such that each page contains exactly k positions and the last positions on the last page may be left empty.
Tokitsukaze would do the following operation: focus on the first special page that contains at least one special item, and at one time, Tokitsukaze would discard all special items on this page. After an item is discarded or moved, its old position would be empty, and then the item below it, if exists, would move up to this empty position. The movement may bring many items forward and even into previous pages, so Tokitsukaze would keep waiting until all the items stop moving, and then do the operation (i.e. check the special page and discard the special items) repeatedly until there is no item need to be discarded.
*/
#include <stdio.h>
int main() {
  long long n, k, r, p, discard = 0;  // n: total items, k: items per page, r: page boundary, p: current special item index, discard: number of discarded items
  int m, ans = 0, i = 0;  // m: number of special items, ans: number of operations, i: loop counter
  scanf("%lld%d%lld%lld", &n, &m, &k, &p);  // Read input values
  while (i < m) {
    // Calculate the right boundary of the current page containing 'p'
    r = ((p - discard - 1) / k + 1) * k + discard;
    // While there are special items in the current page, discard them
    while (i < m && p <= r) {
      ++discard;  // Increment discard count
      ++i;        // Move to next special item
      scanf("%lld", &p);  // Read next special item index
    }
    ++ans;  // Increment operation count after completing a page
  }
  printf("%d", ans);  // Print total number of operations
}


// https://github.com/VaHiX/codeForces/