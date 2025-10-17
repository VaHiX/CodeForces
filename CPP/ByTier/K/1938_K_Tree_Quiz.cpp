// Problem: CF 1938 K - Tree Quiz
// https://codeforces.com/contest/1938/problem/K

/*
 * Problem: Tree Quiz
 * Algorithms: Persistent Segment Tree, DFS, Binary Indexed Tree (Fenwick Tree)
 *
 * Time Complexity: O((n + q) * log n)
 * Space Complexity: O(n * log n)
 *
 * Description:
 * Given a rooted tree of n nodes and q queries, each asking for the k-th smallest
 * element in an array L constructed from all pairs (x, y) where each element is
 * calculated as (x - 1) * n * n + (LCA(x, y) - 1) * n + (y - 1).
 * 
 * Approach:
 * - Use a persistent segment tree to efficiently compute order statistics.
 * - Perform DFS traversal to build in/out time stamps for subtree queries.
 * - Utilize a Fenwick tree for updating and querying subtree sizes while traversing
 *   the tree via DFS.
 * - For each query, calculate k-th smallest element using persistent segment tree and
 *   subtree information.
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
#define mid ((l + r) >> 1)

struct Node {
  int l, r, s; // left, right child indices and count of elements in range
} pt[5005005]; // persistent segment tree nodes

int pc; // persistent counter for new nodes
int n, m, sz[100100], child[100100], in[100100], out[100100], rev[100100], cnt,
    r[100100]; // arrays for DFS traversal and persistent segment tree

vector<int> v[100100]; // adjacency list for tree
vector<array<int, 2>> query[100100]; // queries grouped by node
ll ans[100100]; // answers to each query

// Build persistent segment tree
int build_pst(int l = 1, int r = n) {
  int u = ++pc;
  if (l == r)
    return u;
  pt[u].l = build_pst(l, mid);
  pt[u].r = build_pst(mid + 1, r);
  return u;
}

// Update persistent segment tree
int update_pst(int u, int id, int l = 1, int r = n) {
  if (id < l || r < id)
    return u;
  int x = ++pc; // create new node for this version
  pt[x] = pt[u], pt[x].s++;
  if (l == r)
    return x;
  pt[x].l = update_pst(pt[x].l, id, l, mid);
  pt[x].r = update_pst(pt[x].r, id, mid + 1, r);
  return x;
}

// Find kth smallest element in persistent segment tree
int find_kth_pst(int L, int ml, int mr, int R, int k, int l = 1, int r = n) {
  if (l == r)
    return l;
  int C = pt[pt[R].l].s - pt[pt[L].l].s; // count of elements in left subtree
  int c = pt[pt[mr].l].s - pt[pt[ml].l].s; // same for the other tree
  if (C - c >= k) // if remaining elements in right subtree exceed k
    return find_kth_pst(pt[L].l, pt[ml].l, pt[mr].l, pt[R].l, k, l, mid);
  return find_kth_pst(pt[L].r, pt[ml].r, pt[mr].r, pt[R].r, k - C + c, mid + 1,
                      r);
}

// DFS to set in/out time and size of each subtree
void dfs(int u, int p) {
  sz[u] = 1, in[u] = ++cnt, rev[in[u]] = u;
  for (auto x : v[u])
    dfs(x, u), sz[u] += sz[x];
  out[u] = cnt;
}

int t[100100]; // Binary indexed tree
// Function to update BIT
void update(int b, int x) {
  while (b <= n)
    t[b] += x, b += b & -b;
}

// Find kth element in ordered sequence using BIT
array<int, 2> find_kth(int k) {
  int re1 = 0, re2 = 0;
  for (int i = 19; i >= 0; i--)
    if (re1 + (1 << i) <= n && re2 + t[re1 + (1 << i)] < k)
      re1 += 1 << i, re2 += t[re1];
  return {re1 + 1, re2};
}

// Find kth element in subtree
int find_kth_subtree(int u, int k) {
  // Use persistent data structure for range query
  return find_kth_pst(r[in[u] - 1], r[max(0, in[child[u]] - 1)],
                      r[out[child[u]]], r[out[u]], k);
}

// DFS traversal and update subtree information
void dfs2(int u) {
  update(u, sz[u]); // Update size of current node

  for (auto [k, id] : query[u]) {
    auto [L, M] = find_kth(k); // Get the L and M values from the BIT
    int K = k - M;
    int y = find_kth_subtree(L, K); // Find k-th element in the subtree
    ans[id] = 1ll * (u - 1) * n * n + 1ll * (L - 1) * n + y - 1; // Compute final answer
  }

  for (auto x : v[u]) {
    update(u, -sz[x]); // Remove contribution of child subtree
    child[u] = x;
    dfs2(x); // Recurse into child subtree
    update(u, sz[x]); // Add back child subtree
  }

  update(u, -sz[u]);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  int root = 0;
  for (int i = 1; i <= n; i++) {
    int p;
    cin >> p;
    if (p)
      v[p].push_back(i); // Add to adjacency list
    else
      root = i; // Determine the root node
  }
  dfs(root, 0); // Perform DFS traversal

  r[0] = build_pst(); // Initialize persistent segment tree
  for (int i = 1; i <= n; i++)
    r[i] = update_pst(r[i - 1], rev[i]); // Set up persistent versions

  for (int i = 1; i <= m; i++) {
    ll q;
    cin >> q;
    query[(q - 1) / n + 1].push_back({int((q - 1) % n + 1), i}); // Group queries
  }
  dfs2(root); // Process all the queries

  for (int i = 1; i <= m; i++)
    cout << ans[i] << "\n"; // Output answers

  return 0;
}


// https://github.com/VaHiX/codeForces/