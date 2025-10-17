// Problem: CF 2063 E - Triangle Tree
// https://codeforces.com/contest/2063/problem/E

/*
E. Triangle Tree

Algorithm:
This code computes the sum of all valid triangle-side-length functions f(u,v) over all pairs (u,v) such that u and v are not ancestors of each other in a rooted tree.

Approach:
- The solution uses a DFS traversal to compute subtree sizes and sums.
- It calculates contributions from good pairs based on distance properties.
- It processes the tree to derive triangle constraints using lca distances.
- Time Complexity: O(N) for all test cases combined due to amortized analysis.
  Space Complexity: O(N) for storing graph and auxiliary arrays.

Key Techniques:
- Tree DFS traversal with subtree size calculations
- LCA-based distance computations
- Mathematical formulae to optimize triangle constraint checks

*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 3e5 + 5;
int tot, he[N], ne[N * 2], to[N * 2];
long long siz[N], s[N], ans, de[N];

// DFS function to traverse the tree and compute subtree information
void dfs(int x, int fa) {
  int i, y;
  siz[x] = 0;
  s[x] = 0;
  for (i = he[x]; i != 0; i = ne[i]) {        // Iterate over neighbors
    y = to[i];
    if (y != fa) {
      de[y] = de[x] + 1;                      // Set depth of child
      dfs(y, x);                              // Recursively process subtree
      // Compute contribution to answer based on current node and its children
      ans += s[x] * siz[y] + siz[x] * (siz[y] + s[y]) - siz[x] * siz[y];
      siz[x] += siz[y];                       // Update size of subtree rooted at x
      s[x] += s[y] + siz[y];                  // Update sum for current node
    }
  }
  siz[x]++;                                    // Account for the node itself
}

int main() {
  int T, n, i, x, y;
  long long sum;
  scanf("%d", &T);
  while (T > 0) {
    T--;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
      he[i] = 0;                                // Initialize adjacency list
    tot = 0;
    ans = 0;
    for (i = 1; i < n; i++) {                 // Build adjacency list for the tree
      scanf("%d%d", &x, &y);
      tot++;
      ne[tot] = he[x];
      to[tot] = y;
      he[x] = tot;
      tot++;
      ne[tot] = he[y];
      to[tot] = x;
      he[y] = tot;
    }
    de[1] = 0;
    dfs(1, 0);                                // Start DFS from root node
    for (i = 0; i <= n; i++)
      s[i] = 0;                               // Reset array for depth-based computation
    for (i = 1; i <= n; i++) {
      ans += de[i] * (de[i] + 1) / 2;         // Add initial triangle count based on depth
      s[de[i]]++;                             // Count nodes by their depths
    }
    sum = 0;
    for (i = 1; i <= n; i++) {
      ans = ans - (s[i - 1] * i - sum) * s[i]; // Adjust based on depth count differences
      sum += s[i] * i;                        // Update prefix sum
      s[i] += s[i - 1];                       // Build prefix sums for depths
    }
    printf("%lld\n", ans);                    // Output result for this test case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/