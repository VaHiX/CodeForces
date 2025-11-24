// Problem: CF 1939 B - Evidence Board
// https://codeforces.com/contest/1939/problem/B

/*
 * Code Purpose: This code solves the "Evidence Board" problem, which involves determining a valid chronological order of connections in a detective investigation.
 *               It builds a graph of connections, processes sticker information, and uses DFS to assign connection indices to stickers, then performs a topological traversal to deduce the order.
 * 
 * Algorithms/Techniques:
 * - Graph representation using adjacency lists
 * - Depth-First Search (DFS) for assigning connection indices
 * - Set-based sticker management for efficient lookups
 * - Topological ordering via BFS traversal
 * 
 * Time Complexity: O(n log n) where n is the number of persons
 * Space Complexity: O(n) for storing graph, stickers, and auxiliary data structures
 */
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <utility>
#include <vector>

#define pb push_back
#define del pop_back
#define ll long long
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pli pair<ll, int>
#define deriva_e_iguala_a return
#define fcin ios_base::sync_with_stdio(false)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define all(v) v.begin(), v.end()
#define print(vec, a, b)                                                       \
  for (int i = a; i < b; i++) {                                                \
    cout << vec[i] << ' ';                                                     \
  }                                                                            \
  cout << endl
#define printr(vec)                                                            \
  for (auto i : vec) {                                                         \
    cout << i << ' ';                                                          \
  }                                                                            \
  cout << endl
#define endl '\n'
#define f first
#define s second
#define ordered_set                                                            \
  __gnu_pbds::tree<pii, __gnu_pbds::null_type, less<pii>,                      \
                   __gnu_pbds::rb_tree_tag,                                    \
                   __gnu_pbds::tree_order_statistics_node_update>
using namespace std;
const int IINF = 2e9 + 1, MOD = 998244353, MOD2 = 1e9 + 7;
const ll INF = 1e18;
const double PI = acos(-1);
const int dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0};
const int N = 2e5 + 3;
vector<pii> graph[N], st[N];
set<pii> ss[N];
vector<array<int, 3>> edges;
bool flag = 0;
void dfs(int u, int p, int cur_idx) {
  for (pii pp : graph[u]) {
    int v = pp.f, w = pp.s;
    if (v == p)
      continue;
    dfs(v, u, w);
  }
  if (p) {
    auto it = ss[u].begin();
    int x = it->first, idx_u = it->second, w = edges[cur_idx][2];
    auto it2 = ss[p].lower_bound(mp(w - x, 0));
    if (it2 == ss[p].end()) {
      flag = 1;
      return;
    }
    int idx_p = it2->second;
    st[u][idx_u].second = st[p][idx_p].second = cur_idx;
    ss[u].erase(it);
    ss[p].erase(it2);
  }
}
int main() {
  fcin;
  cin.tie(0);
  int t = 1;
  while (t--) {
    int n, g, u, v, w, x;
    cin >> n >> g;
    vector<int> deg(n + 1);
    edges.reserve(n - 1);
    for (int i = 0; i < n - 1; ++i) {
      cin >> u >> v >> w;
      edges.pb({u, v, w});
      graph[u].pb(mp(v, i));
      graph[v].pb(mp(u, i));
      ++deg[u], ++deg[v];
    }
    for (int i = 1; i <= n; ++i) {
      st[i].reserve(deg[i]);
      for (int j = 0; j < deg[i]; ++j) {
        cin >> x;
        st[i].pb(mp(x, -1));
        ss[i].insert(mp(x, j));
      }
    }
    dfs(1, 0, 0);
    if (flag) {
      cout << "No" << endl;
      continue;
    }
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
      q.push(i);
    }
    vector<int> ans;
    ans.reserve(n - 1);
    while (!q.empty()) {
      u = q.front();
      q.pop();
      while (!st[u].empty()) {
        int idx = st[u].back().second,
            v = (edges[idx][0] != u ? edges[idx][0] : edges[idx][1]);
        if (st[v].back().second == idx) {
          st[v].pop_back();
          st[u].pop_back();
          ans.pb(idx + 1);
          q.push(v);
        } else {
          break;
        }
      }
    }
    cout << "Yes" << endl;
    printr(ans);
  }
}


// https://github.com/VaHiX/CodeForces/