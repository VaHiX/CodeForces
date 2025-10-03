/*
 * Problem URL : https://codeforces.com/problemset/problem/2059/D
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
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
  vector<bool> com(N + 1, false);
  FOR1(i, N) {
    unordered_set<int> s;
    for (int nb : g1[i])
      s.insert(nb);
    for (int nb : g2[i]) {
      if (s.count(nb)) {
        com[i] = true;
        break;
      }
    }
  }
  const int INF = 1000000000;
  vector<vector<int>> d(N + 1, vector<int>(N + 1, INF));
  priority_queue<Node, vector<Node>, greater<Node>> pq;
  d[st1][st2] = 0;
  pq.push({st1, st2, 0});
  int ans = -1;
  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();
    int a = cur.u, b = cur.v, curd = cur.cost;
    if (curd != d[a][b])
      continue;
    if (a == b && com[a]) {
      ans = curd;
      break;
    }
    for (int nxt1 : g1[a])
      for (int nxt2 : g2[b]) {
        int nd = curd + abs(nxt1 - nxt2);
        if (nd < d[nxt1][nxt2]) {
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
