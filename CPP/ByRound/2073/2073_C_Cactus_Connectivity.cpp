// Problem: CF 2073 C - Cactus Connectivity
// https://codeforces.com/contest/2073/problem/C

/*
 * Problem: Cactus Connectivity
 * Algorithm: Union-Find + DFS for bipartite coloring
 * Time Complexity: O(n + m * α(n)) where α is the inverse Ackermann function
 * Space Complexity: O(n + m)
 *
 * Task:
 * Given a cactus graph (a graph where any two simple cycles share at most one vertex),
 * determine its connectivity value, which is the smallest k such that adding any k edges
 * makes the graph 1-edge-connected.
 *
 * Approach:
 * - Use Union-Find to detect and merge connected components.
 * - For each edge in input, if it connects two different components (i.e., not already in same set),
 *   add it to union-find structure and build an adjacency list.
 * - Use DFS with bipartite coloring to separate nodes into connected components.
 * - Count how many edges need to be flipped to satisfy required condition for connectivity.
 */

#include <iostream>

#define N 500005
#define M 505
#define LL long long
#define inf 2147483647
#define LD long double
#define eps 1e-6
using namespace std;
int n, m, f[N], c[N], u[N], v[N], ans;
bool vis[N];
int tot, fir[N], nxt[N << 1], son[N << 1];

// Add an edge to adjacency list
inline void add(int x, int y) {
  son[++tot] = y, nxt[tot] = fir[x], fir[x] = tot;
}

// Find root with path compression for Union-Find
inline int gf(int x) { return f[x] == x ? x : f[x] = gf(f[x]); }

// DFS to color the nodes in bipartite way
inline void dfs(int x, int fa) {
  c[x] = c[fa] ^ 1, vis[x] = 1;
  for (int i = fir[x]; i; i = nxt[i])
    if (son[i] ^ fa)
      dfs(son[i], x);
}

// Main solving function
inline void solve(int tc) {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    f[i] = i; // Initialize Union-Find
  for (int i = 1, x, y; i <= m; i++)
    cin >> x >> y, 
        // If x and y are not in same component, merge them and add edge to graph
        (gf(x) ^ gf(y)) && (f[f[x]] = f[y], add(x, y), add(y, x), 0),
        u[i] = x, v[i] = y;
  for (int i = 1; i <= n; i++)
    if (!vis[i])
      dfs(i, 0); // Traverse all unvisited nodes
  for (int i = 1; i <= m; i++)
    if (c[u[i]] ^ c[v[i]])
      ans++; // Count miscolored edges
  cout << ans + 1 << '\n'; // Add one to get the correct connectivity value
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int tc = 1;
  while (tc--)
    solve(tc);
  return 0;
}


// https://github.com/VaHiX/codeForces/