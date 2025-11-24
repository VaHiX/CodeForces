// Problem: CF 2014 F - Sheriff's Defense
// https://codeforces.com/contest/2014/problem/F

/*
F. Sheriff's Defense
Algorithms/Techniques: Tree Dynamic Programming (DP), DFS traversal on a tree
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the tree and DP states

Problem Description:
The Sheriff has n camps connected in a tree structure, each with initial gold 'a[i]'.
To strengthen a camp, we can spend 'c' gold from each neighbor to increase the strength of that camp.
A strengthened camp survives; others are destroyed.
Goal is to maximize total surviving gold after optimal strengthening.

Approach:
- Use DFS on tree with DP state f[x][0] and f[x][1] where:
  - f[x][0]: max gold if we don't strengthen node x
  - f[x][1]: max gold if we do strengthen node x

For each node, we decide whether to strengthen it:
- If not strengthened: sum of max of (child not strengthened, child strengthened) for all children
- If strengthened: current node's value + sum of (max of child states - 2 * c)
*/
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>

using namespace std;
typedef long long ll;
#define N 400000
ll i, j, k, n, m, t, a[N + 50], f[N + 50][2];
basic_string<ll> v[N + 50];

void dfs(int x, int fa) {
  f[x][0] = 0;                           // Base case: not strengthening this node
  f[x][1] = a[x];                        // If we strengthen this node, gain its value
  for (auto i : v[x])                    // For each neighbor
    if (i != fa) {                       // Avoid going back to parent
      dfs(i, x);                         // Recurse into subtree
      f[x][0] += max(f[i][0], f[i][1]);   // Don't strengthen x: take best from children
      f[x][1] += max(f[i][0], f[i][1] - 2 * m); // Strengthen x: cost of 2*m to neighbors, but still gain value
    }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;                       // Read number of nodes and cost per strengthening
    for (i = 1; i <= n; i++)
      cin >> a[i];                       // Read initial gold at each camp
    for (i = 1; i < n; i++) {            // Read edges to build adjacency list
      cin >> j >> k;
      v[j] += k;                         // Add edge in both directions (undirected tree)
      v[k] += j;
    }
    dfs(1, 0);                           // Start DFS from root node
    cout << max(f[1][0], f[1][1]) << '\n'; // Output maximum gold achievable
    for (i = 1; i <= n; i++)
      v[i] = {};                         // Clear adjacency list for next test case
  }
}


// https://github.com/VaHiX/codeForces/