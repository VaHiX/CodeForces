// Problem: CF 2137 G - Cry Me a River
// https://codeforces.com/contest/2137/problem/G

/*
G. Cry Me a River
Algorithms/Techniques: Topological sorting, BFS-based game simulation with memoization on states.
Time Complexity: O(n + m + q)
Space Complexity: O(n + m)

This code handles a directed acyclic graph (DAG) problem involving a two-player game between Cry and River.
Each node is initially blue. For queries of type 1, we color a node red.
For queries of type 2, we determine if Cry wins when the game starts from a given node under optimal play.

The solution uses:
- Reverse topological order processing via BFS to compute winning conditions.
- State tracking using a 2D array f[i][0] and f[i][1], representing whether a node leads to win for Cry (f[i][0]) or River (f[i][1]).
- Special handling of game states where players can immediately win or lose based on node out-degree and color.
*/

#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;
const int N = 4e5 + 5;
int head[N], num, n, m, k, in[N], deg[N];
struct edge {
  int to, next;
} g[N * 2];
void addd(int u, int v) {
  num++;
  g[num].to = v;
  g[num].next = head[u];
  head[u] = num;
}
bool col[N], ans[N], vis[N], f[N][2];
struct node {
  int opt, x;
} a[N];
queue<int> q;
void work(int x) {
  col[x] = 1;
  if (f[x][0])
    q.push(x);
  if (f[x][1])
    q.push(x + n); // Pushing x+n to distinguish in BFS
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (u > n) { // Handling nodes for "River wins" condition
      u -= n;
      for (int i = head[u]; i; i = g[i].next) {
        int v = g[i].to;
        if (f[v][0] == 0) { // If Cry can win from this node yet not set
          f[v][0] = 1;
          if (col[v])
            q.push(v); // If this node is colored, push it to queue for further propagation
        }
      }
    } else { // Handling nodes for "Cry wins" condition
      for (int i = head[u]; i; i = g[i].next) {
        int v = g[i].to;
        in[v]--;
        if (in[v] == 0) {
          f[v][1] = 1; // Marking that River can win from 'v'
          if (col[v])
            q.push(v + n); // If colored, push related to river queue
        }
      }
    }
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int q;
    cin >> n >> m >> q;
    int u, v;
    num = 0;
    for (int i = 1; i <= n; i++)
      head[i] = f[i][0] = f[i][1] = in[i] = deg[i] = col[i] = 0;
    for (int i = 1; i <= m; i++) {
      cin >> u >> v;
      addd(v, u); // Edge from v to u (reverse direction)
      in[u]++;
      deg[u]++;
    }
    for (int i = 1; i <= n; i++)
      if (!in[i]) // Nodes with no incoming edges are terminal
        f[i][0] = f[i][1] = 1;
    for (int i = 1; i <= q; i++) {
      cin >> a[i].opt >> a[i].x;
      if (a[i].opt == 1)
        col[a[i].x] = 1; // Mark node as red (colored)
    }
    for (int i = 1; i <= n; i++) {
      if (!col[i])
        q++, a[q].opt = 1, a[q].x = i; // Add uncolored nodes to query list
      col[i] = 0;
    }
    for (int i = q; i >= 1; i--) {
      if (a[i].opt == 1) {
        work(a[i].x); // Process coloring updates
      } else {
        ans[i] = (col[a[i].x] & f[a[i].x][0]); // Query result based on current state
      }
    }
    for (int i = 1; i <= q; i++)
      if (a[i].opt == 2)
        cout << (ans[i] ? "YES\n" : "NO\n"); // Output results of type 2 queries
  }
}


// https://github.com/VaHiX/codeForces/