// Problem: CF 2047 F - For the Emperor!
// https://codeforces.com/contest/2047/problem/F

/*
Algorithm: This solution uses a combination of Strongly Connected Components (SCC) and Minimum Cost Maximum Flow (MCMF) to solve the problem.
- First, we compress the graph into SCCs using Tarjan's algorithm.
- Then, we model the problem as a minimum cost flow network:
  * Create a flow network where each SCC is a node.
  * Add edges from source to each SCC with capacity equal to the number of messengers in that SCC.
  * Add edges from each SCC to sink with capacity 1 (to ensure each SCC gets at least one messenger).
  * Add edges between SCCs according to the original graph edges.
  * Run MCMF to find the minimum cost to send one messenger to every SCC.
- Time Complexity: O(V * E * log(V)) where V is the number of nodes and E is the number of edges.
- Space Complexity: O(V + E) for storing the graph and extra data structures.
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;
int n, m, a[201], cmpa[201];
const int INF = 1e9;
set<int> cmpadj[201];
struct SCC {
  vector<vector<int>> adj;
  vector<int> comp, dnum, dlow, active;
  int n, dcnt, ccnt;
  stack<int> s;
  SCC(int n)
      : n(n), dcnt(0), ccnt(0), adj(n), comp(n), dnum(n), dlow(n), active(n) {}
  void tarjan(int u) {
    if (dnum[u])
      return;
    dlow[u] = dnum[u] = ++dcnt;
    active[u] = 1;
    s.push(u);
    for (int v : adj[u]) {
      tarjan(v);
      if (active[v])
        dlow[u] = min(dlow[u], dlow[v]);
    }
    if (dlow[u] == dnum[u]) {
      for (;;) {
        int x = s.top();
        s.pop();
        comp[x] = ccnt;
        active[x] = 0;
        if (x == u)
          break;
      }
      ccnt++;
    }
  }
  void compute() {
    for (int i = 0; i < n; i++)
      tarjan(i);
  }
};
struct MCMF {
  int n, flow = 0, cost = 0;
  vector<vector<int>> adj;
  vector<vector<int>> cap;
  vector<vector<int>> cst;
  vector<int> dst, p, inq;
  MCMF(int n) : n(n), adj(n), cap(n, vector<int>(n)), cst(n, vector<int>(n)){};
  void add_edge(int u, int v, int cap, int c) {
    cst[u][v] = c;
    cst[v][u] = -c;
    this->cap[u][v] = cap;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  bool spfa() {
    dst.assign(n, INF);
    dst[0] = 0;
    inq.assign(n, 0);
    p.assign(n, 0);
    queue<int> q;
    q.push(0);
    while (q.size()) {
      int u = q.front();
      q.pop();
      inq[u] = 0;
      for (int v : adj[u]) {
        if (dst[u] + cst[u][v] < dst[v] && cap[u][v]) {
          p[v] = u;
          dst[v] = dst[u] + cst[u][v];
          if (!inq[v])
            q.push(v);
          inq[v] = 1;
        }
      }
    }
    return dst[1] < INF;
  }
  void solve() {
    while (spfa()) {
      flow++;
      cost += dst[1];
      int v = 1;
      while (v != 0) {
        int u = p[v];
        cap[u][v]--;
        cap[v][u]++;
        v = u;
      }
    }
  }
};
void solve() {
  int n, m;
  cin >> n >> m;
  SCC scc(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0, u, v; i < m; i++) {
    cin >> u >> v;
    scc.adj[u - 1].push_back(v - 1);
  }
  scc.compute();
  fill(cmpa, cmpa + scc.ccnt, 0);
  for (int i = 0; i < scc.ccnt; i++)
    cmpadj[i].clear();
  for (int i = 0; i < n; i++) {
    cmpa[scc.comp[i]] += a[i];
    for (int v : scc.adj[i])
      if (scc.comp[v] != scc.comp[i]) {
        cmpadj[scc.comp[i]].insert(scc.comp[v]);
      }
  }
  MCMF mcmf(scc.ccnt * 3 + 4);
  mcmf.add_edge(3, 2, INF, 0);
  for (int i = 0; i < scc.ccnt; i++) {
    mcmf.add_edge(i * 3 + 4, i * 3 + 5, INF, 0);
    mcmf.add_edge(i * 3 + 4, 1, 1, 0);
    mcmf.add_edge(i * 3 + 5, 3, INF, 0);
    mcmf.add_edge(i * 3 + 6, i * 3 + 4, INF, 1);
    mcmf.add_edge(i * 3 + 6, i * 3 + 5, INF, 0);
    mcmf.add_edge(2, i * 3 + 6, cmpa[i], 0);
    mcmf.add_edge(0, i * 3 + 5, 1, 0);
    for (int v : cmpadj[i]) {
      mcmf.add_edge(i * 3 + 5, v * 3 + 4, INF, 0);
    }
  }
  mcmf.solve();
  if (mcmf.flow == scc.ccnt) {
    cout << mcmf.cost << '\n';
  } else
    cout << "-1\n";
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/