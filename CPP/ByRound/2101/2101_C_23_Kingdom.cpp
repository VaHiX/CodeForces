// Problem: CF 2101 C - 23 Kingdom
// https://codeforces.com/contest/2101/problem/C

/*
C. 23 Kingdom
Algorithms/Techniques: Union-Find, Prefix/Suffix Computation, Greedy
Time Complexity: O(n α(n)) where α is the inverse Ackermann function (nearly constant)
Space Complexity: O(n)

The problem asks to find the maximum possible beauty of a "nice" array b,
where each element of b is between 1 and corresponding element in input array a.
Beauty is defined as sum over all distinct values x of the largest gap d_x(c) between
two occurrences of x in the array.

This solution uses a greedy approach with Union-Find to simulate placing elements
in such a way that maximizes gaps for each value. It precomputes prefix and suffix
counts of how many times we can "place" an element in a way that increases beauty,
then computes the maximum by taking minimums from left and right.

Key observations:
- For each number x, when we place it at index i, we want to find a previous unplaced
  position j such that placing x at i and j creates a large gap.
- To do this efficiently, use Union-Find with path compression to track the latest
  available index for each number which can be used to create the maximum gap.

The idea is:
1. Precompute prefix count for forward pass: how many valid placements from left.
2. Precompute suffix count for backward pass: how many valid placements from right.
3. For each split point, combine the counts to get optimal result.

*/

#include <algorithm>
#include <iostream>

#define ll long long
using namespace std;
const int N = 2e5 + 10;
int n, a[N], fa[N], pre[N], suf[N];

// Union-Find find with path compression
int findfa(int x) { return x == fa[x] ? x : fa[x] = findfa(fa[x]); }

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  // Initialize Union-Find structure
  for (int i = 1; i <= n; i++)
    fa[i] = i;
  // Forward pass: calculate prefix count of valid placements
  for (int i = 1; i <= n; i++) {
    int x = findfa(a[i]);  // Find the root of current value's group
    pre[i] = pre[i - 1];   // Carry forward previous count
    if (x) {               // If a valid index exists to place value
      pre[i]++;            // Increment count
      fa[x] = x - 1;       // Mark this position as used (move root backward)
    }
  }
  // Reset Union-Find
  for (int i = 1; i <= n; i++)
    fa[i] = i;
  // Backward pass to compute suffix count
  suf[n + 1] = 0;
  for (int i = n; i >= 1; i--) {
    int x = findfa(a[i]);  // Find the root of current value's group
    suf[i] = suf[i + 1];   // Carry forward previous count
    if (x) {               // If a valid index exists to place value
      suf[i]++;            // Increment count
      fa[x] = x - 1;       // Mark this position as used (move root backward)
    }
  }
  // Compute final answer by combining prefix and suffix counts
  ll ans = 0;
  for (int i = 1; i < n; i++) {
    ans += min(pre[i], suf[i + 1]);  // Take minimum of left and right to avoid overcounting
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
}


// https://github.com/VaHiX/codeForces/