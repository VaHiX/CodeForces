// Problem: CF 1646 B - Quality vs Quantity
// https://codeforces.com/contest/1646/problem/B

/*
B. Quality vs Quantity

Algorithm: Sorting + Two Pointers / Greedy
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the array

The problem asks whether we can partition a sequence into two groups (Red and Blue)
such that Sum(RED) > Sum(BLUE) and Count(RED) < Count(BLUE).

Key insight:
- We sort the array first.
- To maximize sum with minimal count, we try to assign largest elements to Red group.
- To minimize count with maximum sum, we try to assign smallest elements to Blue group.
- The condition is checked by comparing prefix sum and suffix sum.

The approach:
- Sort the array.
- Take the first (n+1)/2 elements as Red group (to keep count small).
- Take the rest as Blue group (to maximize sum).
- Compare sum of Red vs sum of Blue.
*/

#include <stdio.h>
#include <algorithm>
#include <numeric>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  int a[n];
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  sort(a, a + n);
  // Compare sum of first half (potential red group) with sum of second half (potential blue group)
  printf(accumulate(a, a + (n + 1) / 2, 0ll) <
                 accumulate(a + (n + 2) / 2, a + n, 0ll)
             ? "YES\n"
             : "NO\n");
}

int main() {
  int T;
  scanf("%d", &T);
  for (int i = 0; i < T; ++i) {
    solve();
  }
}


// https://github.com/VaHiX/codeForces/