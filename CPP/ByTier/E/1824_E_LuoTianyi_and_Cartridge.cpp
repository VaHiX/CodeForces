// Problem: CF 1824 E - LuoTianyi and Cartridge
// https://codeforces.com/contest/1824/problem/E

/*
 * Overview
 * --------
 * This solution computes the maximum possible value of i * f(i) over a
 * process where values are removed/merged as we sweep a parameter i from 1..N.
 * The algorithm maintains three segment trees (T1, T2, T3) to track different
 * classes of contributions, uses disjoint-set-union (DSU) to merge components,
 * and keeps multisets per component to quickly retrieve extremes.
 *
 * Key data-structures:
 * - DSU (fa[]) to merge components when edges are activated
 * - s[u]: multiset of values currently in component u
 * - ru[u], xo[u]: auxiliary counts/xor used to trigger component merges
 * - Three segment trees (T1/T2/T3) implemented as SGT to maintain weighted
 *   sums and k-th queries needed to compute f(i) efficiently
 *
 * High level flow:
 * 1. Populate initial values and add per-edge events to buckets G[c]
 * 2. Sweep i from 1..N, updating trees and merging components as edges occur
 * 3. After handling events at i, compute current f(i) via ask() and update
 *    answer = max(answer, i * f(i))
 *
 * Implementation notes:
 * - N is set to 2e5 (max value range). Arrays sized slightly larger for safety.
 * - Multisets provide O(log n) insert/delete and retrieval of largest element.
 * - DSU merges use small-to-large merging of multisets to keep complexity near
 *   O(n log^2 n) in practice.
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200000;  // maximum value to sweep over
int n, b[200100];      // n: number of initial elements; b[i]: values
vector<int> G[200100]; // G[c]: list of indices/events at sweep value c
int U[201000], V[200100], D[200100]; // edge endpoints and weight D
int fa[200100];                      // DSU parent
// DSU find with path compression
int F(int x) {
  if (x == fa[x])
    return x;
  return fa[x] = F(fa[x]);
}
// per-component multisets (store values present in component)
multiset<int> s[201000];
int ru[201000],
    xo[200010]; // ru: degree-like count, xo: xor of incident edge ids
struct SGT {
  ll su[800010];   // su[p]: weighted sum of values at this node
  int su2[801000]; // su2[p]: count of elements at this node

  // Point update: at position x, add z occurrences (adds x*z to sum, z to
  // count)
  inline void up(int p, int l, int r, int x, int z) {
    su[p] += x * z, su2[p] += z;
    if (l == r)
      return;
    int mid = (l + r) >> 1;
    if (x <= mid)
      up(p << 1, l, mid, x, z);
    else
      up(p << 1 | 1, mid + 1, r, x, z);
  }

  // Query: compute contribution of largest k values (by value) from segment
  // Returns the sum of the k largest values stored in this tree
  inline ll kth(int p, int l, int r, int k) {
    if (l == r)
      return 1ll * min(su2[p], k) * l;
    int mid = (l + r) >> 1;
    if (k <= su2[p << 1 | 1])
      return kth(p << 1 | 1, mid + 1, r, k);
    return su[p << 1 | 1] + kth(p << 1, l, mid, k - su2[p << 1 | 1]);
  }
} T1, T2, T3;
int O1, O2; // O1: count of active elements; O2: count of active edges
bool vi[201000];

// Update T1 and T3 when the max value in a component changes
// z is +1 to add or -1 to remove the contribution of value x
void gk(int x, int z) { T1.up(1, 1, N, x, -z), T3.up(1, 1, N, x, z); }

// Merge two DSU components u and v when edge with weight W becomes active
// Uses small-to-large for efficient multiset merging
void merge(int u, int v, int W) {
  u = F(u), v = F(v);
  if (u == v)
    return;
  // Small-to-large merging: always merge smaller into larger
  if (s[u].size() < s[v].size())
    swap(u, v);
  // Deactivate edge W in T2 (one fewer edge active at this weight)
  T2.up(1, 1, N, W, -1);
  O2--, fa[v] = u;
  // Remove tracked maxima from T1/T3 before merge
  if (ru[u] == 1 && !s[u].empty())
    gk(*(--s[u].end()), -1);
  if (ru[v] == 1 && !s[v].empty())
    gk(*(--s[v].end()), -1);
  // Update degree counts and xor for merged component
  ru[u] += ru[v] - 2, xo[u] ^= xo[v];
  // Merge multiset v into u
  for (int x : s[v])
    s[u].insert(x);
  // Re-add tracked maximum if component now has single endpoint
  if (ru[u] == 1 && !s[u].empty())
    gk(*(--s[u].end()), 1);
  // If merged component becomes empty with single endpoint, activate hidden
  // edge
  if (s[u].empty() && ru[u] == 1) {
    int o = xo[u];
    if (F(U[o]) != u)
      swap(U[o], V[o]);
    merge(U[o], V[o], D[o]);
  }
}

// Remove element z from the component containing x (used when element is
// deleted)
void dk(int x, int z) {
  x = F(x);
  // Remove tracked maximum before deletion
  if (ru[x] == 1)
    gk(*(--s[x].end()), -1);
  // Decrement count in T1
  T1.up(1, 1, N, z, -1);
  // Remove z from component's multiset
  s[x].erase(s[x].find(z));
  // Re-add tracked maximum if component still has single endpoint
  if (ru[x] == 1 && !s[x].empty())
    gk(*(--s[x].end()), 1);
  // If component becomes empty with single endpoint, activate hidden edge
  if (s[x].empty() && ru[x] == 1) {
    int o = xo[x];
    if (F(U[o]) != x)
      swap(U[o], V[o]);
    merge(U[o], V[o], D[o]);
  }
}

// Compute f(i) for current sweep value using contributions from T1, T2, T3
// e = number of top elements/edges to select based on active counts
// op = number of values currently tracked as component maxima in T3
ll ask() {
  int e = min(O1 - 1, O2), op = T3.su2[1];
  return T1.kth(1, 1, N, e + 1 - op) + T3.su[1] + T2.kth(1, 1, N, e);
}
int main() {
  // Read the number of elements
  scanf("%d", &n);
  O1 = n, O2 = n - 1; // Initialize active counts
  ll ans = 0;

  // Read positions: for each element i, read its "position" a and add i to G[a]
  // This groups elements by their position value
  for (int i = 1, a; i <= n; i++)
    scanf("%d", &a), G[a].push_back(i), fa[i] = i;

  // Read element weights b[i]; initialize T1 with these weights
  // Each element i starts as its own component with multiset {b[i]}
  for (int i = 1; i <= n; i++)
    scanf("%d", &b[i]), T1.up(1, 1, N, b[i], 1), s[i].insert(b[i]);

  // Precompute baseline answer from direct position-weight pairs
  for (int i = 1; i <= N; i++)
    for (int j : G[i])
      ans = max(ans, 1ll * i * b[j]);

  // Read edges: for each edge, read endpoints U[i], V[i], activation value c,
  // and weight D[i]
  for (int i = 1, c; i < n; i++) {
    scanf("%d%d%d%d", &U[i], &V[i], &c, &D[i]);
    // Increment degree counters and record edge id in xor for both endpoints
    ru[U[i]]++, ru[V[i]]++, xo[U[i]] ^= i, xo[V[i]] ^= i;
    // Add edge activation event to bucket G[c]; use index n+i to distinguish
    // from elements
    G[c].push_back(n + i);
    // Initialize T2 with edge weights (all edges active at start)
    T2.up(1, 1, N, D[i], 1);
  }

  // For each element component with degree 1 (exposed endpoint), track its max
  // value in T3
  for (int i = 1; i <= n; i++)
    if (ru[i] == 1)
      gk(*(--s[i].end()), 1);

  // Sweep over values i = 1..N
  for (int i = 1; i <= N; i++) {
    // Update answer with current f(i) multiplied by i
    ans = max(ans, 1ll * i * ask());

    // Process all events scheduled for value i
    for (int j : G[i]) {
      if (j <= n) {
        // Event is deletion of element j (j <= n means it's an original
        // element)
        O1--;
        dk(j, b[j]);
      } else {
        // Event is activation of edge (n+j corresponds to edge index j-n)
        merge(U[j - n], V[j - n], D[j - n]);
      }
    }

    // Stop if only 0 or 1 element remains (no more meaningful computation)
    if (O1 <= 1)
      break;
  }

  // Output the maximum answer found
  return printf("%lld", ans), 0;
}

// https://github.com/VaHiX/CodeForces/