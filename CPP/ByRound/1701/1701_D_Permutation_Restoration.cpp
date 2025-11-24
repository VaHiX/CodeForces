// Problem: CF 1701 D - Permutation Restoration
// https://codeforces.com/contest/1701/problem/D

/*
 * Problem: D. Permutation Restoration
 * 
 * Algorithm: 
 *   - Use a greedy approach with a set to assign values to positions.
 *   - For each position i, compute the valid range [l, r] where a[i] can be placed,
 *     based on the constraint b[i] = floor(i / a[i]).
 *   - Use a set to maintain intervals and assign the smallest available position
 *     to each element in order.
 * 
 * Time Complexity: O(n log n) per test case due to sorting with set operations.
 * Space Complexity: O(n) for storing arrays and sets.
 * 
 * Techniques:
 *   - Interval assignment using a set to track valid ranges.
 *   - Greedy assignment of smallest possible values.
 */

#include <stdio.h>
#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;
const int N = 5e5 + 7, INF = 1e9;
typedef pair<int, int> pa;
int T_T, i, n, x, ans[N], l, r;
set<pa> s;
vector<pa> f[N];
int main() {
  for (scanf("%d", &T_T); T_T--;) {
    for (scanf("%d", &n), i = 1; i <= n; ++i) {
      scanf("%d", &x);
      // Compute left and right bounds for a[i] such that floor(i / a[i]) = x
      l = i / (x + 1) + 1;
      r = x ? i / x : n;
      f[l].push_back({r, i});  // Store interval [l, r] for position i
    }
    for (i = 1; i <= n; ++i) {
      // Insert all intervals that start at or before i into the set
      for (auto p : f[i])
        s.insert(p);
      // Assign smallest available position to a[p.second]
      ans[s.begin()->second] = i;
      // Remove the used interval from the set
      s.erase(s.begin());
    }
    for (i = 1; i <= n; ++i)
      printf("%d ", ans[i]), f[i].clear();  // Print result and reset f
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/