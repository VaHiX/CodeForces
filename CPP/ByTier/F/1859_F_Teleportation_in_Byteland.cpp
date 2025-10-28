// Problem: CF 1859 F - Teleportation in Byteland
// https://codeforces.com/contest/1859/problem/F

/*
Algorithm: Centroid Decomposition with DP on Trees
Time Complexity: O(n * log W * log n + q * log W)
Space Complexity: O(n * log W)

This solution uses centroid decomposition to handle queries on a tree.
For each centroid, it calculates the minimum time to reach any node from the centroid
with different skill levels. The key insight is to precompute the optimal paths
and skill upgrades to minimize travel time.
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
const int MAXN = 1e5 + 4, LOGW = 21; // LOGW = 21 is enough for w up to 1e6
const ll inf = 1e18 + 100;
bool us[MAXN]; // visited array for centroid decomposition
char qp[MAXN]; // binary string indicating if a city has a driving course
int subtree_size[MAXN];
vector<pair<int, int>> g[MAXN]; // adjacency list with weights
int branch[MAXN]; // used to group children of centroid
ll fastest[MAXN][LOGW], bring_talent[MAXN][LOGW], with_talent[MAXN][LOGW]; // DP arrays
ll answers[MAXN];
ll qualification_cost; // cost of one driving course
struct query_t {
  int a, b, id;
};
void init(int n) {
  fill(us, us + n, false);
  for (int i = 0; i < n; ++i) {
    g[i].clear();
  }
}
void get_sizes(int v, int p) {
  subtree_size[v] = 1;
  for (auto [u, _] : g[v]) {
    if (!us[u] && u != p) {
      get_sizes(u, v);
      subtree_size[v] += subtree_size[u];
    }
  }
}
int get_centroid(int v, int p, int n) {
  for (auto [u, _] : g[v]) {
    if (!us[u] && u != p && subtree_size[u] * 2 > n) {
      return get_centroid(u, v, n);
    }
  }
  return v;
}
inline int get_cost(int w, int i) { return (w - 1 >> i) + 1; } // Calculates cost with skill level 2^i
void calc_fair_dist(int v, int p) {
  bring_talent[v][0] = fastest[v][0] = with_talent[v][0]; // Initialize base case
  for (int i = 1; i < LOGW; ++i) {
    bring_talent[v][i] =
        qp[v] == '1' ? with_talent[v][i] + i * qualification_cost : inf;
    fastest[v][i] =
        qp[v] == '1' ? with_talent[v][0] + i * qualification_cost : inf;
  }
  for (auto [u, w] : g[v]) {
    if (u == p || us[u]) {
      continue;
    }
    for (int i = 0; i < LOGW; ++i) {
      with_talent[u][i] = with_talent[v][i] + get_cost(w, i); // Propagate with_talent from parent
    }
    calc_fair_dist(u, v);
    for (int i = 0; i < LOGW; ++i) {
      bring_talent[v][i] = min(bring_talent[u][i] + w, bring_talent[v][i]); // Update bring_talent
      fastest[v][i] = min(fastest[v][i], fastest[u][i] + get_cost(w, i)); // Update fastest
    }
  }
}
void recalc_dist(int v, int p) {
  for (auto [u, w] : g[v]) {
    if (u == p || us[u]) {
      continue;
    }
    for (int i = 0; i < LOGW; ++i) {
      bring_talent[u][i] = min(bring_talent[u][i], bring_talent[v][i] + w);
      fastest[u][i] = min(fastest[u][i], fastest[v][i] + get_cost(w, i));
    }
    if (v != p) {
      branch[u] = branch[v];
    }
    recalc_dist(u, v);
  }
}
void answer_queries(int v, vector<query_t> &qs) {
  get_sizes(v, v);
  int ctd = get_centroid(v, v, subtree_size[v]);
  for (int i = 0; i < LOGW; ++i) {
    bring_talent[ctd][i] = with_talent[ctd][i] = fastest[ctd][i] = 0;
  }
  calc_fair_dist(ctd, ctd);
  for (int i = 0; i < g[ctd].size(); ++i) {
    branch[g[ctd][i].first] = i;
  }
  recalc_dist(ctd, ctd);
  branch[ctd] = -1;
  vector<vector<query_t>> qq(g[ctd].size());
  for (auto &q : qs) {
    for (int i = 0; i < LOGW; ++i) {
      answers[q.id] = min({answers[q.id], with_talent[q.a][0] + fastest[q.b][i],
                           bring_talent[q.a][i] + with_talent[q.b][i]});
    }
    if (branch[q.a] == branch[q.b]) {
      qq[branch[q.a]].push_back(q);
    }
  }
  us[ctd] = true;
  for (int i = 0; i < g[ctd].size(); ++i) {
    if (us[g[ctd][i].first] || qq[i].empty()) {
      continue;
    }
    answer_queries(g[ctd][i].first, qq[i]);
  }
}
void solve(istream &in, ostream &out) {
  int n;
  in >> n >> qualification_cost;
  init(n);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    in >> u >> v >> w;
    --u, --v;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }
  for (int i = 0; i < n; ++i) {
    cin >> qp[i];
  }
  int q;
  in >> q;
  vector<query_t> qs;
  fill(answers, answers + q, inf);
  for (int i = 0; i < q; ++i) {
    int a, b;
    in >> a >> b;
    --a, --b;
    if (a == b) {
      answers[i] = 0;
    } else {
      qs.push_back({a, b, i});
    }
  }
  answer_queries(0, qs);
  for (int i = 0; i < q; ++i) {
    out << answers[i] << '\n';
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int tests = 1;
  cin >> tests;
  while (tests--) {
    solve(cin, cout);
  }
}


// https://github.com/VaHiX/CodeForces/