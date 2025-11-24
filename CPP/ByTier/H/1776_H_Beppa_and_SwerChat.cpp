// Problem: CF 1776 H - Beppa and SwerChat
// https://codeforces.com/contest/1776/problem/H

/*
 * Problem: Minimum Number of Members Online Between 9:00 and 22:00
 *
 * Description:
 * Beppa opened a group chat twice - once at 9:00 and once at 22:00. She recorded
 * the order of members in both cases. Each member has a unique ID between 1 and n.
 * The order represents members sorted by decreasing last seen times. We need to find
 * the minimum number of members who must have been online at least once during
 * the interval between 9:00 and 22:00.
 *
 * Algorithm:
 * - Traverse both lists from the end (latest seen first)
 * - Match elements in reverse order
 * - If elements match, advance the pointer in the second list
 * - Otherwise, increment counter (this member must have been online)
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for input vectors
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    long cnt(0), idx(n - 1); // cnt counts unmatched elements, idx tracks position in b
    for (long p = n - 1; p >= 0; p--) {
      if (a[p] == b[idx]) { // If current element in a matches element in b
        --idx;              // Move to next element in b
      } else {
        ++cnt; // Increment count of unmatched elements (needs to be online)
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/