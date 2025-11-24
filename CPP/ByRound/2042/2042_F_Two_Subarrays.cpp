// Problem: CF 2042 F - Two Subarrays
// https://codeforces.com/contest/2042/problem/F

/*
F. Two Subarrays
Algorithms/Techniques: Segment Tree with Range Maximum Subarray Query, Lazy Propagation
Time Complexity: O(n log n + q log n)
Space Complexity: O(n)

The problem requires handling updates and queries on two arrays a and b.
Each query asks for the maximum sum of costs from two non-overlapping subarrays within a range [l,r].
The cost of a subarray [l,r] is defined as: sum(a[l] to a[r]) + sum(b[l] to b[r]).
We use a segment tree that maintains information about:
- Maximum subarray sum
- Left and right maximum sums
- Total sum in the segment

Each node of the segment tree holds information needed for combining two segments
to compute maximal sum over non-overlapping subarrays.
*/

#include <algorithm>
#include <iostream>

#define int long long
#define pb push_back
#define SZ(x) (int)(x).size()
using namespace std;
const int N = 2e5 + 5, INF = 1e18;
int n, a[N], b[N], m, op, x, y;

struct node {
  int s, l, r, m, lm, rm, lr, mm;
  // s: total sum in the segment [l,r]
  // l: maximum prefix sum from left to right
  // r: maximum suffix sum from left to right
  // m: maximum subarray sum within current interval
  // lm: max sum starting from left end
  // rm: max sum ending at right end
  // lr: sum from left to right (for combining)
  // mm: max total cost for two non-overlapping subarrays in this segment
  inline node operator+(node x) {
    return {s + x.s,
            max(l, s + x.l),          // max prefix of current
            max(x.r, x.s + r),        // max suffix of current
            max({m, x.m, r + x.l}),   // best subarray in combination
            max({s + x.lm, l + x.m, lr + x.l, lm}),  // left max ending or extending
            max({x.s + rm, x.r + m, x.lr + r, x.rm}),// right max starting or extending
            max({s + x.lr, l + x.r, lr + x.s}),            // cross combining sums
            max({x.mm, r + x.lm, m + x.m, rm + x.l, mm})}; // best two non-overlapping in current segment
  }
};

struct SGT {
#define ls (rt << 1)
#define rs (rt << 1 | 1)
  node t[N << 2];
  
  inline node mkn(int x) {
    // Create a new leaf node for position x with a[x] as base cost and b[x] as balance
    return {a[x], a[x] + b[x], a[x] + b[x], a[x] + b[x] * 2,
            -INF, -INF,        -INF,        -INF};
  }
  
  inline void psu(int rt) { 
    // Push up operation to recompute parent from children
    t[rt] = t[ls] + t[rs]; 
  }
  
  void bld(int rt = 1, int l = 1, int r = n) {
    // Build the segment tree recursively
    if (l == r) {
      t[rt] = mkn(l);
      return;
    }
    int mid = (l + r) >> 1;
    bld(ls, l, mid), bld(rs, mid + 1, r);
    psu(rt);
  }
  
  void upd(int x, int rt = 1, int l = 1, int r = n) {
    // Update the value at index x
    if (l == r) {
      t[rt] = mkn(x);
      return;
    }
    int mid = (l + r) >> 1;
    x <= mid ? upd(x, ls, l, mid) : upd(x, rs, mid + 1, r);
    psu(rt);
  }
  
  node qry(int L, int R, int rt = 1, int l = 1, int r = n) {
    // Query range [L, R]
    if (l >= L && r <= R)
      return t[rt];
    int mid = (l + r) >> 1;
    if (R <= mid)
      return qry(L, R, ls, l, mid);
    if (L > mid)
      return qry(L, R, rs, mid + 1, r);
    return qry(L, R, ls, l, mid) + qry(L, R, rs, mid + 1, r);
  }
} T;

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++)
    cin >> b[i];
    
  T.bld(); // Build segment tree
  
  cin >> m;
  while (m--) {
    cin >> op >> x >> y;
    if (op == 1)
      a[x] = y, T.upd(x);        // Update array a
    if (op == 2)
      b[x] = y, T.upd(x);        // Update array b
    if (op == 3)
      cout << T.qry(x, y).mm << '\n';  // Query maximum sum of two non-overlapping subarrays
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/