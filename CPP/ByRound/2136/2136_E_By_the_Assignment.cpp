// Problem: CF 2136 E - By the Assignment
// https://codeforces.com/contest/2136/problem/E

/*
E. By the Assignment
time limit per test
4 seconds
memory limit per test
512 megabytes
input
standard input
output
standard output

For an undirected connected graph of n vertices, where the i-th 
vertex has a weight of v_i, we define the value of a simple path l_1, l_2, ..., l_m as v_{l_1} XOR v_{l_2} XOR ... XOR v_{l_m}. We call the graph balanced if and only if:
 For every 1 <= p < q <= n, all simple paths from p to q have the same value.

Aquawave has given you an undirected connected graph of n vertices and m edges, and the i-th vertex in the graph has a weight of a_i. However, some of the weights are missing, represented by -1.
Aquawave wants to assign an integer weight between 0 and V-1 to each vertex with a_i=-1, so that the graph will be balanced.

Algorithms/Techniques:
- Bridge detection using DFS
- Bipartite check on biconnected components
- XOR properties in graphs

Time Complexity: O(n + m) per test case
Space Complexity: O(n + m)
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
inline void dfs(int now, int from) {
  dfn[now] = low[now] = ++cnt;
  for (int i = head[now]; i; i = e[i].next) {
    if (((i ^ 1) == from)) // Skip the reverse edge
      continue;
    if (!dfn[e[i].to]) { // If not visited
      dfs(e[i].to, i);
      low[now] = min(low[now], low[e[i].to]);
      if (low[e[i].to] > dfn[now]) {
        bridge[i] = 1, bridge[i ^ 1] = 1; // Mark this edge as a bridge
      }
    } else
      low[now] = min(low[now], dfn[e[i].to]); // Back edge found
  }
}
inline void dfs1(int now) {
  if (a[now] != -1)
    s.insert(a[now]);
  for (int i = head[now]; i; i = e[i].next) {
    if (bridge[i]) // Skip bridges in this traversal
      continue;
    if (c[e[i].to] == 0) { // Not yet colored
      c[e[i].to] = (c[now] ^ 1); // Alternate colors for bipartite check
      dfs1(e[i].to);
    } else if (c[e[i].to] == c[now]) // Same color means odd cycle - not bipartite
      flag = 1;
  }
}
inline void add(int x, int y) {
  e[++cnt] = (E){head[x], y};
  head[x] = cnt;
  bridge[cnt] = 0; // Initialize bridge flag
}
inline void solve() {
  cnt = 1;
  cin >> n >> m >> v;
  for (int i = 1; i <= n; i++)
    cin >> a[i], head[i] = 0, dfn[i] = 0, low[i] = 0, c[i] = 0;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    add(u, v);
    add(v, u);
  }
  cnt = 0;
  dfs(1, 0); // Find bridges
  ll ans = 1;
  for (int i = 1; i <= n; i++) {
    if (c[i] == 0) { // Unvisited component
      c[i] = 2;
      s.clear();
      flag = 0;
      dfs1(i); // Traverse without bridges to check bipartite property
      if (s.size() > 1)
        ans = 0; // Multiple fixed values are impossible
      if (s.size() == 1 && flag && *s.begin()) // Flag set and value is non-zero
        ans = 0; // Conflict
      if (!flag && s.size() == 0) // No constraint from current component
        ans = ans * v % mod; // Choose any value for missing vertex
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