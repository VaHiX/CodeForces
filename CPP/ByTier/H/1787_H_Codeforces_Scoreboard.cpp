// Problem: CF 1787 H - Codeforces Scoreboard
// https://codeforces.com/contest/1787/problem/H

// Enhanced/Documented: Codeforces - Scoreboard related solution
// This file implements a specialized implicit treap (randomized BST)
// with lazy propagation. It is used to maintain an ordered set of
// elements where each node stores a base value `d[id]` and a lazy
// addition `flg[id]` that is propagated to children.
//
// High-level idea:
// - Input consists of triples (k, b, a). The algorithm sorts these by k
//   (descending) and then inserts them into an ordered structure.
// - The treap supports splitting by a custom predicate that depends on
//   the current accumulated K and the rank (position) inside the tree.
// - Merging and splitting allow the code to move a suffix/prefix of the
//   structure, apply lazy updates, and insert new nodes while keeping
//   track of totals. Finally a DFS collects final contributions.

#include <bits/stdc++.h>
using namespace std;

const int o = 2e5 + 10; // array sizing (safely above constraints)

// Global state for the treap and computation
int T, n, rt; // T = test cases, n = number of items, rt = treap root id
int ls[o], rs[o], s[o], w[o]; // left/right child, subtree size, random priority
long long K, ans, d[o], flg[o],
    tot; // K=current k, ans=result, d=base values, flg=lazy add
mt19937 rnd(time(0));

// Input triples stored as info {k, b, a}
struct info {
  int k, b, a;
} z[o];

// Sort by decreasing k (we process larger k first)
inline bool cmp(info A, info B) { return A.k > B.k; }

// Apply an additive value `val` to node `id` (accumulate both base and lazy)
inline void ad(int id, long long val) {
  if (id)
    d[id] += val, flg[id] += val;
}

// Push lazy value to children
inline void pushdown(int id) {
  ad(ls[id], flg[id]);
  ad(rs[id], flg[id]);
  flg[id] = 0;
}

// Recompute subtree size for node id
inline void update(int id) {
  if (id)
    s[id] = s[ls[id]] + 1 + s[rs[id]];
}

// Split treap `id` into x (left) and y (right) such that all nodes
// in x satisfy the predicate: d[node] + K * (rank) >= val is false
// The function uses `rnk` as the number of nodes already to the left
// and compares with the threshold `val`. This is a custom split by
// computed key rather than by explicit stored key.
void split(int id, int rnk, long long val, int &x, int &y) {
  if (!id) {
    x = y = 0;
    return;
  }
  pushdown(id);
  // If the computed key for this node is strictly less than val,
  // then this node and its left subtree belong to the right part `y`.
  if (d[id] + K * (rnk + s[ls[id]] + 1) < val)
    y = id, split(ls[id], rnk, val, x, ls[y]);
  else
    x = id, split(rs[id], rnk + s[ls[id]] + 1, val, rs[x], y);
  update(id);
}

// Merge two treaps x and y into id (standard randomized treap merge)
void merge(int &id, int x, int y) {
  if (!x || !y) {
    id = x | y;
    return;
  }
  pushdown(x);
  pushdown(y);
  if (w[x] < w[y])
    id = x, merge(rs[id], rs[x], y);
  else
    id = y, merge(ls[id], x, ls[y]);
  update(id);
}

// In-order traversal that accumulates contributions into `ans`.
// `tot` keeps a running prefix sum of d[node] as we visit nodes in order.
void dfs(int nw) {
  pushdown(nw);
  if (ls[nw])
    dfs(ls[nw]);
  ans = max(ans, tot += d[nw]);
  if (rs[nw])
    dfs(rs[nw]);
}

int main() {
  // For each test case we read n triples, randomize priorities and
  // build/modify the treap by splitting/merging while applying lazy updates.
  for (scanf("%d", &T); T--; printf("%lld\n", ans), tot = rt = 0) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      // Read input and initialize node i: random priority, size=1,
      // clear d/flg and child pointers.
      scanf("%d%d%d", &z[i].k, &z[i].b, &z[i].a),
          w[i] = rnd(), s[i] = 1, d[i] = flg[i] = ls[i] = rs[i] = 0;
    // Process triples sorted by descending k
    sort(z + 1, z + n + 1, cmp);
    for (int i = 1, x, y; i <= n; ++i) {
      // Add immediate a contribution to the total
      tot += z[i].a;
      K = z[i].k; // current slope parameter for split predicate
      // Split the treap by threshold (b - a). Left part x contains nodes
      // whose adjusted key is >= threshold; right part y are those < threshold
      split(rt, 0, z[i].b - z[i].a, x, y);
      // Apply lazy subtraction -K to the right part
      ad(y, -K);
      // Initialize node i's base value d[i] with formula depending on x size
      d[i] = z[i].b - K * (s[x] + 1) - z[i].a;
      // Insert node i by merging: x + {i} + y
      merge(x, x, i);
      merge(rt, x, y);
    }
    // After all insertions, compute maximum prefix-sum over inorder traversal
    ans = tot;
    dfs(rt);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/