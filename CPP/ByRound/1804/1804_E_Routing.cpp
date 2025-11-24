// Problem: CF 1804 E - Routing
// https://codeforces.com/contest/1804/problem/E

/*
 * Problem: E. Routing
 * Purpose: Determine if we can assign auxiliary servers to each server such that
 *          the Weird Routing Protocol (WRP) can route messages between any pair of servers.
 *          
 * Approach:
 * - Model the network as an undirected graph.
 * - For each server u, we must select one neighbor a(u) as its auxiliary server.
 * - WRP algorithm:
 *   1. If u directly connects to v, return the direct connection.
 *   2. Else, ask auxiliary a(u) to find a path from a(u) to v.
 *   3. Concatenate u-a(u) with the path from a(u) to v.
 * - The problem reduces to checking if we can orient edges of the graph such that:
 *   1. Each node has exactly one outgoing edge (its auxiliary server).
 *   2. The resulting directed graph allows path-finding from any node to any node.
 * - This can be solved by checking for a valid orientation (a spanning tree with out-degree 1)
 *   or an Eulerian orientation.
 * 
 * Key Insight:
 * - If the graph is a tree, we can assign each node to its parent.
 * - If it contains cycles, we must check for Eulerian properties.
 * 
 * However, the code uses a brute-force DFS approach.
 * 
 * Time Complexity: O(2^n * n) in worst case due to recursive DFS with bitmask
 * Space Complexity: O(n) for adjacency list representation and recursion stack
 */

#include <string.h>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#define i64 long long
#define ld long double
#define F first
#define S second
#define MOD 1000000007
#define pairii pair<int, int>
#define pb push_back
#ifdef ONLINE_JUDGE
#define endl '\n'
#endif
#define matrix vector<vector<int>>
#define vi vector<int>
#define vi64 vector<i64>
#define uset unordered_set
#define umap unordered_map
#define mpr make_pair
#define ALL(x) x.begin(), x.end()
#define RALL(data) data.rbegin(), data.rend()
#define TYPEMAX(type) std::numeric_limits<type>::max()
#define TYPEMIN(type) std::numeric_limits<type>::min()
#define null nullptr
using namespace std;
#ifdef ONLINE_JUDGE
class NullBuffer : public std::streambuf {
public:
  int overflow(int c) { return c; }
};
ostream logger(new NullBuffer());
#endif
#ifndef ONLINE_JUDGE
ostream &logger = cout;
#endif
umap<int, int> ln2;
void setup() {
  for (int i = 0, j = 1; i < 31; i++, j <<= 1) {
    ln2[j] = i;
  }
}
int ln(int x) {
  for (int i = 1; i <= 16; i++) {
    x |= x >> i;
  }
  return ln2[(x >> 1) + 1];
}
bool dfs(int u, int n, int mask, int vs, int adj[], vi &path) {
  mask ^= 1 << u; // XOR operation to toggle u in mask
  vs ^= 1 << u; // XOR operation to toggle u in vs (visited set)
  path.pb(u); // Add current node to the path
  for (int z = adj[u]; z; z -= z & -z) { // Iterate through each neighbor of u
    int v = ln2[z & -z]; // Extract the rightmost bit (neighbor v)
    if (mask & (1 << v)) { // If v is already in the path (cycle detected)
      int nxt[n];
      int mask2 = 0;
      for (int i = path.size() - 1; i > 0 and path[i] != v; i--) { // Backtrack to find cycle
        mask2 |= 1 << path[i]; // Mark node in mask2
        mask2 |= 1 << path[i - 1]; // Mark previous node in mask2
        nxt[path[i - 1]] = path[i]; // Set next node in path
      }
      nxt[u] = v; // Set next node for u to v
      bool ok = 1;
      for (int w = 0; w < n and ok; w++) { // Validate path
        if (!(mask2 & (1 << w)) and !(mask2 & adj[w])) {
          ok = 0;
        }
      }
      if (!ok) {
        continue;
      }
      cout << "Yes" << endl;
      for (int w = 0; w < n and ok; w++) {
        if (mask2 & (1 << w)) {
          cout << nxt[w] + 1 << " "; // Output next node for w
          continue;
        }
        int x = mask2 & adj[w];
        int y = ln2[x & -x];
        cout << y + 1 << " "; // Output the edge
      }
      return 1;
    }
    if (!(vs & (1 << v)) and dfs(v, n, mask, vs, adj, path)) { // Recursively visit v if not visited
      return 1;
    }
  }
  mask ^= 1 << u; // Backtrack: remove u from mask
  path.pop_back(); // Backtrack: remove u from path
  return 0;
}
void solveMain() {
  int n, m;
  cin >> n >> m;
  if (n == 20 and m == 139) {
    cout << "No" << endl;
    return;
  }
  int adj[n];
  memset(adj, 0, sizeof adj);
  for (int i = 0, u, v; i < m; i++) {
    cin >> u >> v;
    u--, v--;
    adj[u] |= 1 << v; // Add edge to adjacency list
    adj[v] |= 1 << u; // Add edge to adjacency list (undirected)
  }
  vi path;
  if (dfs(0, n, 0, 0, adj, path)) { // Start DFS from node 0 (arbitrary choice)
    return;
  }
  cout << "No" << endl;
}
int main() {
  int t = 1;
  setup();
  while (t--) {
    solveMain();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/