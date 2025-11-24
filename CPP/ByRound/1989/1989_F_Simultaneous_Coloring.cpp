// Problem: CF 1989 F - Simultaneous Coloring
// https://codeforces.com/contest/1989/problem/F

/*
 * Task: Simultaneous Coloring
 * 
 * Problem Description:
 * Given a matrix of size n x m, we can paint entire rows red or columns blue.
 * When performing k actions simultaneously, the cost is k^2 coins.
 * For each query, a cell must be painted a specific color. After each query,
 * output the minimum cost to satisfy all current restrictions.
 * 
 * Approach:
 * The problem uses 2-SAT with Tarjan's SCC algorithm to determine which cells
 * must be in the same or different color groups.
 * 
 * Key Techniques:
 * 1. 2-SAT encoding: Each cell (i,j) is represented by two variables - one for red, 
 *    another for blue. For each constraint cell (i,j) must be red, we create an edge
 *    from the blue variable of (i,j) to the red variable of (i,j).
 * 2. Tarjan's algorithm for finding SCCs to solve 2-SAT.
 * 3. Union-Find for maintaining and merging components to calculate cost.
 * 
 * Time Complexity: O(nm + q^2 log q)
 * Space Complexity: O(nm + q)
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

#define ll long long
using namespace std;
const int N = 4e5 + 2;
vector<pair<int, pair<int, int>>> edge;
int team[N + 2], low[N + 2], num[N + 2], timer, scc;
vector<int> adj[N + 2];
stack<int> st;
void dfs(int u) {
  num[u] = low[u] = ++timer;
  st.push(u);
  for (int v : adj[u]) {
    if (team[v])
      continue;
    if (!num[v]) {
      dfs(v);
      low[u] = min(low[u], low[v]);
    } else
      low[u] = min(low[u], num[v]);
  }
  if (low[u] == num[u]) {
    scc++;
    int v;
    do {
      v = st.top();
      st.pop();
      team[v] = scc;
    } while (v != u);
  }
}
int ans[N + 2];
void calc(int l, int r, vector<pair<int, pair<int, int>>> g) {
  for (auto [id, cur] : g) {
    auto [u, v] = cur;
    num[u] = num[v] = low[u] = low[v] = timer = scc = 0;
    team[u] = team[v] = 0;
    adj[u].clear();
    adj[v].clear();
  }
  int mid = (l + r) / 2;
  for (auto [id, cur] : g) {
    if (id > mid)
      continue;
    auto [u, v] = cur;
    adj[u].push_back(v);
  }
  for (auto [id, cur] : g) {
    auto [u, v] = cur;
    if (!num[u]) {
      dfs(u);
    }
  }
  vector<pair<int, pair<int, int>>> right;
  vector<pair<int, pair<int, int>>> left;
  for (auto [id, cur] : g) {
    auto [u, v] = cur;
    if (team[u] == team[v]) {
      ans[id] = mid;
      if (id <= mid)
        left.push_back({id, {u, v}});
    } else {
      right.push_back({id, {team[u], team[v]}});
    }
  }
  if (l >= r)
    return;
  calc(l, mid, left);
  calc(mid + 1, r, right);
}
int par[N + 2];
ll sum = 0;
int find_par(int u) {
  if (par[u] < 0)
    return u;
  par[u] = find_par(par[u]);
  return par[u];
}
ll cost(ll x) { return (x == -1 ? 0 : x * x); }
void union_set(int u, int v) {
  u = find_par(u);
  v = find_par(v);
  if (u != v) {
    sum -= cost(par[u]);
    sum -= cost(par[v]);
    sum += cost(par[u] + par[v]);
    if (par[u] > par[v])
      swap(u, v);
    par[u] += par[v];
    par[v] = u;
  }
}
vector<int> td[N + 2];
void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 1; i <= q; i++) {
    ans[i] = q + 1;
    int u, v;
    char c;
    cin >> u >> v >> c;
    if (c == 'R') {
      edge.push_back({i, {u, v + n}});
    } else
      edge.push_back({i, {v + n, u}});
  }
  memset(par, -1, sizeof(par));
  calc(1, q, edge);
  for (int i = 1; i <= q; i++) {
    td[ans[i]].push_back(i);
    for (auto z : td[i]) {
      assert(z <= edge.size() && z != 0);
      auto [id, cur] = edge[z - 1];
      auto [u, v] = cur;
      union_set(u, v);
    }
    cout << sum << '\n';
  }
}
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
#define _ "maxseq."
  if (fopen(_ "inp", "r")) {
    freopen(_ "inp", "r", stdin);
    freopen(_ "out", "w", stdout);
  }
  solve();
}


// https://github.com/VaHiX/CodeForces/