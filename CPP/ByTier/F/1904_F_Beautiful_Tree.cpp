/* ******************************************************************************
 * Problem: 1904 F - Beautiful Tree
 * https://codeforces.com/contest/1904/problem/F
 *
 * Description:
 * Given a tree and a set of operations that add directed constraints between
 * segments of the Euler tour of the tree (implemented via a segment-tree-like
 * graph), determine an ordering of vertices consistent with all constraints or
 * report -1 if impossible. The solution builds a directed acyclic graph
 * representing dependencies and performs a topological sort.
 *
 * Time Complexity:
 * - Building the segment-style graph: O(N log N + M log N)
 * - Topological sort (DFS): O(V + E)
 * Overall complexity dominated by graph construction and edges added by
 *updates.
 *
 * Space Complexity:
 * - O(N log N) nodes in the auxiliary graph (segment tree layers)
 * - O(E) edges where E depends on number of updates and ranges
 *
 * Key components:
 * 1. Heavy-child reordering of the rooted tree (dfs) to support path splitting
 * 2. Euler tour / in-order indexing (dfs1) to map subtree/paths to ranges
 * 3. A three-layer directed graph constructed from segment-tree indices
 * 4. Range update function that links segments to constraint nodes
 * 5. Topological sort to extract valid ordering or detect a cycle
 ******************************************************************************/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef long double ld;
typedef vector<int> vi;
#define mp make_pair
#define pb push_back
#define all(v) v.begin(), v.end()

constexpr int maxn = (1 << 18) + 5;

int n, m, q, k, t, a, b, c;
// adjacency list of the input tree
vector<int> v[maxn];
// subtree sizes computed during first DFS
int sz[maxn];
// head[x] stores the head (top) of the heavy-path containing x
int head[maxn];

// First DFS: computes subtree sizes and identifies the "heavy" child
// For each node x we move the child with maximum subtree size to v[x][0].
// This is a common trick to facilitate heavy-path decomposition and
// to make path-to-range conversions easier later.
void dfs(int x, int par) {
  sz[x] = 1;
  pii cmax = {0, 0};
  for (int i = 0; i < v[x].size(); i++) {
    int it = v[x][i];
    if (it == par)
      continue;
    dfs(it, x);
    sz[x] += sz[it];
    cmax = max(cmax, {sz[it], i});
  }
  // place the heavy child at index 0
  swap(v[x][0], v[x][cmax.second]);
}

int dfsCnt = 0;
// in[x] = position of x in DFS order (Euler index)
int in[maxn];
// depth of node in rooted tree
int depth[maxn];
// node[pos] = original node id at DFS position pos
int node[maxn];
// parent in the rooted tree
int p[maxn];

// Second DFS: generate Euler-order indices and set up heavy-path heads
// head[x] indicates the top node of the heavy-path containing x
void dfs1(int x, int par) {
  in[x] = dfsCnt++;
  node[dfsCnt - 1] = x;
  p[x] = par;
  depth[x] = depth[par] + 1;

  for (auto it : v[x]) {
    if (it == par)
      continue;
    // If child is not heavy child, it starts a new head; otherwise it
    // inherits head from parent to remain on same heavy path.
    if (it != v[x][0]) {
      head[it] = it;
    } else {
      head[it] = head[x];
    }
    dfs1(it, x);
  }
}

// N is the segment-tree base size used for mapping ranges to nodes
constexpr int N = 1 << 18;
// Auxiliary directed graph (three layered): internal segment nodes, leaves,
// and reversed-layer nodes for backward edges. Size 3*N accommodates them.
vector<int> adj[3 * N];

// Build base connections between segment-tree nodes and the reversed layer.
// This preconstructs structural edges used by range updates.
void build() {
  for (int i = 1; i < N; i++) {
    // standard segment tree parent -> children edges
    adj[i].pb(2 * i);
    adj[i].pb(2 * i + 1);
    if (2 * i < N) {
      // connect reversed children -> reversed parent
      adj[2 * i + 2 * N].pb(i + 2 * N);
      adj[2 * i + 1 + 2 * N].pb(i + 2 * N);
    } else {
      // leaf-level linking into reversed layer
      adj[2 * i].pb(i + 2 * N);
      adj[2 * i + 1].pb(i + 2 * N);
    }
  }
}

// Convert a range [l, r) into O(log N) segment nodes and add directed
// edges between the constraint node x and those nodes. Parameter t decides
// direction: t == 1 means add edges x -> segment_nodes, otherwise segment_nodes
// -> x. Special-case: if x lies strictly inside [l, r) we split into two ranges
// (l, x) and (x+1, r) to avoid self-loop semantics.
void update(int l, int r, int x, int t) {
  if (l <= x && x < r) {
    // split range to exclude x itself
    update(l, x, x, t);
    update(x + 1, r, x, t);
    return;
  }
  // traverse segment tree range in the usual iterative way
  for (l += N, r += N, x += N; l < r; l >>= 1, r >>= 1) {
    if (t == 1) {
      if (l & 1)
        adj[x].pb(l++);
      if (r & 1)
        adj[x].pb(--r);
    } else {
      int pad = 0;
      if (l < N)
        pad = 2 * N; // use reversed-layer offset for internal nodes
      if (l & 1)
        adj[pad + l++].pb(x);
      if (r & 1)
        adj[pad + --r].pb(x);
    }
  }
}

// Add an operation that affects the path between nodes a and b.
// Using heavy-path decomposition, we break the path into O(log N) ranges
// on the Euler indices and call update to convert each range into graph edges.
// t: direction flag, c: index (constraint node) used in the auxiliary graph.
void add(int t, int a, int b, int c) {
  while (head[a] != head[b]) {
    if (depth[head[a]] < depth[head[b]])
      swap(a, b);
    // add edges covering the segment from head[a] to a
    update(in[head[a]], in[a] + 1, c, t);
    a = p[head[a]]; // jump to parent of the current heavy-path head
  }
  if (depth[a] < depth[b])
    swap(a, b);
  // final segment when both nodes are on same heavy-path
  update(in[b], in[a] + 1, c, t);
}

// visited/done flags for DFS-based topo sort on the auxiliary graph
bool vis[3 * N];
bool done[3 * N];
// ok becomes false if a cycle is detected
bool ok = true;
// ordering stack (postorder result for leaves corresponding to original nodes)
vector<int> st;

// Depth-first topological sort with cycle detection.
// If a back-edge is found (vis=true but done=false), we mark ok=false.
// When a node corresponding to an original tree vertex is finished
// (leaf-layer index in [N, N+n)), we record it in st for final ordering.
void toposort(int x) {
  if (!ok)
    return;
  vis[x] = true;
  for (auto it : adj[x]) {
    if (!vis[it]) {
      toposort(it);
    } else if (!done[it]) {
      // back-edge -> cycle
      ok = false;
      return;
    }
  }
  done[x] = true;
  if (x >= N && x < N + n)
    st.pb(node[x - N]);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  // read tree
  cin >> n >> m;
  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b;
    a--, b--;
    v[a].pb(b);
    v[b].pb(a);
  }

  // prepare heavy-child ordering and Euler indices
  dfs(0, 0);
  head[0] = 0;
  dfs1(0, 0);

  // build auxiliary graph structure
  build();

  // read and apply m operations (constraints)
  for (int i = 0; i < m; i++) {
    cin >> t >> a >> b >> c;
    a--, b--, c--;
    add(t, a, b, in[c]);
  }

  // run topological sort on the entire auxiliary graph
  for (int i = 1; i < 3 * N; i++) {
    if (!vis[i]) {
      toposort(i);
    }
  }

  if (ok) {
    // the recorded list is in reverse-topological order; reverse it
    reverse(all(st));
    vector<int> idx(n);
    for (int i = 0; i < n; i++) {
      idx[st[i]] = i + 1;
    }
    for (auto it : idx)
      cout << it << " ";
  } else {
    // cycle detected -> impossible
    cout << -1;
  }
}

// https://github.com/VaHiX/CodeForces/