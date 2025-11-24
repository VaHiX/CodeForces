// Problem: CF 1192 B - Dynamic Diameter
// https://codeforces.com/contest/1192/problem/B

/*
Purpose: 
This code solves the Dynamic Diameter problem on a tree. It supports updates to edge weights and efficiently computes the diameter of the tree after each update. The approach uses a DFS traversal to build a Euler tour of the tree, then builds a segment tree to maintain information about the diameter.

Algorithms:
1. DFS Euler Tour to represent tree as array
2. Segment Tree with lazy propagation to maintain diameter information
3. Dynamic updates with propagation

Time Complexity: O((n + q) * log n)
Space Complexity: O(n * log n)

*/
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
#include <utility>

using namespace std;
using ll = long long;

// Node structure for segment tree
struct Node {
  ll min_d;
  ll max_d;
  ll best;
  ll best_l;
  ll best_r;
  ll lazy;
  Node() : min_d(0), max_d(0), best(0), best_l(0), best_r(0), lazy(0) {}
};

// Global variables for tree representation and operations
vector<vector<pair<int, ll>>> graph;  // Adjacency list representation
vector<tuple<int, int, ll>> edges;   // Store original edges
vector<ll> current_edge_weight;      // Current weights of edges
vector<int> child_node;              // Child node for each edge (based on DFS)
vector<int> parent_vec;              // Parent of each node
vector<ll> depth_node;               // Depth of each node
vector<int> in_time;                 // In time of DFS traversal
vector<int> out_time;                // Out time of DFS traversal
vector<ll> D;                        // Euler tour depths
int timer = 0;                       // Timer for DFS
int n, q;                            // Number of vertices and queries
ll w;                                // Weight limit
vector<Node> seg_tree;               // Segment tree for diameter tracking

// DFS to compute in/out times and depth for Euler tour
void dfs_times(int u, int parent, ll depth) {
  in_time[u] = timer;
  D[timer] = depth;
  timer++;
  for (auto &edge : graph[u]) {
    int v = edge.first;
    ll weight = edge.second;
    if (v == parent)
      continue;
    parent_vec[v] = u;
    depth_node[v] = depth + weight;
    dfs_times(v, u, depth + weight);
    D[timer] = depth;
    timer++;
  }
  out_time[u] = timer - 1;
}

// Merge two nodes for segment tree
Node merge(Node &L, Node &R) {
  Node res;
  res.min_d = min(L.min_d, R.min_d);
  res.max_d = max(L.max_d, R.max_d);
  res.best_l = max({L.best_l, R.best_l, R.max_d - 2 * L.min_d});
  res.best_r = max({R.best_r, L.best_r, L.max_d - 2 * R.min_d});
  res.best = max({L.best, R.best, L.best_r + R.max_d, L.max_d + R.best_l});
  res.lazy = 0;
  return res;
}

// Push lazy values to children
void push(int node_idx, int l, int r) {
  if (seg_tree[node_idx].lazy != 0) {
    seg_tree[node_idx].min_d += seg_tree[node_idx].lazy;
    seg_tree[node_idx].max_d += seg_tree[node_idx].lazy;
    seg_tree[node_idx].best_l -= seg_tree[node_idx].lazy;
    seg_tree[node_idx].best_r -= seg_tree[node_idx].lazy;
    if (l != r) {
      seg_tree[2 * node_idx + 1].lazy += seg_tree[node_idx].lazy;
      seg_tree[2 * node_idx + 2].lazy += seg_tree[node_idx].lazy;
    }
    seg_tree[node_idx].lazy = 0;
  }
}

// Build the segment tree from Euler tour
void build_seg_tree(int node_idx, int l, int r) {
  if (l == r) {
    seg_tree[node_idx].min_d = D[l];
    seg_tree[node_idx].max_d = D[l];
    seg_tree[node_idx].best = 0;
    seg_tree[node_idx].best_l = -D[l];
    seg_tree[node_idx].best_r = -D[l];
    seg_tree[node_idx].lazy = 0;
    return;
  }
  int mid = (l + r) / 2;
  build_seg_tree(2 * node_idx + 1, l, mid);
  build_seg_tree(2 * node_idx + 2, mid + 1, r);
  seg_tree[node_idx] =
      merge(seg_tree[2 * node_idx + 1], seg_tree[2 * node_idx + 2]);
}

// Update segment tree with a delta value for a range
void update_seg_tree(int node_idx, int l, int r, int ql, int qr, ll add) {
  push(node_idx, l, r);
  if (qr < l || r < ql) {
    return;
  }
  if (ql <= l && r <= qr) {
    seg_tree[node_idx].lazy = add;
    push(node_idx, l, r);
    return;
  }
  int mid = (l + r) / 2;
  update_seg_tree(2 * node_idx + 1, l, mid, ql, qr, add);
  update_seg_tree(2 * node_idx + 2, mid + 1, r, ql, qr, add);
  push(2 * node_idx + 1, l, mid);
  push(2 * node_idx + 2, mid + 1, r);
  seg_tree[node_idx] =
      merge(seg_tree[2 * node_idx + 1], seg_tree[2 * node_idx + 2]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> q >> w;
  graph.resize(n);
  edges.resize(n - 1);
  current_edge_weight.resize(n - 1);
  child_node.resize(n - 1);
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    ll c;
    cin >> a >> b >> c;
    a--;
    b--;
    edges[i] = make_tuple(a, b, c);
    current_edge_weight[i] = c;
    graph[a].push_back({b, c});
    graph[b].push_back({a, c});
  }
  parent_vec.resize(n, -1);
  depth_node.resize(n, 0);
  in_time.resize(n);
  out_time.resize(n);
  D.resize(2 * n - 1, 0);
  dfs_times(0, -1, 0);
  // Determine child for each edge based on DFS (parent relationship)
  for (int i = 0; i < n - 1; i++) {
    int a = get<0>(edges[i]);
    int b = get<1>(edges[i]);
    if (parent_vec[b] == a) {
      child_node[i] = b;
    } else {
      child_node[i] = a;
    }
  }
  int size = 2 * n - 1;
  seg_tree.resize(4 * size);
  build_seg_tree(0, 0, size - 1);
  ll last = 0;
  for (int i = 0; i < q; i++) {
    ll d, e;
    cin >> d >> e;
    d = (d + last) % (n - 1);
    e = (e + last) % w;
    int edge_index = d;
    ll new_weight = e;
    ll old_weight = current_edge_weight[edge_index];
    ll delta = new_weight - old_weight;
    current_edge_weight[edge_index] = new_weight;
    int child = child_node[edge_index];
    update_seg_tree(0, 0, size - 1, in_time[child], out_time[child], delta);
    last = seg_tree[0].best;
    cout << last << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/