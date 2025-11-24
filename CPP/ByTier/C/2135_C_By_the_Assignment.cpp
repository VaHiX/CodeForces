// Problem: CF 2135 C - By the Assignment
// https://codeforces.com/contest/2135/problem/C

/*
C. By the Assignment
Algorithms/Techniques: 
  - Finding bridges in an undirected graph using Tarjan's algorithm
  - DFS traversal to determine connected components and their coloring
  - XOR-based path value consistency check for balanced graphs
  - Modular arithmetic and combinatorics for counting valid assignments

Time Complexity: O(n + m) per test case, where n is number of vertices and m is number of edges.
Space Complexity: O(n + m), used for adjacency list, DFS recursion stack, bridge tracking, etc.

*/

#include <algorithm>
#include <iostream>
#include <set>

#define ll long long
using namespace std;
const int N = 2e5 + 50, M = 4e5 + 50;
const ll mod = 998244353;
int n, m, v, head[N], cnt = 1, dfn[N], low[N], a[N], c[N];
set<int> s;
bool bridge[M << 1], flag;
struct E {
  int next, to;
} e[M << 1];

// DFS to find bridges in the graph using Tarjan's algorithm
inline void dfs(int now, int from) {
  dfn[now] = low[now] = ++cnt;
  for (int i = head[now]; i; i = e[i].next) {
    if (((i ^ 1) == from)) // Skip parent edge
      continue;
    if (!dfn[e[i].to]) {   // If not visited
      dfs(e[i].to, i);
      low[now] = min(low[now], low[e[i].to]);
      if (low[e[i].to] > dfn[now]) {  // Bridge found
        bridge[i] = 1, bridge[i ^ 1] = 1; // Mark both directions as bridge
      }
    } else
      low[now] = min(low[now], dfn[e[i].to]);  // Back edge update
  }
}

// DFS to process component and count assignments
inline void dfs1(int now) {
  if (a[now] != -1)
    s.insert(a[now]);
  for (int i = head[now]; i; i = e[i].next) {
    if (bridge[i])
      continue; // Skip bridge edges as they divide components
    if (c[e[i].to] == 0) { // If not visited in this component
      c[e[i].to] = (c[now] ^ 1); // Color it differently
      dfs1(e[i].to);
    } else if (c[e[i].to] == c[now]) // If same color, conflict found
      flag = 1;
  }
}

// Add edge to adjacency list
inline void add(int x, int y) {
  e[++cnt] = (E){head[x], y};
  head[x] = cnt;
  bridge[cnt] = 0;  // Initialize bridge flag false
}

// Main solution function
inline void solve() {
  cnt = 1;
  cin >> n >> m >> v;
  for (int i = 1; i <= n; i++)
    cin >> a[i], head[i] = 0, dfn[i] = 0, low[i] = 0, c[i] = 0;
  for (int i = 1; i <= m; i++) {
    int u, v_edge;
    cin >> u >> v_edge;
    add(u, v_edge);
    add(v_edge, u);
  }
  cnt = 0;
  dfs(1, 0); // Start bridge detection from node 1
  ll ans = 1;
  for (int i = 1; i <= n; i++) {
    if (c[i] == 0) {  // If not assigned to any component yet
      c[i] = 2;       // Assign starting color (any value other than 0)
      s.clear();      // Clear set for new component
      flag = 0;
      dfs1(i);
      if (s.size() > 1)
        ans = 0;  // Multiple conflicting values impossible to satisfy
      if (s.size() == 1 && flag && *s.begin())
        ans = 0;  // Conflicting XOR paths when a fixed value exists
      if (!flag && s.size() == 0)
        ans = ans * v % mod; // No fixed node in component, choose any assignment
    }
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/