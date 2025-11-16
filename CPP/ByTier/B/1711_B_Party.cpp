// Problem: CF 1711 B - Party
// https://codeforces.com/contest/1711/problem/B

/*
 * Code Purpose: 
 *   Finds the minimum possible total unhappiness value of a party, 
 *   such that the number of cakes eaten (i.e., pairs of friends both invited) is even.
 * 
 * Algorithm:
 *   - For each test case, we compute the minimum unhappiness value.
 *   - We keep track of the degree of each node (number of friends).
 *   - The key insight:
 *     - If the number of edges (m) is even, then we can always select a subset of nodes 
 *       such that even number of edges are covered — so we just need to find the minimum 
 *       unhappiness value when we don't invite any nodes.
 *     - If the number of edges (m) is odd, then we must ensure an even number of cakes.
 *       This means either:
 *         1. We include a node with odd degree to "fix" the parity (so that some edge pairs
 *            become even), or
 *         2. We must include a pair of nodes such that both have degree 1 (and can be paired).
 *       Our optimal choice is to either include the minimum unhappiness node with odd degree
 *       or find minimum cost of a pair (as described).
 * 
 * Time Complexity: O(N + M) per test case, where N is the number of nodes and M is the number of edges.
 * Space Complexity: O(N) for storing degrees and unhappiness values.
 */

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 300013;
int a[N], d[N], T, x, y, i, n, m, mn;
int main() {
  cin >> T;
  while (T--) {
    mn = 2e9; // Initialize minimum unhappiness to large value
    cin >> n >> m;
    for (i = 1; i <= n; i++)
      d[i] = 0, cin >> a[i]; // Reset degrees and read node unhappiness
    for (i = 1; i <= m; i++)
      cin >> x >> y, d[x]++, d[y]++, mn = min(mn, a[x] + a[y]); // Track degrees and min pair unhappiness
    if (m & 1) // If number of edges is odd, we need to handle odd degree nodes
      for (i = 1; i <= n; i++)
        if (d[i] & 1) // If degree is odd
          mn = min(mn, a[i]); // Update the minimum unhappiness value for including an odd-degree node
    cout << mn * (m & 1) << '\n'; // If m is odd, we use the adjusted minimum; otherwise 0
  }
}


// https://github.com/VaHiX/CodeForces/