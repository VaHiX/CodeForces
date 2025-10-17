// Problem: CF 2079 C - Dreaming Is Not Harmful
// https://codeforces.com/contest/2079/problem/C

// Flowerbox describing the code purpose
/*
Problem Description:
This solution computes the minimum number of days for each employee to become the CEO of a company,
given that they can cancel one other employee (reducing their competence to zero) and observe how
the company structure changes due to promotions.

Algorithms/Techniques:
1. Tree DFS traversal and Heavy-Light Decomposition (HLD) for efficient path queries.
2. Segment Tree with Lazy Propagation to track maximum values on paths from a node to root.
3. Topological ordering using set-based approach.
4. Path compression and optimization through virtual paths.

Time Complexity: O(N log N + Q log N)
Space Complexity: O(N)
*/

#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <set>

int N, Q, pa[500009], ta[500009], as[500009], v[500009], iv[500009], vi[500009],
    v2[500009], to[500009], nxt[500009], hd[500009], k, kk, t[500009],
    dfn[500009], top[500009], siz[500009], son[500009];

// Link node u to node v (undirected edge setup for adjacency list)
void l(int u, int v) {
  to[++k] = v;
  nxt[k] = hd[u];
  hd[u] = k;
}

// DFS to compute subtree sizes and heavy child
void dfs(int n, int f) {
  siz[n] = 1;
  for (int i = hd[n]; i; i = nxt[i]) {
    dfs(to[i], n); // Recursive call on children
    siz[n] += siz[to[i]]; // Add size of child subtree
    if (siz[son[n]] < siz[to[i]])
      son[n] = to[i]; // Update heavy child
  }
}

// DFS second pass: HLD preparation - assign top and dfn for each node
void dfs2(int n, int tp) {
  top[n] = tp; // Top of current chain in HLD
  dfn[n] = ++kk; // Assign DFS number
  if (son[n] == 0)
    return;
  dfs2(son[n], tp); // Recurse on heavy child
  for (int i = hd[n]; i; i = nxt[i]) {
    if (son[n] == to[i])
      continue;
    dfs2(to[i], to[i]); // Start new chain
  }
}

// Segment tree with lazy propagation
int sg[1200009], la[1200009];
#define ls (n << 1)
#define rs ((n << 1) | 1)
#define md ((l + r) >> 1)

// Query range max value in segment tree with lazy propagation
int qr(int n, int l, int r, int L, int R) {
  if (L <= l && r <= R)
    return sg[n];
  int as = 0;
  if (md >= L)
    as = std::max(as, qr(ls, l, md, L, R));
  if (R > md)
    as = std::max(as, qr(rs, md + 1, r, L, R));
  return as + la[n];
}

// Update range in segment tree with lazy propagation
void up(int n, int l, int r, int L, int R) {
  if (L <= l && r <= R) {
    la[n]++; // Increment lazy tag by 1
    sg[n]++; // Increment node value by 1
    return;
  }
  if (md >= L)
    up(ls, l, md, L, R);
  if (R > md)
    up(rs, md + 1, r, L, R);
  sg[n] = std::max(sg[ls], sg[rs]) + la[n]; // Propagate upward
}

signed main(void) {
  scanf("%d %d", &N, &Q);
  for (int i = 2; i <= N; i++) {
    scanf("%d", &pa[i]);
    ta[i] = pa[i];
    l(pa[i], i); // Build graph from parent to child
  }
  for (int i = 1; i <= N; i++) {
    scanf("%d", &v[i]);
    iv[v[i]] = i; // Map competence level back to employee id
  }

  // Topologically sort nodes in order of DFS (used in later processing)
  std::set<int> ss;
  ss.insert(v[1]);
  int ll = 0;
  while (!ss.empty()) {
    int a = *ss.rbegin(); // Get maximum competence level
    ss.erase(a);
    a = iv[a];
    t[++ll] = a; // Store in topological order
    for (int i = hd[a]; i; i = nxt[i])
      ss.insert(v[to[i]]); // Add children to queue
  }

  kk = 0;
  dfs(1, 0); // Compute subtree sizes and heavy child
  dfs2(1, 1); // Heavy light decomposition

  for (int i = 1; i <= N; i++) {
    int x = t[i], rr = N + 1, aa = 0;
    while (x) {
      if (rr - dfn[x] >= 2)
        aa = std::max(aa, qr(1, 1, N, dfn[x] + 1, rr - 1));
      up(1, 1, N, dfn[top[x]], dfn[x]); // Update segment tree for chain
      rr = dfn[top[x]];
      x = pa[top[x]]; // Jump to parent of current chain top
    }
    if (rr >= 2)
      aa = std::max(aa, qr(1, 1, N, 1, rr - 1));
    as[t[i]] = i - aa - 1; // Calculate final answer for that node
  }

  while (Q--) {
    int x;
    scanf("%d", &x);
    printf("%d ", as[x]); // Output precomputed results
  }
}


// https://github.com/VaHiX/codeForces/