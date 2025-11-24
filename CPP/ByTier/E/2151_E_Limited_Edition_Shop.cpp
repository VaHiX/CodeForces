// Problem: CF 2151 E - Limited Edition Shop
// https://codeforces.com/contest/2151/problem/E

/*
E. Limited Edition Shop

Algorithm: Segment Tree with Coordinate Compression + Dynamic Programming-like Process
Time Complexity: O(n log n) per test case
Space Complexity: O(n)

Approach:
- For each object in Alice's preference list, we determine the best sum of values she can get.
- We use a segment tree to maintain the maximum value sum that could be achieved up to some position.
- The idea is to simulate all possible selections of Alice's items, ensuring that Bob picks his items first from those not yet selected.
- For each item in Alice's preference list, we query what's the best sum so far among previously unselected items (in terms of Bob's order),
  then update accordingly.

Key observations:
1. We process Alice's list in order: for each element `a[i]`, we look at where this item stands in Bob's list.
2. Items appearing before the current one in Bob's sequence are already picked by Bob, so they cannot be taken by Alice.
3. Among remaining possible items from previous steps (those after the current item in Bob's sequence), we choose the best value sum possible with segment tree updates and queries.
*/
#include <stdio.h>
#include <algorithm>

#define int long long
using namespace std;
const int maxn = 2e5 + 10;
const int inf = 1e18;
int T, n;
int v[maxn], w[maxn], a[maxn], b[maxn], pos[maxn];
struct Segment_Tree {
  int l, r;
  int mx, lazy;
} t[maxn << 2];
inline void ipt() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; i++)
    scanf("%lld", &v[i]);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &b[i]);
    pos[b[i]] = i; // Precompute positions of Bob's preference
  }
}
inline void upd(int i) { t[i].mx = max(t[i << 1].mx, t[i << 1 | 1].mx); }
inline void build(int i, int l, int r) {
  t[i].l = l, t[i].r = r, t[i].mx = 0, t[i].lazy = 0;
  if (l == r) {
    if (l == 0)
      t[i].mx = 0; // Base case: zero index initialized to 0
    return;
  }
  int mid = l + r >> 1;
  build(i << 1, l, mid);
  build(i << 1 | 1, mid + 1, r);
  upd(i);
}
inline void modify(int i, int x) {
  t[i].mx += x;
  t[i].lazy += x;
}
inline void pushdown(int i) {
  if (t[i].lazy) {
    modify(i << 1, t[i].lazy);
    modify(i << 1 | 1, t[i].lazy);
    t[i].lazy = 0;
  }
}
inline void change(int i, int l, int r, int x) {
  if (t[i].l > r || t[i].r < l)
    return;
  if (l <= t[i].l && t[i].r <= r) { // Segment fully covered
    modify(i, x);
    return;
  }
  pushdown(i); // Propagate down before recursion
  change(i << 1, l, r, x);
  change(i << 1 | 1, l, r, x);
  upd(i);
}
inline void change_mx(int i, int l, int x) {
  if (t[i].l == t[i].r) { // Leaf node
    t[i].mx = max(t[i].mx, x); // Update maximum value stored
    return;
  }
  pushdown(i);
  int mid = t[i].l + t[i].r >> 1;
  if (l <= mid)
    change_mx(i << 1, l, x);
  else
    change_mx(i << 1 | 1, l, x);
  upd(i);
}
inline int query(int i, int l, int r) {
  if (t[i].l > r || t[i].r < l)
    return -inf; // Out of bounds
  if (l <= t[i].l && t[i].r <= r) // Fully within range
    return t[i].mx;
  pushdown(i); // Push lazy updates before querying subtrees
  int p = max(query(i << 1, l, r), query(i << 1 | 1, l, r));
  return p;
}
inline void solve() {
  for (int i = 1; i <= n; i++) {
    int p = query(1, 0, pos[a[i]]); // Query max value achievable up to position in Bob's list
    change(1, 0, pos[a[i]] - 1, v[a[i]]); // Add this item to the set of available items (modify segment)
    change_mx(1, pos[a[i]], p); // Update max value at current index in the tree
  }
  printf("%lld\n", t[1].mx);
}
signed main() {
  scanf("%lld", &T);
  while (T--) {
    ipt();
    build(1, 0, n); // Initialize segment tree
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/