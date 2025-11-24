// Problem: CF 1098 A - Sum in the tree
// https://codeforces.com/contest/1098/problem/A

/*
 * Problem: A. Sum in the tree
 * Algorithms/Techniques: Tree traversal, Greedy, Minimum cost flow concept
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * The solution processes a tree where some "s" values (sum from node to root) are missing.
 * For nodes with even depth, s_v was erased (-1), so we must reconstruct them in a way that
 * minimizes total sum of 'a' values. We use the constraint that s[v] = a[v] + s[parent[v]]
 * to determine valid values for missing s values and compute minimum a values.
 *
 * Strategy:
 * 1. Reconstruct s values for even-depth nodes by propagating forward from root.
 * 2. For each node, ensure s[node] >= s[parent(node)] to maintain valid path sum.
 * 3. Compute total minimum sum of a values using differences s[i] - s[p[i]].
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;

ll n, p[100005], s[100005], ans = 0, i;

int main() {
  scanf("%lld", &n);
  for (i = 2; i <= n; i++)
    scanf("%lld", &p[i]); // Read parent of each node
  for (i = 1; i <= n; i++)
    scanf("%lld", &s[i]); // Read initial s values, -1 means missing

  // Convert -1 to a large number so that they can be processed as valid numbers
  for (i = 1; i <= n; i++)
    if (s[i] == -1)
      s[i] = 1e9 + 1;

  // Propagate minimum s values from children towards parents for even-depth nodes
  for (i = 2; i <= n; i++)
    s[p[i]] = min(s[i], s[p[i]]); // Minimize s of parent based on child’s s

  // Final validation and calculation of answer
  for (i = 1; i <= n; i++) {
    if (s[i] < s[p[i]]) { // If current node's s is less than its parent's s, impossible
      cout << -1 << endl;
      return 0;
    }
    if (s[i] <= 1e9) // Only count valid s values in sum calculation
      ans += s[i] - s[p[i]]; // Contribution to total sum from current node
  }

  cout << ans << endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/