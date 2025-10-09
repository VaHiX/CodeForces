// Problem: CF 2062 D - Balanced Tree
// https://codeforces.com/contest/2062/problem/D

/*
D. Balanced Tree
Algorithms/Techniques: Tree DFS, Greedy, Subtree Value Adjustment

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Problem Description:
Given a tree with n nodes, each node has a range [l[i], r[i]] for its value.
We want to make all values equal by performing operations where we can increase 
all values in the subtree of a chosen node v, while considering u as root.

Approach:
- Perform DFS on tree rooted at 1
- For each node u, calculate minimum possible value that can be achieved in its subtree
- If child's computed value (f[v]) is greater than current node's value (f[u]), 
  we must "push up" the excess to maintain balance; this excess contributes to final cost (tag)
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 2e5 + 2;
int T, n, l[N], r[N], f[N];
long long tag;
vector<int> e[N];

void dfs(int u, int fa) {
  f[u] = l[u]; // Initialize with minimum possible value for node u
  for (int v : e[u]) // Iterate through all children of u
    if (v != fa) { // Avoid going back to parent
      dfs(v, u); // Recursively compute for child
      if (f[v] > f[u]) { // If child's value is higher than current node's value
        if (f[v] > r[u]) {
          // If child's value exceeds upper bound of current node, 
          // we need to push up the difference to balance it
          f[u] = r[u], tag += f[v] - r[u];
        } else {
          // Child's value is within bounds of current node, so take it
          f[u] = f[v];
        }
      }
    }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n;
    tag = 0;
    for (int i = 1; i <= n; ++i)
      e[i].clear();
    for (int i = 1; i <= n; ++i)
      cin >> l[i] >> r[i];
    for (int i = 1, u, v; i < n; ++i) {
      cin >> u >> v;
      e[u].push_back(v), e[v].push_back(u);
    }
    dfs(1, 0);
    cout << f[1] + tag << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/