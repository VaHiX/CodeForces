// Problem: CF 2128 F - Strict Triangle
// https://codeforces.com/contest/2128/problem/F

/*
F. Strict Triangle
Algorithms/Techniques: Dijkstra's algorithm, graph traversal with priority queues

Time Complexity: O((n + m) * log n) per test case
Space Complexity: O(n + m)

This problem determines whether there exists an assignment of edge weights such that 
the shortest path from node 1 to node n does NOT equal the sum of shortest paths 
from 1 to k and k to n. We use two Dijkstra runs:
1. First to compute shortest distances from k to all nodes (using upper bounds r[i]).
2. Second to compute a "critical" value dp[v] which represents the minimum cost needed 
   to ensure that dist(1,v) > dist(1,k) + dist(k,v).
The key insight is that we want to make the triangle inequality strict, so we check 
if there's any assignment that allows strict inequality.

*/
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define ll long long
#define sz(x) ((int)x.size())
using namespace std;
using pii = pair<ll, int>;
using tup = tuple<int, int, int>;
const int N = 200005;
int n, m, k, l[N], r[N];
vector<pii> G[N];
void solve() {
  scanf("%d%d%d", &n, &m, &k);
  rep(i, 1, n) G[i].clear();
  rep(i, 1, m) {
    int x, y;
    scanf("%d%d%d%d", &x, &y, &l[i], &r[i]);
    G[x].emplace_back(y, i), G[y].emplace_back(x, i);
  }
  vector<ll> dis(n + 1); // distances from node k to all nodes
  vector<int> vs(n + 1); // visited array
  priority_queue<pii, vector<pii>, greater<pii>> q; // min-heap for Dijkstra
  rep(i, 1, n) dis[i] = 1e18;
  dis[k] = 0;
  q.emplace(0, k);
  while (!q.empty()) {
    int u = q.top().second;
    q.pop();
    if (vs[u])
      continue;
    vs[u] = 1;
    for (auto v : G[u])
      if (dis[v.first] > dis[u] + r[v.second]) {
        dis[v.first] = dis[u] + r[v.second];
        q.emplace(dis[v.first], v.first);
      }
  }
  rep(i, 1, n) vs[i] = 0;
  vector<ll> dp(n + 1); // critical values for maintaining strict inequality
  rep(i, 2, n) dp[i] = 1e18;
  dp[1] = -1e18;
  q.emplace(-1e18, 1);
  while (!q.empty()) {
    int u = q.top().second;
    q.pop();
    if (vs[u])
      continue;
    vs[u] = 1;
    if (dis[u] <= dp[u])
      continue;
    for (auto v : G[u])
      if (v.first != k) { // avoid going back to k to prevent cycles
        ll nv = max(dp[u] + l[v.second], l[v.second] - dis[u]);
        if (nv < dp[v.first])
          dp[v.first] = nv, q.emplace(dp[v.first], v.first);
      }
  }
  if (dis[n] > dp[n])
    puts("YES");
  else
    puts("NO");
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    solve();
}


// https://github.com/VaHiX/codeForces/