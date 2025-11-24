// Problem: CF 1672 I - PermutationForces
// https://codeforces.com/contest/1672/problem/I
 
/*
Algorithm/Techniques: Segment Trees with Lazy Propagation, Binary Indexed Trees
(Fenwick Trees), Set Data Structure, Simulated Greedy Approach
 
Time Complexity: O(n * log^2(n)) - Each operation on segment tree and BIT takes
O(log n) time, and we perform at most O(n) such operations. Space Complexity:
O(n) - For segment trees, BITs, and auxiliary data structures.
 
This solution uses two segment trees and two BITs to simulate the process of
removing elements from a permutation with minimum required strength 's'. It
maintains the minimum strength needed at each step by using lazy propagation and
efficient range queries.
 
SOLUTION APPROACH:
The problem requires us to greedily remove elements from a permutation, choosing
at each step the element that minimizes the maximum "cost" incurred. The cost at
each removal step depends on the relative position of the element and how many
elements have already been removed around it.
 
The key insight is to process the permutation in two directions (left-prefix and
right-suffix) using mirrored structures L and R. Each structure maintains:
- A segment tree (with lazy propagation) tracking min cost and position.
- A Fenwick tree (BIT) to quickly count already-removed elements in ranges.
- A set of "active" (non-removed) positions.
 
At each iteration, we find the minimum-cost element from either direction,
output that cost, and remove the element, updating the structures accordingly.
*/
 
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
 
#define For(i, a, b) for (int i = (a); i <= (b); ++i)
#define Rep(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
#define fi first
#define se second
#define mkp make_pair
typedef pair<int, int> pii;
#define maxn 500005
#define inf 0x3f3f3f3f
 
int n, p[maxn];
 
// Binary Indexed Tree (Fenwick Tree) for efficient range sum queries
struct bit {
  int tr[maxn];
  // Add value y to position x
  void add(int x, int y) {
    for (; x <= n + 1; x += x & -x)
      tr[x] += y;
  }
  // Query prefix sum from 1 to x
  int ask(int x) {
    int s = 0;
    for (; x; x ^= x & -x)
      s += tr[x];
    return s;
  }
};
// Segment Tree with Lazy Propagation for efficient range updates and queries.
// Stores pairs (value, index) to track the minimum in each node.
struct segt {
  pii t[maxn << 2];   // Segment tree nodes (min value, index)
  int tag[maxn << 2]; // Lazy propagation tags for range additions
 
  // Build tree with initial values (infinity, position)
  void build(int p, int l, int r) {
    t[p] = mkp(inf, l);
    if (l == r)
      return;
    int mid = l + r >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
  }
 
  // Update parent based on children
  void up(int p) { t[p] = min(t[p << 1], t[p << 1 | 1]); }
 
  // Apply lazy tag: add value v to node
  void pt(int p, int v) { tag[p] += v, t[p].fi += v; }
 
  // Push lazy tag down to children
  void down(int p) {
    if (tag[p])
      pt(p << 1, tag[p]), pt(p << 1 | 1, tag[p]), tag[p] = 0;
  }
 
  // Add value v to range [nl, nr]
  void add(int p, int l, int r, int nl, int nr, int v) {
    if (l >= nl && r <= nr)
      return pt(p, v);
    int mid = l + r >> 1;
    down(p);
    if (nl <= mid)
      add(p << 1, l, mid, nl, nr, v);
    if (nr > mid)
      add(p << 1 | 1, mid + 1, r, nl, nr, v);
    up(p);
  }
 
  // Update single position to a specific value
  void upd(int p, int l, int r, int x, pii y) {
    if (l == r)
      return tag[p] = 0, t[p] = y, void();
    int mid = l + r >> 1;
    down(p);
    x <= mid ? upd(p << 1, l, mid, x, y) : upd(p << 1 | 1, mid + 1, r, x, y);
    up(p);
  }
 
  // Query minimum in range [ql, qr]
  pii ask(int p, int l, int r, int ql, int qr) {
    if (l >= ql && r <= qr)
      return t[p];
    int mid = l + r >> 1;
    down(p);
    pii res = mkp(inf, inf);
    if (ql <= mid)
      res = min(res, ask(p << 1, l, mid, ql, qr));
    if (qr > mid)
      res = min(res, ask(p << 1 | 1, mid + 1, r, ql, qr));
    return res;
  }
 
  // Public interfaces (wrapper functions for cleaner calls)
  void add(int l, int r, int v) { add(1, 1, n, l, r, v); }
  pii ask(int l, int r) { return ask(1, 1, n, l, r); }
  void upd(int x, pii y) { upd(1, 1, n, x, y); }
};
// Direction-specific data structure (mirrored for L and R directions).
// Simulates removal process and maintains active positions and costs.
struct {
  segt t0, t1; // Two segment trees for different cost functions
  bit s0, s1;  // Two Fenwick trees for counting removed elements
  set<pii> in; // Set of "in" elements (position, index)
  set<int> s;  // Set of active (non-removed) positions
  int x[maxn]; // Transformed position array
 
  // Get minimum cost and corresponding position
  pii get() { return t0.t[1]; }
 
  // Initialize the structure based on input permutation
  void init() {
    t0.build(1, 0, n + 1), t1.build(1, 0, n + 1);
    s.insert(0), s.insert(n + 1);
    x[n + 1] = n + 1;
    int mn = inf;
    // Process elements from right to left, maintaining min value seen so far
    Rep(i, n, 1) if (x[i]) {
      mn = min(mn, x[i]);
      if (mn == x[i])
        // Element is part of the minimum chain
        s.insert(i), in.insert(mkp(x[i], i)), t0.upd(i, mkp(x[i] - i, i));
      else
        // Element is beyond the minimum chain
        t1.upd(i, mkp(x[i], i));
    }
  }
 
  // Mark element y as removed; x is its transformed position
  void add(int y, int x) {
    auto it = in.lower_bound(mkp(y, -1));
    if (it != in.end())
      t0.add(it->se, x, -1);    // Decrease cost in segment tree
    s0.add(x, 1), s1.add(y, 1); // Update Fenwick trees
  }
 
  // Count how many elements in range (u, x[u]) have been removed
  int cnt(int u) { return s1.ask(x[u]) - s0.ask(u); }
 
  // Add position u to the "in" set and update segment tree costs
  void addin(int u) {
    s.insert(u), in.insert(mkp(x[u], u));
    t1.upd(u, mkp(inf, u));
    t0.upd(u, mkp(x[u] - u - cnt(u), u));
  }
 
  // Remove position u from the active set and promote candidates from t1 to t0
  void del(int u) {
    s0.add(u, 1), s1.add(x[u], 1);
    auto it = s.lower_bound(u);
    int ql = *prev(it), qr = *next(it); // Get neighbors of u in the active set
    s.erase(it), in.erase(mkp(x[u], u));
    t0.upd(u, mkp(inf, u));
    // Check and promote elements from range [ql, qr] if their costs became
    // viable
    while (ql <= qr) {
      pii t = t1.ask(ql, qr);
      if (t.fi > x[qr])
        break;
      addin(ql = t.se);
    }
  }
} L, R; // Left and right direction structures
int main() {
  cin >> n;
  // Transform the permutation into two views: L for left half, R for right half
  For(i, 1, n) {
    cin >> p[i];
    if (p[i] >= i)
      L.x[i] = p[i]; // Left view: elements where p[i] >= i
    else
      R.x[n - i + 1] =
          n + 1 - p[i]; // Right view: mirrored transform for other elements
  }
 
  // Initialize both directional structures
  L.init(), R.init();
 
  int res = 0;
  // Greedy removal: at each step, pick the minimum-cost element from either L
  // or R
  For(i, 1, n) {
    pii resl = L.get(), resr = R.get(), now = min(resl, resr);
    res = max(res, now.fi); // Update global maximum cost
    int u = now.se;         // Element to remove
 
    // Remove from chosen direction and sync the other direction
    if (now == resl)
      R.add(n + 1 - p[u], n + 1 - u), L.del(u);
    else
      L.add(p[n + 1 - u], n + 1 - u), R.del(u);
  }
 
  cout << res;
  return 0;
}
 
// https://github.com/VaHiX/CodeForces/