// Problem: CF 1615 E - Purple Crayon
// https://codeforces.com/contest/1615/problem/E

/*
 * Problem: Purple Crayon
 * Purpose: Determine the optimal score of a two-player game on a tree where 
 *          Red colors up to k nodes and Blue colors any non-red nodes.
 * Algorithm: 
 *   - Use DFS to compute subtree sizes for each node.
 *   - Greedily select subtrees to maximize Red's score, then calculate Blue's optimal response.
 *   - For each possible number of red nodes Red chooses, compute the resulting score.
 * 
 * Time Complexity: O(n * log n) due to priority queue operations and DFS traversal
 * Space Complexity: O(n) for storing the tree and priority queues
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define maxn 200010
using namespace std;
int n, m;
priority_queue<int> q[maxn];  // stores subtree sizes for each node
vector<int> g[maxn];         // adjacency list representation of the tree

// DFS function to calculate subtree sizes
void dfs(int u, int p) {
  for (int v : g[u]) {
    if (v != p) {
      dfs(v, u);
      // Swap to ensure smaller queue is merged into larger one for efficiency
      if (q[u].size() < q[v].size())
        swap(q[u], q[v]);
      // Merge all elements of q[v] into q[u]
      while (q[v].size())
        q[u].push(q[v].top()), q[v].pop();
    }
  }
  // If no children, initial subtree size is 1
  if (q[u].empty())
    q[u].push(1);
  else {
    int t = q[u].top();
    q[u].pop(), q[u].push(t + 1);  // increment the size since we include the node itself
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  // Read edges and build adjacency list
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
  }
  dfs(1, -1);  // Start DFS from root node 1

  int used = 0;             // Number of nodes Red has colored
  long long ans = -1e18;    // Initialize answer to a very small number

  // Try all possible numbers of red nodes Red can color (from 0 to m)
  for (int i = 0; i <= m; i++) {
    // Calculate maximum number of blue nodes Blue can color
    int j = min(n / 2, n - used);
    // Compute score using formula: white * (red - blue)
    ans = max(ans, 1ll * (i - j) * (n - i - j));
    // If there are remaining subtrees to choose, add the size of the largest subtree to used
    if (q[1].size())
      used += q[1].top(), q[1].pop();
  }
  cout << ans << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/