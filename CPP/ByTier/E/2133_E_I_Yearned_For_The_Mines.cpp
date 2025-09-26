// Problem: CF 2133 E - I Yearned For The Mines
// https://codeforces.com/contest/2133/problem/E

/*
E. I Yearned For The Mines

Algorithms/Techniques: Tree DFS, Greedy Strategy, Decomposition of Tree into Components

Time Complexity: O(n) per test case
Space Complexity: O(n) for storage of tree and auxiliary arrays

This code implements a strategy to catch Herobrine in a tree-shaped mine by performing 
a sequence of checks (operation 1) or destroying edges (operation 2) on nodes. 
The algorithm uses a two-phase DFS traversal:
1. First phase identifies leaf nodes and determines which ones require special operations,
   marking nodes that are part of structures that can trap Herobrine.
2. Second phase performs check operations on remaining unvisited nodes, ensuring all paths
   are covered and Herobrine is caught in at most ⌊5/4 * n⌋ steps.

*/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define pii pair<int, int>
#define MP make_pair
#define F first
#define S second
using namespace std;
const int N = 2e5 + 3;
int T, n, c[N], vis[N];
vector<int> lv;
vector<pii> op;
int Next[N << 1], ver[N << 1], head[N], tot;
void add(int x, int y) {
  ver[++tot] = y;
  Next[tot] = head[x], head[x] = tot;
}
void dfs1(int u, int fa) {
  int cnt = 0, fl = 0;
  for (int i = head[u]; i; i = Next[i]) {
    int v = ver[i];
    if (v == fa)
      continue;
    dfs1(v, u);
    if (c[v] == 1)
      cnt++;
    if (c[v] == 2)
      fl = 1;
  }
  if (!cnt)
    lv.emplace_back(u); // Leaf node
  if (cnt >= 3 || fl) {
    op.push_back(MP(2, u)); // Destroy edges connected to this node
    op.push_back(MP(1, u)); // Then check it
    c[u] = 3;
    vis[u] = 1;
  } else if (cnt == 2)
    c[u] = 2;
  else
    c[u] = 1;
}
void dfs2(int u) {
  vis[u] = 1;
  op.push_back(MP(1, u)); // Check the current node
  for (int i = head[u]; i; i = Next[i]) {
    int v = ver[i];
    if (!vis[v] && c[v] != 3)
      dfs2(v); // Recursively traverse other subtrees
  }
}
void Main() {
  cin >> n;
  lv.clear();
  op.clear();
  tot = 0;
  for (int i = 1; i <= n; i++)
    head[i] = vis[i] = 0;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    add(u, v);
    add(v, u);
  }
  dfs1(1, 0); // Phase 1: traverse and decide which nodes to destroy/check
  for (auto u : lv)
    if (!vis[u])
      dfs2(u); // Phase 2: check remaining unvisited nodes in a DFS way
  cout << op.size() << "\n";
  for (auto u : op)
    cout << u.F << " " << u.S << "\n";
}
signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--)
    Main();
  return 0;
}


// https://github.com/VaHiX/codeForces/