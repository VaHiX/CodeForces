// Problem: CF 2131 F - Unjust Binary Life
// https://codeforces.com/contest/2131/problem/F

/*
F. Unjust Binary Life

Purpose:
This code solves a dynamic programming and optimization problem involving two binary strings,
a and b, that define an n×n grid based on XOR operations. The goal is to compute the total minimum
number of bit flips needed to make valid paths (from (1,1) to all (x,y)) possible, where each cell in
the path must be 0.

Algorithms/Techniques:
- Prefix sums for efficient range queries.
- Sorting and binary search for optimization.
- Mathematical derivation using cumulative sums and order statistics.

Time Complexity: O(n log n) per test case due to sorting and binary searches.
Space Complexity: O(n) for storing intermediate arrays and prefix sums.

*/

#include <algorithm>
#include <iostream>
#define L long long
using namespace std;
constexpr int Mn = 2e5 + 11;
char c[Mn], k[Mn];
int h[Mn], l[Mn], n, i, p, l1[Mn], h1[Mn];
L y, g1, g2, q[Mn];

void C() {
  y = g1 = g2 = 0;
  cin >> n >> c + 1 >> k + 1;
  // Compute prefix sums of '0' counts and cumulative XOR differences
  for (i = 1; i <= n; i++) {
    h1[i] = h1[i - 1] + (c[i] == '0');       // Prefix count of 0s in string c
    l1[i] = l1[i - 1] + (k[i] == '0');       // Prefix count of 0s in string k
    g1 += h1[i];                             // Total number of cells that can be flipped to make a path valid at each column
    g2 += l1[i];                             // Same as above, but for rows
    h[i] = h[i - 1] + ((c[i] == '1') ? -1 : 1);  // Cumulative XOR difference (c[i] - k[i]) in terms of contribution to path validity
    l[i] = l[i - 1] + ((k[i] == '1') ? 1 : -1);  // Same as above but for row-wise contribution
  }
  l[n + 1] = 1e9;                                // Sentinel value for binary search
  sort(l + 1, l + n + 2);                        // Sort prefix sums of k contributions for efficient querying
  for (i = 1; i <= n; i++)
    q[i] = q[i - 1] + l[i];                      // Compute prefix sum of sorted values for range queries
  for (i = 1; i <= n; i++) {
    p = lower_bound(l + 1, l + n + 2, h[i]) - l; // Find how many elements in sorted list are less than or equal to h[i]
    y += q[p - 1] - 1LL * h[i] * (p - 1);       // Calculate cost using prefix sums and math
  }
  cout << y + g1 * n + g2 * n << '\n';           // Final answer includes global penalties for flip costs
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    C();
  return 0;
}


// https://github.com/VaHiX/codeForces/