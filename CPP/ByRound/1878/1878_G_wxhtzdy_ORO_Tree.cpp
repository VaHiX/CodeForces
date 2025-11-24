// Problem: CF 1878 G - wxhtzdy ORO Tree
// https://codeforces.com/contest/1878/problem/G

/*
Purpose: Solve the IOI 2023 problem "wxhtzdy ORO Tree" where we need to find the maximum "niceness" 
         of any vertex on the shortest path between two vertices in a tree. Niceness is defined as 
         the sum of the number of non-zero bits in the OR of values along paths from query vertices to 
         each vertex on the path.

Algorithms/Techniques Used:
- Binary Lifting for LCA (Lowest Common Ancestor) computation
- Preprocessing to calculate OR values along paths from each vertex to ancestors
- Efficient traversal and querying using precomputed data structures

Time Complexity: O(N * log N + Q * log N) per test case
Space Complexity: O(N * log N) for storing binary lifting and OR data structures

Note: The implementation uses several optimizations including precomputation and binary search
to efficiently determine the maximum niceness for each query.
*/

#include <string.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define MX 200005
#define cmp                                                                    \
  [&](const pi &x, const pi &y) {                                              \
    return dp[x.first] > dp[y.first] ||                                        \
           dp[x.first] == dp[y.first] && x.second < y.second;                  \
  }
typedef pair<int, int> pi;
int T, N, A[MX], Q, par[20][MX], dp[MX], ans[MX];
vector<int> adj[MX], pos[MX], tmppos;
vector<pi> ors[MX];
inline void DFS(int u = 1, int p = 0) {
  par[0][u] = p;
  // Initialize position array for each bit
  for (int i = 0; i <= 30; i++)
    if (A[u] & (1 << i))
      pos[u][i] = u;
  // Traverse children
  for (int &v : adj[u])
    if (v != p) {
      pos[v] = pos[u]; // Copy parent's position info
      dp[v] = dp[u] + 1; // Depth tracking
      DFS(v, u);
    }
  // Sort positions by depth in descending order for efficient processing
  sort(tmppos.begin(), tmppos.end(),
       [&](int &x, int &y) { return dp[pos[u][x]] > dp[pos[u][y]]; });
  ors[u].clear();
  int val = 0;
  ors[u].push_back({u, 0}); // Start with current node
  for (int &bit : tmppos) {
    if (pos[u][bit] == 0)
      break;
    if (pos[u][bit] == ors[u].back().first)
      ors[u].back().second = (val |= (1 << bit)); // Update OR value from bit
    else
      ors[u].push_back({pos[u][bit], (val |= (1 << bit))}); // Add new entry
  }
}
inline void Build_LCA() {
  pos[1].assign(31, 0);
  dp[1] = 1;
  DFS();
  // Build binary lifting table for LCA
  for (int i = 1; i <= 18; i++)
    for (int j = 0; j <= N; j++)
      par[i][j] = par[i - 1][par[i - 1][j]];
}
inline int LCA(int u, int v) {
  // Ensure u is deeper than v
  if (dp[u] < dp[v])
    swap(u, v);
  // Lift u to same depth as v
  for (int i = 18; i >= 0; i--)
    if (dp[u] >= dp[v] + (1 << i))
      u = par[i][u];
  if (u == v)
    return u;
  // Move both up until they meet
  for (int i = 18; i >= 0; i--)
    if (par[i][u] != par[i][v])
      u = par[i][u], v = par[i][v];
  return par[0][u];
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  memset(par, 0, sizeof(par));
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i <= 30; i++)
    tmppos.push_back(i);
  cin >> T;
  while (T--) {
    cin >> N;
    for (int i = 1; i <= N; i++)
      cin >> A[i];
    for (int i = 1; i < N; i++) {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v), adj[v].push_back(u);
    }
    Build_LCA();
    cin >> Q;
    while (Q--) {
      int u, v;
      cin >> u >> v;
      int anc = LCA(u, v), p = par[0][anc]; // Find LCA and its parent
      // Get OR values for paths to ancestors
      int valu = (upper_bound(ors[u].begin(), ors[u].end(), pi{p, -1}, cmp) - 1)
                     ->second;
      int valv = (upper_bound(ors[v].begin(), ors[v].end(), pi{p, -1}, cmp) - 1)
                     ->second;
      int mx = __builtin_popcount(valu) + __builtin_popcount(valv);
      // Check all nodes in u's path
      for (auto item : ors[u]) {
        if (dp[item.first] <= dp[anc])
          break;
        int z = item.first;
        mx = max(mx, __builtin_popcount(item.second) +
                         __builtin_popcount(
                             valv | (upper_bound(ors[z].begin(), ors[z].end(),
                                                 pi{p, -1}, cmp) -
                                     1)
                                        ->second));
      }
      // Check all nodes in v's path
      for (auto item : ors[v]) {
        if (dp[item.first] <= dp[anc])
          break;
        int z = item.first;
        mx = max(mx, __builtin_popcount(item.second) +
                         __builtin_popcount(
                             valu | (upper_bound(ors[z].begin(), ors[z].end(),
                                                 pi{p, -1}, cmp) -
                                     1)
                                        ->second));
      }
      cout << mx << " ";
    }
    cout << "\n";
    for (int i = 1; i <= N; i++)
      adj[i].clear();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/