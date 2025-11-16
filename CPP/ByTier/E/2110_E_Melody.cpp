// Problem: CF 2110 E - Melody
// https://codeforces.com/contest/2110/problem/E

/*
E. Melody
Algorithms/Techniques: Hierholzer's algorithm for Eulerian path, coordinate compression, graph construction

Time Complexity: O(n log n + m) where m is the number of edges in graph (i.e., n)
Space Complexity: O(n)

This code constructs a graph from sound pairs such that:
- Each sound has a unique volume and pitch.
- A valid sequence of sounds must have consecutive sounds differ only in volume OR only in pitch.
- The problem reduces to finding an Eulerian path in this constructed graph.
- It uses coordinate compression to reduce large coordinate values into manageable indices,
  then checks for Eulerian Path existence using Hierholzer's algorithm.

*/

#include <algorithm>
#include <iostream>

using namespace std;
int t, m, u[200005], v[200005], head[400005], cnt = 1, deg[400005], ans[200005];
bool vis[400005];
struct edge {
  int v, nxt;
} e[400005];

// Add edge to adjacency list
void add(int u, int v) {
  cnt++, e[cnt].v = v, e[cnt].nxt = head[u], head[u] = cnt;
}

// Coordinate compression function to map large numbers to smaller indices
int rebuild(int n, int a[]) {
  int temp[n + 5], cnt;
  for (int i = 1; i <= n; i++)
    temp[i] = a[i];
  sort(temp + 1, temp + n + 1), cnt = unique(temp + 1, temp + n + 1) - temp - 1;
  for (int i = 1; i <= n; i++)
    a[i] = lower_bound(temp + 1, temp + cnt + 1, a[i]) - temp;
  return cnt;
}

// DFS to perform Hierholzer's algorithm, building Eulerian path
void dfs(int pos, edge e[], int head[], int ans[], int &cnt) {
  for (int i = head[pos]; i; i = head[pos]) {
    head[pos] = e[i].nxt;
    if (!vis[i])
      vis[i] = vis[i ^ 1] = 1, dfs(e[i].v, e, head, ans, cnt),
      ans[++cnt] = i / 2;
  }
}

// Check and find Eulerian path in the graph
bool hierholzer(int n, int m, edge e[], int head[], int ans[]) {
  int s = 0, cnt = 0;
  for (int i = 1; i <= n; i++)
    deg[i] = 0;
  for (int i = 2; i <= 2 * m + 1; i++)
    vis[i] = 0, deg[e[i].v]++;
  for (int i = 1, num = 0; i <= n; i++) {
    if (deg[i] & 1) {
      if (++num > 2)
        return 0;
      s = i;
    }
  }
  if (!s)
    for (int i = 1; i <= n; i++)
      if (deg[i])
        s = i;
  dfs(s, e, head, ans, cnt);
  if (cnt != m)
    return 0;
  return 1;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cin >> t;
  while (t--) {
    cin >> m;
    for (int i = 1; i <= m; i++)
      cin >> u[i] >> v[i];
    int cnt1 = rebuild(m, u), cnt2 = rebuild(m, v);
    for (int i = 1; i <= m; i++)
      add(u[i], cnt1 + v[i]), add(cnt1 + v[i], u[i]);
    if (hierholzer(cnt1 + cnt2, m, e, head, ans)) {
      cout << "Yes\n";
      for (int i = 1; i <= m; i++)
        cout << ans[i] << (i == m ? '\n' : ' ');
    } else
      cout << "No\n";
    for (int i = 1; i <= cnt1 + cnt2; i++)
      head[i] = 0;
    cnt = 1;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/