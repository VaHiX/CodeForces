// Problem: CF 1940 A - Parallel Universes
// https://codeforces.com/contest/1940/problem/A

/*
 * Problem: Parallel Universes
 * Purpose: Determine whether we can make Berlandia connected by flipping at most n edges
 *          between two universes such that Cherlandia remains connected after each flip.
 *
 * Algorithms:
 * - Union-Find (Disjoint Set Union) for tracking connected components in Cherlandia
 * - Graph representation using hash maps (unordered_map)
 * - Greedy strategy for edge selection and adjustment
 *
 * Time Complexity: O(m1 + m2 + n^2) where m1, m2 are the number of edges in Berlandia and Cherlandia
 * Space Complexity: O(n + m1 + m2) 
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#define LL long long
#define LLL __int128
#define uint unsigned
#define ldb long double
#define uLL unsigned long long
using namespace std;
const int N = 3e5 + 5;
int n, m1, m2, fd[N];
unordered_map<int, int> G[N], H[N]; // G: Berlandia, H: Cherlandia

// Find root of x with path compression
inline int find(const int &x) { return x == fd[x] ? x : fd[x] = find(fd[x]); }

// Main function for solving one test case
inline void MAIN() {
  cin >> n >> m1 >> m2;
  // Clear all structures
  for (int i = 1; i <= n; ++i)
    G[i].clear(), H[i].clear(), fd[i] = i;

  // Read Berlandia edges and union them in DSU
  for (int i = 1; i <= m1; ++i) {
    int u, v;
    cin >> u >> v;
    H[u][v] = H[v][u] = 1, fd[find(u)] = find(v); // Union nodes if they're connected in Berlandia
  }

  // Read Cherlandia edges
  for (int i = 1; i <= m2; ++i) {
    int u, v;
    cin >> u >> v;
    G[u][v] = G[v][u] = 1; // Store edges in Cherlandia graph to check connectivity later
  }

  // If Berlandia is already connected (all nodes in same component)
  bool ok = 1;
  for (int i = 1; i <= n; ++i)
    ok &= find(i) == find(1);
  if (ok)
    return cout << "Yes\n0\n", void(); // No need to use any spell

  // Try pairs of nodes in G to see if flipping them makes Berlandia connected
  for (int u = 1; u <= n; ++u)
    for (int v = u + 1; v <= n; ++v)
      if (!(G[u][v] ^ H[u][v])) { // XOR to detect where G and H differ on this edge
        vector<pair<int, int>> ans;
        if (!G[u][v])
          ans.emplace_back(u, v); // Flip unlit edge in Berlandia (i.e., add to lit)

        // Find unconnected nodes to connect using existing connections from Cherlandia
        for (int i = 1; i <= n; ++i)
          if (i != u && i != v && !H[u][i] && !H[v][i]) {
            ans.emplace_back(G[u][i] ? v : u, i); // Use either u-i or v-i connection to reconnect
          }
        cout << "Yes\n" << ans.size() << '\n';
        for (auto [x, y] : ans)
          cout << x << ' ' << y << '\n';
        return;
      }

  if (n < 4) // If n < 4, impossible in this case due to structure constraints
    return cout << "No\n", void();

  vector<pair<int, int>> ans;
  int a = 1, b = 2, c = 3, d = 4;

  // Heuristic choice to choose four points to ensure valid configuration
  if (G[a][b] + G[b][c] + G[c][d] + H[c][a] + H[a][d] + H[d][b] > 3)
    a = 3, b = 1, c = 4, d = 2;

  // Add necessary edges to make Berlandia connected
  if (H[c][a])
    ans.emplace_back(c, a); // Connect c-a in Berlandia
  if (H[a][d])
    ans.emplace_back(a, d);
  if (H[d][b])
    ans.emplace_back(d, b);
  if (G[a][b])
    ans.emplace_back(a, b);
  if (G[b][c])
    ans.emplace_back(b, c);
  if (G[c][d])
    ans.emplace_back(c, d);

  // Add remaining required edges to make Berlandia fully connected
  for (int i = 1; i <= n; ++i)
    if (i != a && i != b && i != c && i != d)
      if (!H[i][a] && !H[i][b] && !H[i][c] && !H[i][d])
        ans.emplace_back(i, a); // Use this node to connect existing components

  cout << "Yes\n" << ans.size() << '\n';
  for (auto [x, y] : ans)
    cout << x << ' ' << y << '\n';
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int t, tid;
  cin >> t >> tid;
  while (t--)
    MAIN();
  return 0;
}


// https://github.com/VaHiX/codeForces/