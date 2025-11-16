// Problem: CF 2053 E - Resourceful Caterpillar Sequence
// https://codeforces.com/contest/2053/problem/E

/*
E. Resourceful Caterpillar Sequence
Algorithms/Techniques: Tree traversal, graph analysis, combinatorics.
Time Complexity: O(n) per test case, where n is the number of vertices.
Space Complexity: O(n) for storing the tree and auxiliary arrays.

The problem involves counting pairs (p,q) such that Aron wins a game played on a tree,
where players move caterpillars (paths between two endpoints) in alternating turns.
Aron wins if the tail q becomes a leaf at some point during the game.
This implementation computes for each node how many valid pairs (p,q) lead to Aron's win
by analyzing the structure of the tree and degrees of nodes.

Key insight:
- If q is a leaf initially, Aron wins immediately.
- Otherwise, the analysis counts valid configurations considering only internal nodes for p and q,
  ensuring no winning moves exist for Nora before Aron can win.

The code uses:
1. Degree counting to identify leaves and internal nodes.
2. BFS-style logic to compute branching behavior of non-leaf nodes.
3. Combinatorial calculation to count valid (p,q) pairs efficiently.
*/

#include <stdio.h>
#include <vector>
using namespace std;
typedef long long ll;

// edge[u] stores the adjacency list for node u
vector<int> edge[200002];
// d[i] stores degree of node i
int d[200002], b[200002];

// Function to compute number of valid pairs (p,q) where Aron wins
ll solve(int n) {
  // Build adjacency list and degree count
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
    d[u]++, d[v]++;
  }

  int leaf = 0, bleaf = 0;
  // Identify leaves and count special nodes
  for (int i = 1; i <= n; i++)
    if (d[i] == 1) {
      leaf++;
      int y = edge[i].front();
      if (d[y] != 1) {
        if (!b[y])  // Only count once per internal node
          bleaf++;
        b[y]++;
      }
    }

  // Start with default contribution: all leaves with non-leaves
  ll ans = 1ll * leaf * (n - leaf);

  // Add contributions from branching nodes
  for (int i = 1; i <= n; i++)
    if (b[i])
      ans += 1ll * (n - leaf - bleaf) * (d[i] - b[i] - 1);
  
  return ans;
}

int main() {
  int _;
  scanf("%d", &_);
  while (_--) {
    int n;
    scanf("%d", &n);
    // Clear all data structures for next test case
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
      d[i] = b[i] = 0;
    }
    printf("%lld\n", solve(n));
  }
}


// https://github.com/VaHiX/codeForces/