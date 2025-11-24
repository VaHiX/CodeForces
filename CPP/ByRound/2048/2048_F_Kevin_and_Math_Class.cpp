// Problem: CF 2048 F - Kevin and Math Class
// https://codeforces.com/contest/2048/problem/F

/*
F. Kevin and Math Class
Algorithms/Techniques: Segment tree with lazy propagation, monotonic stack, binary lifting or divide and conquer.
Time Complexity: O(n log n) per test case due to segment tree processing and stack operations.
Space Complexity: O(n) for storing the input and auxiliary structures.

Problem Summary:
Kevin needs to reduce all elements in array 'a' to 1 by performing operations on segments.
Each operation selects a segment [l, r], finds minimum value x in b[l..r], and updates each a[i] = ceil(a[i]/x).
Goal: Find minimum number of such operations.

Approach:
- For each element in the sequence, we use a monotonic stack to determine for each index,
  which indices form a segment where that element is the minimum value.
- Then we apply a divide-and-conquer tree-like structure (segment tree) where
  at each node, we merge results from left and right children to compute final result.
- The key insight is to track how many operations are needed for each bit position,
  using max and min logic combined with greedy processing.

 */

#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;
const int kMaxN = 2e5 + 1, kL = 64;
struct V {
  LL f[kL], a, b, l, r;
} v[kMaxN];
int s[kMaxN], t, n, m, ans;

// Function to process the tree and compute minimum operations needed
void T(int x) {
  if (x) {
    T(v[x].l), T(v[x].r);
    // Merge values from children into current node's array 'f'
    for (int l = 0, r = 0; l + r < kL;
         (v[v[x].l].f[l] > v[v[x].r].f[r] ? l++ : r++)) {
      v[x].f[l + r] = max({v[v[x].l].f[l], v[v[x].r].f[r], v[x].a});
      (l + r) &&
          (v[x].f[l + r] =
               min(v[x].f[l + r], (v[x].f[l + r - 1] + v[x].b - 1) / v[x].b));
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> t; t--;) {
    cin >> n;
    fill(v + 1, v + 1 + n, v[m = 0]); // Reset data
    for (int i = 1; i <= n; i++) {
      cin >> v[i].a;
    }
    for (int i = 1; i <= n; i++) {
      cin >> v[i].b;
      // Maintain monotonic stack to find leftmost index where b[i] becomes min
      for (; m && v[i].b < v[s[m]].b; m--) {
        v[i].l = s[m];
      }
      m && (v[s[m]].r = i), s[++m] = i;
    }
    T(s[1]); // Start processing the tree
    // Count how many steps are needed to get 'a' to 1
    for (ans = 0; v[s[1]].f[ans] > 1; ans++) {
    }
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/