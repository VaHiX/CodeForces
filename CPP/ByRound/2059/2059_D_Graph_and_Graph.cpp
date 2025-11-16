// Problem: CF 2059 D - Graph and Graph
// https://codeforces.com/contest/2059/problem/D

/*
D. Graph and Graph
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm: Dijkstra's shortest path on a state space (u, v) where u is node in first graph and v is node in second graph.
We compute the minimum cost to reach a state where both tokens are at same vertex that is also a common vertex (i.e., exists in both graphs).

Time Complexity: O((V + E1 + E2) * log(V^2)) = O((V + E1 + E2) * log V)
Space Complexity: O(V^2 + E1 + E2)

The problem models a two-token game on two graphs, where at each step,
the tokens move to adjacent nodes in their respective graphs and the cost is |u1 - u2|.
We want to find the minimum total cost to reach a state where both tokens are at the same vertex
that exists in both graphs (i.e., has common neighbors in both).
This is modeled as a weighted directed graph with states defined by pairs of nodes from each graph.
*/
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;
#define FOR(i, n) for (int i = 0; i < (n); i++)
#define FOR1(i, n) for (int i = 1; i <= (n); i++)
#define ll long long
struct Node {
  int u, v, cost;
  bool operator>(const Node &other) const { return cost > other.cost; }
};
void solve() {
  int N, st1, st2;
  cin >> N >> st1 >> st2;
  int E1;
  cin >> E1;
  vector<vector<int>> g1(N + 1), g2(N + 1);
  FOR(i, E1) {
    int x, y;
    cin >> x >> y;
    g1[x].push_back(y);
    g1[y].push_back(x);
  }
  int E2;
  cin >> E2;
  FOR(i, E2) {
    int x, y;
    cin >> x >> y;
    g2[x].push_back(y);
    g2[y].push_back(x);
  }
  vector<bool> com(N + 1, false); // Mark nodes common to both graphs
  FOR1(i, N) {
    unordered_set<int> s;
    for (int nb : g1[i])
      s.insert(nb);
    for (int nb : g2[i]) {
      if (s.count(nb)) {  // If neighbor exists in both graphs
        com[i] = true;
        break;
      }
    }
  }
  const int INF = 1000000000;
  vector<vector<int>> d(N + 1, vector<int>(N + 1, INF)); // d[a][b] = min cost to reach state (a,b)
  priority_queue<Node, vector<Node>, greater<Node>> pq;  // Min-heap for Dijkstra
  d[st1][st2] = 0;
  pq.push({st1, st2, 0});
  int ans = -1;
  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();
    int a = cur.u, b = cur.v, curd = cur.cost;
    if (curd != d[a][b]) // Skip outdated entries
      continue;
    if (a == b && com[a]) {  // If both tokens are at same node which is common in both
      ans = curd;
      break;
    }
    for (int nxt1 : g1[a])
      for (int nxt2 : g2[b]) {
        int nd = curd + abs(nxt1 - nxt2);
        if (nd < d[nxt1][nxt2]) {  // Relax edge and push to heap
          d[nxt1][nxt2] = nd;
          pq.push({nxt1, nxt2, nd});
        }
      }
  }
  cout << ans << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/