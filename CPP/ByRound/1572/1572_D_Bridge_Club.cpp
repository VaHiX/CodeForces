// Problem: CF 1572 D - Bridge Club
// https://codeforces.com/contest/1572/problem/D

/*
D. Bridge Club
Algorithms/Techniques: Minimum Cost Maximum Flow (MCMF)
Time Complexity: O((V + E) * log(V) * F) where V = number of nodes, E = number of edges, F = max flow
Space Complexity: O(V + E)

The problem models a bipartite matching with a cost function.
We construct a flow network:
- Source s connects to each player (with capacity 1 and cost 0)
- Each player u connects to player v with edge if they agree on at least n-2 topics (i.e., disagree on at most 2), with capacity 1 and negative cost equal to sum of their values.
- Each player v connects to sink t (with capacity 1 and cost 0)
We run MCMF with capacity k to find maximum earnings.

The algorithm:
1. For all pairs of players, we determine how many topics they agree on.
2. For those who agree on at least n - 2 topics, we add an edge in the flow graph with negative cost (revenue).
3. We then use min-cost max-flow to compute the optimal assignment.
*/

#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;
const int N = (1 << 20);
int n, a[N], k, vis[N], s, S, T, t, id[N], cnt, ans;
struct dp {
  int u, v, w;
  inline bool operator<(const dp &x) const { return w > x.w; }
};
int head[N], tot = 1, cur[N], last[N];
int dis[N], flow[N], pre[N];
struct node {
  int next, to, flow, w;
} edge[N << 1];
void add(int u, int v, int flow, int w) {
  tot++;
  edge[tot].next = head[u];
  edge[tot].to = v;
  edge[tot].flow = flow;
  edge[tot].w = w;
  head[u] = tot;
}
void addedge(int u, int v, int flow, int w) {
  add(u, v, flow, w), add(v, u, 0, -w);
}
inline bool spfa() {
  queue<int> q;
  for (int i = s; i <= t; i++)
    dis[i] = 2e9, flow[i] = 2e9, vis[i] = 0;
  q.push(s);
  vis[s] = 1, dis[s] = 0, pre[t] = -1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = 0;
    for (int i = head[u]; i; i = edge[i].next) {
      int v = edge[i].to;
      if (edge[i].flow > 0 && dis[v] > dis[u] + edge[i].w) {
        dis[v] = dis[u] + edge[i].w;
        pre[v] = u;
        last[v] = i;
        flow[v] = min(flow[u], edge[i].flow);
        if (!vis[v]) {
          vis[v] = 1;
          q.push(v);
        }
      }
    }
  }
  if (pre[t] != -1)
    return 1;
  return 0;
}
void dfs() {
  while (spfa()) {
    int u = t;
    ans += flow[t] * dis[t];
    while (u != s) {
      edge[last[u]].flow -= flow[t];
      edge[last[u] ^ 1].flow += flow[t];
      u = pre[u];
    }
  }
}
priority_queue<dp> q;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  s = 0, t = 2e4 + 5;
  S = t - 1;
  addedge(s, S, k, 0); // Source connects to super source with capacity k

  for (int i = 0; i < (1 << n); i++)
    cin >> a[i];
  
  int mn = 1e9, sz = 0, sum = 2 * n * k; // Threshold to keep largest cost edges
  for (int i = 0; i < (1 << n); i++) {
    int num = __builtin_popcount(i);
    if (num & 1)
      continue;
    for (int j = 0; j < n; j++) {
      int k = (i ^ (1 << j)), val = a[i] + a[k]; // XOR flips bit j, we check agreement
      if (sz < sum)
        q.push({i, k, val}), sz++, mn = min(mn, val);
      else {
        if (val > mn)
          q.pop(), q.push({i, k, val}), mn = q.top().w;
      }
    }
  }
  
  while (!q.empty()) {
    int u = q.top().u, v = q.top().v, w = q.top().w;
    q.pop();
    // Map original nodes to internal node ids for flow graph
    if (!id[u])
      id[u] = ++cnt, addedge(S, id[u], 1, 0);
    if (!id[v])
      id[v] = ++cnt, addedge(id[v], t, 1, 0);
    // Add edge between u and v in flow network with negative cost (profit)
    addedge(id[u], id[v], 1, -w);
  }
  
  dfs();
  cout << -1 * ans; // Negative sign because we store negative costs for profit maximization
  return 0;
}


// https://github.com/VaHiX/codeForces/