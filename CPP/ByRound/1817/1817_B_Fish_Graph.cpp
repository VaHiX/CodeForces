// Problem: CF 1817 B - Fish Graph
// https://codeforces.com/contest/1817/problem/B

/*
 * Fish Graph Detection Algorithm
 *
 * Purpose:
 * This code determines whether a given undirected graph contains a subgraph that is a "Fish Graph".
 * A Fish Graph is defined as a simple cycle with a special node u belonging to the cycle,
 * and exactly 2 additional edges connecting to node u, but not to any other node in the cycle.
 *
 * Algorithm:
 * 1. For each node with degree >= 4, perform DFS to find a cycle that includes this node.
 * 2. Once a cycle is found, check if there are 2 edges from the special node to nodes that are not part of the cycle.
 * 3. If such a configuration exists, output the edges forming the Fish Graph.
 *
 * Time Complexity: O(n * (n + m)) where n is number of nodes and m is number of edges
 * Space Complexity: O(n + m) for storing adjacency list and auxiliary arrays
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
const int maxn = 2e5 + 10;
const int mod = 1e9 + 7;
int n, m;
ll ksm(ll x, ll y);
vector<int> e[maxn]; // adjacency list
int deg[maxn];       // degree of each node
int vis[maxn];       // visited array for DFS
vector<int> ans;     // stores nodes in the found cycle
int tt[maxn];        // marks nodes that belong to the cycle

// DFS function to find a cycle starting from 'now', with parent 'fa'
// cnt tracks the depth of the current DFS
int dfs(int now, int fa, int cnt = 1) {
  // If node is visited and it's the starting node, and depth is at least 4
  if (vis[now] && fa == now && cnt >= 4) {
    ans.push_back(now);  // add to cycle list
    tt[now] = 1;         // mark as part of cycle
    return 1;
  }
  // If already visited, skip
  if (vis[now])
    return 0;
  vis[now] = 1;  // mark current node as visited
  for (int to : e[now]) {
    // Skip if it's the parent
    if (to == fa) {
      if (dfs(to, fa, cnt + 1)) {
        ans.push_back(now);  // add current to cycle list
        tt[now] = 1;         // mark current as part of cycle
        return 1;
      }
    }
  }
  for (int to : e[now]) {
    if (to == fa)
      continue;  // skip parent
    if (dfs(to, fa, cnt + 1)) {
      ans.push_back(now);  // add current to cycle list
      tt[now] = 1;         // mark current as part of cycle
      return 1;
    }
  }
  return 0;
}

void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    deg[i] = 0;
    e[i].clear();
    tt[i] = 0;
  }
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
    deg[u]++;
    deg[v]++;
  }
  ans.clear();
  for (int i = 1; i <= n; i++) {
    if (deg[i] < 4)  // skip nodes with degree less than 4
      continue;
    for (int j = 1; j <= n; j++) {
      vis[j] = 0;  // reset visited array
    }
    dfs(i, i);  // start DFS from node i
    if (ans.size()) {  // Found a valid cycle
      vector<pair<int, int>> out;  // store edges for output
      cout << "YES\n";
      cout << ans.size() + 1 << "\n";  // +1 because we need 2 extra edges
      for (int j = 0; j + 1 < ans.size(); j++) {
        out.push_back({ans[j], ans[j + 1]});  // connect consecutive nodes in cycle
      }
      int cnt = 0;  // count of extra edges found
      for (int to : e[i]) {
        if (!tt[to]) {  // if node is not in the cycle
          cnt++;
          out.push_back({i, to});  // add extra edge
        }
        if (cnt == 2) {  // found 2 extra edges
          break;
        }
      }
      if (cnt == 2) {  // if we successfully added 2 extra edges
        for (auto temp : out) {
          cout << temp.first << " " << temp.second << "\n";  // print all edges
        }
      }
      return;
    }
  }
  cout << "NO\n";  // no valid Fish Graph found
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int _ = 1;
  cin >> _;
  while (_--) {
    solve();
  }
  return 0;
}

ll ksm(ll x, ll y) {
  ll ret = 1;
  do {
    if (y & 1)
      ret = ret * x % mod;
    x = x * x % mod;
  } while (y >>= 1);
  return ret;
}


// https://github.com/VaHiX/CodeForces/