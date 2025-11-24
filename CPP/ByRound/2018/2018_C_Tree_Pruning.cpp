// Problem: CF 2018 C - Tree Pruning
// https://codeforces.com/contest/2018/problem/C

/*
C. Tree Pruning
time limit per test3 seconds
memory limit per test256 megabytes
t+pazolite, ginkiha, Hommarju - Paved Garden

Task: Given a tree rooted at node 1, we want to make all leaves at the same distance from root by removing edges.
The minimum number of operations (removing leaf and its adjacent edge) is required.

Algorithms/Techniques:
- Tree DFS traversal
- Dynamic Programming on Trees
- Preprocessing to calculate depths and counts of leaves

Time Complexity: O(n) per test case, where n is the number of nodes. Each node is visited once in DFS.
Space Complexity: O(n) for storing the tree structure and auxiliary arrays f, g.

*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
int n, f[500005], g[500005];
vector<int> edge[500005];

// DFS to compute depth counts and leaf counts at each level
int dfs(int x, int from, int deep) {
  int tmp = deep;                 // tmp tracks maximum depth found in subtree
  f[deep]++;                      // increment count of nodes at current depth
  for (auto y : edge[x])          // iterate over adjacent nodes
    if (y != from) {              // avoid going back to parent
      tmp = max(tmp, dfs(y, x, deep + 1));  // recursive DFS call with increased depth
    }
  g[tmp]++;                       // g[i] = number of leaves at depth i
  return tmp;                     // return max depth encountered in subtree
}

inline void solve() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {   // read edges
    int u, v;
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);         // build adjacency list
    edge[v].push_back(u);
  }
  dfs(1, 0, 0);                   // start DFS from root node 1

  int ans = 0;
  for (int i = 1; i <= n; i++)
    f[i] += f[i - 1] - g[i - 1], ans = max(ans, f[i]);  // compute prefix sums and find max
  printf("%d\n", n - ans);        // min operations = total nodes - max number of nodes that can remain
}

inline void clear() {
  for (int i = 0; i <= n; i++)
    f[i] = g[i] = 0, edge[i].clear();  // reset arrays and edges
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    clear();
    solve();
  }
}


// https://github.com/VaHiX/codeForces/