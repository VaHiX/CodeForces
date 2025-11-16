// Problem: CF 1787 G - Colorful Tree (again)
// https://codeforces.com/contest/1787/problem/G

#include <bits/stdc++.h>
using namespace std;

/*
  Problem: Colorful Tree (again) - enhanced version

  Summary:
  - We have a tree with n nodes and edges colored by colors (1..n).
  - For each color `c`, we consider the subgraph formed by edges of that color.
    If this subgraph is a simple path between two endpoints u[c], v[c], we
    compute its LCA and the total weight w[c] of edges of that color; otherwise
    the color `c` is ignored.
  - The program maintains, for each node x, a set S[x] of valid colors whose
    path's LCA is x (with pair {w[color], color}). We also maintain a global
    multiset `answer` that stores, for each node x that is currently "visible",
    the maximum w among S[x] (i.e., the last element of S[x]). The query asks
    to toggle visibility of a node and adjust contributions (with some extra
    logic related to adjacent colors along the parent edge).

  Data structures:
  - E[u]: adjacency list of the tree
  - edge[c]: list of edges with color c
  - mp[{u,v}] = {weight, color} for quick lookup of edge properties
  - Binary lifting arrays `fa` and `dep` for LCA computation
  - For each color c that forms a valid path, we store:
      u[c], v[c] = endpoints of the path
      lca[c] = LCA(u[c], v[c])
      w[c] = total weight of edges of color c
    and we add {w[c], c} into S[lca[c]] so contributions are grouped by LCA.

  Query handling:
  - Each node x has a visibility flag `vis[x]` that controls whether its
    contribution (the maximum of S[x]) is present in the global multiset
    `answer`.
  - Additionally, `facol[x]` stores the color of the edge between x and its
    parent (if any) -- when toggling x we must also enable/disable the color
    associated with that parent edge under certain conditions; `cntdel[color]`
    tracks how many endpoints of that color are currently hidden.

  The rest of the code builds these structures, initializes S and answer,
  and processes q toggle queries printing the current maximum over `answer`
  (or 0 if empty).
*/

int n, q;
vector<int> E[200001]; // adjacency list for the tree
vector<pair<int, int>>
    edge[200001]; // edges grouped by color: edge[c] contains (u,v)
map<pair<int, int>, pair<int, int>> mp; // maps (u,v) -> (weight, color)
int dep[200001], fa[200001][19];        // depth and binary-lifting parents

// Precompute depth and binary lifting parents for LCA queries
void init(int u, int father) {
  dep[u] = dep[father] + 1;
  fa[u][0] = father;
  for (int k = 1; k <= 18; k++)
    fa[u][k] = fa[fa[u][k - 1]][k - 1];
  for (int v : E[u])
    if (v != father)
      init(v, u);
}

// Standard binary-lifting LCA: lift deeper node up, then lift both together
int LCA(int u, int v) {
  if (dep[u] < dep[v])
    swap(u, v);
  for (int k = 18; k >= 0; k--)
    if (dep[u] - dep[v] >= (1 << k))
      u = fa[u][k];
  if (u == v)
    return u;
  for (int k = 18; k >= 0; k--)
    if (fa[u][k] != fa[v][k])
      u = fa[u][k], v = fa[v][k];
  return fa[u][0];
}

// Per-color and per-node bookkeeping
int deg[200001],
    facol[200001]; // deg temporary, facol[x] = color of parent edge
int u[200001], v[200001], lca[200001], cntdel[200001];
long long w[200001]; // total weight per color (only for valid colors)
set<pair<long long, int>>
    S[200001]; // S[x] holds pairs {w[color], color} with LCA == x
multiset<long long>
    answer;       // global multiset of per-node maxima (one per visible node)
bool vis[200001]; // visibility flag per node

// Helper to add the current maximum of S[u] into the global `answer` set
void insert(int u) {
  if (S[u].empty())
    return;
  // insert the largest w present at node u (last element of the ordered set)
  answer.insert((*--S[u].end()).first);
}

// Helper to remove the current maximum of S[u] from the global `answer` set
void remove(int u) {
  if (S[u].empty())
    return;
  long long val = (*--S[u].end()).first;
  answer.erase(answer.find(val));
}

int main() {
  scanf("%d%d", &n, &q);
  // Read the tree edges: each edge has endpoints u,v, weight w, and color c
  for (int i = 1; i < n; i++) {
    int u, v, w, c;
    scanf("%d%d%d%d", &u, &v, &w, &c);
    E[u].push_back(v);
    E[v].push_back(u);
    edge[c].emplace_back(u, v);
    // store weight and color keyed by unordered pair (u,v)
    mp[{u, v}] = mp[{v, u}] = {w, c};
  }

  // Prepare LCA structures (root the tree at node 1)
  init(1, 0);

  // For each color i, determine if the edges of that color form a simple path.
  // Approach: maintain degree counts for vertices incident to edges of color i
  // and collect the distinct vertices involved. For a valid path we must have
  // exactly two endpoints of degree 1 and all other involved vertices degree 2.
  for (int i = 1; i <= n; i++) {
    // First, remove counts of edges of previous color (i-1) to reuse `deg`
    // array
    for (pair<int, int> e : edge[i - 1])
      deg[e.first]--, deg[e.second]--;
    set<int> s; // set of vertices that participate in color i's edges
    for (pair<int, int> e : edge[i]) {
      deg[e.first]++, deg[e.second]++;
      s.insert(e.first), s.insert(e.second);
    }

    // Quick validity check: no vertex in this set should have degree >= 3
    bool flag = true;
    for (int j : s)
      if (deg[j] >= 3)
        flag = false;

    // Find the two endpoints of the path (vertices with degree == 1)
    for (int j : s) {
      if (deg[j] != 1)
        continue;
      if (!u[i])
        u[i] = j;
      else if (!v[i])
        v[i] = j;
      else
        flag = false; // more than two endpoints -> not a simple path
    }
    if (!v[i])
      flag = false; // less than two endpoints -> invalid
    if (!flag)
      continue; // skip this color if not forming a path

    // Valid path: compute LCA of endpoints and total weight
    lca[i] = LCA(u[i], v[i]);
    for (pair<int, int> e : edge[i])
      w[i] += mp[e].first;
    // Store this color in the set corresponding to its path's LCA
    S[lca[i]].insert({w[i], i});
  }

  // For each node i>1 compute the color of the edge connecting it to its parent
  // facol[i] = color of edge (i, parent). If that color was invalid
  // (w[color]==0) set facol to 0 meaning no special color assigned.
  for (int i = 2; i <= n; i++) {
    facol[i] = mp[{i, fa[i][0]}].second;
    if (!w[facol[i]])
      facol[i] = 0;
  }

  // Initially mark all nodes visible and add their per-node maxima to `answer`.
  for (int i = 1; i <= n; i++)
    insert(i), vis[i] = true;

  // Process q queries. Each query toggles visibility of a node x (op=0 -> hide,
  // op=1 -> show) When hiding/showing a node x, we also need to potentially
  // disable/enable the color associated with the parent edge of x (facol[x])
  // using cntdel to handle both endpoints being hidden/shown.
  while (q--) {
    int op, x;
    scanf("%d%d", &op, &x);
    if (op == 0) {
      // Hide node x: remove its max contribution from global answer
      vis[x] = false;
      remove(x);
      int id = facol[x];
      if (id) {
        if (!cntdel[id]) {
          // If this is the first endpoint being hidden, remove color id
          // from its LCA set and update `answer` accordingly
          if (vis[lca[id]])
            remove(lca[id]);
          S[lca[id]].erase({w[id], id});
          if (vis[lca[id]])
            insert(lca[id]);
        }
        cntdel[id]++;
      }
    } else {
      // Show node x: add its max contribution back
      vis[x] = true;
      insert(x);
      int id = facol[x];
      if (id) {
        cntdel[id]--;
        if (!cntdel[id]) {
          // If both endpoints now visible, reinsert the color into its LCA set
          if (vis[lca[id]])
            remove(lca[id]);
          S[lca[id]].insert({w[id], id});
          if (vis[lca[id]])
            insert(lca[id]);
        }
      }
    }
    // Output current maximum over all visible per-node maxima (or 0 if empty)
    printf("%lld\n", answer.empty() ? 0 : *--answer.end());
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/