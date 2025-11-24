// Problem: CF 2052 C - Cactus without Bridges
// https://codeforces.com/contest/2052/problem/C

#include <algorithm>
#include <array>
#include <iostream>
#include <string>

using namespace std;
constexpr int N = 1e5;
// Cactus without Bridges - Label edges such that each vertex has distinct consecutive labels
// Time Complexity: O(n + m)
// Space Complexity: O(n + m)
basic_string<array<int, 2>> nei[N];
int tin[N], tup[N], ce[N], pe[N], ue[N], ct, ans[2 * N];

void dfs0(int v, int p) {
  // First DFS to compute DFS tree and find back edges
  tin[v] = tup[v] = ++ct;
  for (auto [u, e] : nei[v])
    if (u != p)
      if (!tin[u]) {
        pe[u] = e;             // parent edge
        dfs0(u, v);
        ce[v] ^= ce[u] ^ 1;    // xor of cycle flags along the path
        tup[v] = min(tup[v], tup[u]); // low value update
      } else if (tin[u] < tin[v]) {
        ue[v] = e;             // back edge to ancestor
        ce[v] ^= 1;            // mark this as odd cycle
        tup[v] = min(tup[v], tin[u]);
      }
}

void dfs1(int v, int ofs) {
  // Second DFS to assign labels for each component
  basic_string<int> vs, es{pe[v]}, ds{0};
  for (int u = v; ~u;) {
    vs.push_back(u);
    int nx = -1, x = 0;
    for (auto [w, e] : nei[u])
      if (tin[w] > tin[u])
        if (tup[w] == tup[u]) {
          nx = w;
          es.push_back(e);
        } else if (pe[w] == e)
          x ^= ce[w] ^ 1;    // xor of cycle flags for each subcomponent
    ds.push_back(ds.back() ^ (1 << x));
    if (!~nx)
      es.push_back(ue[u]);   // append back edge if needed
    u = nx;
  }
  // Adjust labeling based on parity conditions
  if (!ds.back() || ds.back() == 3) {
    int i = ds.size() - 1;
    while (ds[i] ^ ds[i - 1] ^ 1)
      --i;
    int s = 2 * (ds[i] - ds[i - 1]);
    while (i < ds.size())
      ds[i++] -= s;
  }
  // Adjust offset to ensure no negative labels
  ofs += max(0, -ds.back());
  for (int i = 0; i < es.size(); ++i)
    ans[es[i]] = ds[i] += ofs;
  for (int i = 0; i < vs.size(); ++i) {
    int x = ds[i] + ds[i + 1] + 1 & 1, l = -2 * !x, r = x,
        nofs = min(ds[i], ds[i + 1]) - l;
    for (auto [w, e] : nei[vs[i]])
      if (tup[w] == tin[vs[i]] && pe[w] == e) {
        dfs1(w, nofs + (ce[w] ? l -= 2 : r++)), r += r & 2; // recursive DFS into subtree
      }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  if (m % 2)
    return cout << "NO\n", 0;
  for (int i = 0, a, b; i < m; ++i)
    cin >> a >> b, nei[--a].push_back({--b, i}), nei[b].push_back({a, i}); // build adjacency list
  int r = 0;
  while (nei[r].size() > 2)
    ++r;
  dfs0(r, r);    // first DFS
  dfs1(nei[r][0][0], 0);  // second DFS to label edges
  int ofs = *min_element(ans, ans + m) - 1;
  cout << "YES\n" << *max_element(ans, ans + m) - ofs << '\n';
  for (int i = 0; i < m; ++i)
    cout << ans[i] - ofs << ' ';
}


// https://github.com/VaHiX/codeForces/