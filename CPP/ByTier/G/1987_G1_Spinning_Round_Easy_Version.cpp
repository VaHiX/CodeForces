// Problem: CF 1987 G1 - Spinning Round (Easy Version)
// https://codeforces.com/contest/1987/problem/G1

/*
Algorithm: This solution uses a monotonic stack to compute the left and right "largest index"
           where p[j] > p[i] for each i. Then, it constructs a binary tree from these relations
           and performs a DFS to compute maximum distances (diameter) in the tree.
           For each node, it tracks:
           - f[i]: maximum distance in the left subtree
           - g[i]: maximum distance in the right subtree
           - mx[i]: maximum path passing through node i
           - dep[i]: depth of node i in the tree
           - mxf[i], mxg[i]: auxiliary values for tracking max distance from each node upwards

Time Complexity: O(n) amortized per test case due to stack operations and DFS traversal
Space Complexity: O(n) for storing arrays and recursion stack
*/

#include <algorithm>
#include <cstdio>
const int INF = 1000000000;
using std::max;
int a[400005], stk[400005], f[400005], g[400005], mxf[400005], mxg[400005],
    dep[400005], top;
int ls[400005], rs[400005], mx[400005];

// Depth-first search to compute max distances in the constructed tree
void dfs(int u) {
  if (ls[u]) {
    dep[ls[u]] = dep[u] + 1, dfs(ls[u]), mx[u] = max(mx[u], mx[ls[u]] + 1);
    f[u] = max(f[u], mxg[ls[u]] - dep[u]), mxf[u] = mxf[ls[u]];
  }
  if (rs[u]) {
    dep[rs[u]] = dep[u] + 1, dfs(rs[u]), mx[u] = max(mx[u], mx[rs[u]] + 1);
    g[u] = max(g[u], mxf[rs[u]] - dep[u]), mxg[u] = mxg[rs[u]];
  }
  int tmp = mx[ls[u]] + mx[rs[u]] + 2;
  f[u] = max(f[u], tmp), g[u] = max(g[u], tmp);
  mxf[u] = max(mxf[u], f[u] + dep[u]);
  mxg[u] = max(mxg[u], g[u] + dep[u]);
}

int main() {
  mx[0] = -1;
  int _;
  scanf("%d", &_);
  while (_--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i), f[i] = g[i] = ls[i] = rs[i] = dep[i] = mx[i] = 0;
      mxf[i] = mxg[i] = -INF;
    }
    scanf("%*s"); // Read and discard the string s, since all are '?'
    stk[top = 1] = 1;
    for (int i = 2; i <= n; ++i) {
      bool lft = false;
      while (top && a[stk[top]] < a[i])
        --top, lft = true;
      if (lft)
        ls[i] = stk[top + 1]; // Assign the leftmost larger element's index
      if (top)
        rs[stk[top]] = i;     // Assign current element as right child of top
      stk[++top] = i;         // Push current index to stack
    }
    int rt = stk[1];          // Root is at top of stack
    dfs(rt);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
      ans = max(ans, max(f[i], g[i])); // Find maximum diameter
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/