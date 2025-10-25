// Problem: CF 2132 F - Rada and the Chamomile Valley
// https://codeforces.com/contest/2132/problem/F

// Problem: F. Rada and the Chamomile Valley
// Time Complexity: O(n + m + q) per test case
// Space Complexity: O(n + m)
// Algorithms/Techniques:
// - Finding bridges in an undirected graph using DFS (Tarjan's algorithm)
// - BFS to compute distances from source
// - Using bridge information and BFS distances to assign nearest lane index for each vertex

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

#define pii pair<int, int>
#define f first
#define s second
using namespace std;
const int N = 2e5 + 50, INF = 0x3f3f3f3f;
int n, m, head[N], cnt, dfn[N], low[N], idx, last[N];
bool tag[N << 1]; // tag[i] = true if edge i is a bridge
pii dis[N];       // dis[i] stores {distance to nearest bridge lane, index of that lane}
struct E {
  int next, to;
} e[N << 1];
inline void add(int x, int y) {
  e[++cnt] = (E){head[x], y}; // Add edge from x to y
  head[x] = cnt;
  tag[cnt] = 0; // Initially mark as not a bridge
}
inline void dfs(int now, int id) { // Tarjan's algorithm to find bridges
  dfn[now] = low[now] = ++idx; // Set discovery time and low value of node
  for (int i = head[now]; i; i = e[i].next) {
    if (((i ^ 1) == id)) // Skip parent edge in undirected graph
      continue;
    if (!dfn[e[i].to]) { // If not visited
      dfs(e[i].to, i);   // Recursive DFS
      low[now] = min(low[now], low[e[i].to]); // Update low value
      if (low[e[i].to] > dfn[now])  // Bridge found
        tag[i] = 1, tag[i ^ 1] = 1;
    } else // Back edge case
      low[now] = min(low[now], dfn[e[i].to]); // Update low value using back edge
  }
}
inline void solve() {
  cin >> n >> m;
  cnt = 1;
  idx = 0;
  for (int i = 1; i <= n; i++)
    head[i] = 0, dfn[i] = 0, low[i] = 0, dis[i].f = INF, dis[i].s = -1,
    last[i] = -1; // Initialize all arrays
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    add(u, v); // Add edges in both directions
    add(v, u);
  }
  dfs(1, 0); // Find bridges starting from node 1
  queue<int> q;
  q.push(1); // BFS to build tree (spanning tree)
  last[1] = 0; // Root node has no parent edge
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    for (int i = head[now]; i; i = e[i].next) {
      if (last[e[i].to] != -1) // Already visited
        continue;
      last[e[i].to] = i; // Record parent edge
      q.push(e[i].to);   // Visit node
    }
  }
  int now = n;
  while (now != 1) { // Backtrack from node n to root to check bridges on path
    int id = last[now];
    if (tag[id]) { // If current edge is a bridge, update distances
      dis[now] = min(dis[now], {0, id / 2});
      dis[e[id ^ 1].to] = min(dis[e[id ^ 1].to], {0, id / 2});
    }
    now = e[id ^ 1].to; // Move to parent
  }
  for (int i = 1; i <= n; i++) // Push nodes with bridge distance 0 into queue
    if (dis[i].f == 0)
      q.push(i);
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    auto [step, id] = dis[now]; // Distance and lane index of current node
    for (int i = head[now]; i; i = e[i].next) {
      if (dis[e[i].to] > make_pair(step + 1, id)) { // Relax edges with better distance
        dis[e[i].to] = {step + 1, id};
        q.push(e[i].to);
      }
    }
  }
  int Q;
  cin >> Q;
  while (Q--) {
    int c;
    cin >> c;
    cout << dis[c].s << ' '; // Output nearest bridge lane index
  }
  cout << '\n';
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