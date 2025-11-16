// Problem: CF 813 C - The Tag Game
// https://codeforces.com/contest/813/problem/C

/*
 * Problem: C. The Tag Game
 * 
 * Description:
 * Alice and Bob play a game on a rooted tree. Alice starts at vertex 1, Bob starts at vertex x (x != 1).
 * Bob moves first. Each turn, a player can either stay or move to an adjacent vertex.
 * The game ends when Alice reaches Bob's position.
 * Alice wants to minimize total moves; Bob wants to maximize.
 * Return the total number of moves in the game under optimal play.
 * 
 * Algorithms/Techniques:
 * - Tree DFS traversal to compute depth and parent info
 * - For each node, store maximum depth of subtree (dpth)
 * - Use distance from root to compute optimal strategy for Bob
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> adj;
const int maxn = 2e5 + 5;
int fa[maxn], dpth[maxn], dist[maxn];
int x, n, i, a, b, ans;

// DFS to compute parent, distance from root, and max depth of subtree for each node
void dfs(int v, int p) {
  dpth[v] = 0;         // Initialize depth of current node
  fa[v] = p;           // Set parent of current node
  for (auto &to : adj[v]) {
    if (to != p) {     // Avoid going back to parent
      dist[to] = dist[v] + 1;  // Set distance from root
      dfs(to, v);      // Recursively process child
      dpth[v] = max(dpth[v], dpth[to] + 1);  // Update max depth of subtree
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin >> n >> x;
  adj.resize(n + 1);  // Resize adjacency list

  // Read edges and build the tree
  for (i = 0; i < n - 1; ++i) {
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(1, 0);  // Start DFS from root (vertex 1)

  // For Bob's optimal strategy: traverse upward from x to find best position
  // The idea: Bob chooses a vertex such that the distance to this vertex
  // plus the max depth of subtree from that vertex is maximized.
  for (a = x, i = 0, ans = 0; i <= (dist[x] - 1) / 2; a = fa[a], i++)
    ans = max(ans, dist[a] + dpth[a]);  // Update max value

  cout << 2 * ans;  // Total moves = 2 * answer due to alternating turns

  return 0;
}


// https://github.com/VaHiX/CodeForces/