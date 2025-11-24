// Problem: CF 1970 G1 - Min-Fund Prison (Easy)
// https://codeforces.com/contest/1970/problem/G1

/*
==================================================
Problem: G1. Min-Fund Prison (Easy)
Algorithm/Techniques: Graph traversal (DFS, BFS), Tree properties, Optimization
Time Complexity: O(n + m) per test case, where n is number of nodes and m is number of edges
Space Complexity: O(n + m) for adjacency list and auxiliary arrays
==================================================
*/
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;
#define endl "\n"
#define x first
#define y second
typedef pair<long long, long long> PLL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e5 + 10, inf = 0x3f3f3f3f, mod = 1e9 + 7;
int h[N], e[N * 2], ne[N * 2], idx, d[N]; // h: head of adjacency list, e: edge, ne: next pointer, d: subtree size
bool st[N]; // visited array
int n, m, c;
ll res;
void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }
int dfs(int u) {
  st[u] = 1;
  for (int i = h[u]; i != -1; i = ne[i]) {
    int j = e[i];
    if (!st[j])
      d[u] += dfs(j); // accumulate subtree size
  }
  return d[u];
}
void bfs() {
  queue<int> que;
  que.push(1);
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    if (st[u])
      continue;
    st[u] = 1;
    for (int i = h[u]; i != -1; i = ne[i]) {
      int j = e[i];
      if (!st[j]) {
        // Calculate minimum cost of splitting at edge (u, j)
        res = min(res, (ll)d[j] * d[j] + (ll)(n - d[j]) * (n - d[j]));
        que.push(j);
      }
    }
  }
}
void solve() {
  cin >> n >> m >> c;
  res = 1e18;
  idx = 0;
  for (int i = 1; i <= n; i++)
    h[i] = -1, d[i] = 1, st[i] = 0; // Initialize data structures
  while (m--) {
    int a, b;
    cin >> a >> b;
    add(a, b); // Add edge in both directions (undirected graph)
    add(b, a);
  }
  dfs(1); // Compute subtree sizes
  for (int i = 1; i <= n; i++)
    st[i] = 0;
  bfs(); // Try all possible edges to cut the tree into two parts
  cout << res << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/