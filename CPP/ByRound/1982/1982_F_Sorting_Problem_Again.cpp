// Problem: CF 1982 F - Sorting Problem Again
// https://codeforces.com/contest/1982/problem/F

/*
Algorithm/Technique:
- This code uses a Segment Tree to efficiently maintain and query properties of an array.
- The segment tree stores:
  - Minimum and maximum values in each segment (mn, mx)
  - Whether a segment is sorted (flag)
- To find the minimal subarray to sort:
  - We use two queries:
    - query1: finds the leftmost position where we can start sorting to make the whole array sorted.
    - query2: finds the rightmost position where we can end sorting to make the whole array sorted.
- Time Complexity: O(n log n) per query due to segment tree operations.
- Space Complexity: O(n) for storing the segment tree and array.

Time Complexity: O(n log n) per query
Space Complexity: O(n)
*/

#include <algorithm>
#include <iostream>

#define N 500005
#pragma GCC optimize("inline")
using namespace std;
int T, n, q, a[N];
#define lid (id << 1)
#define rid (lid | 1)
int mn[N << 2], mx[N << 2], flag[N << 2];

// Build segment tree with min, max and sorted flag for each node
inline void build(int id, int l, int r) {
  if (l == r) {
    mn[id] = mx[id] = a[l], flag[id] = 1;
    return;
  }
  int m = (l + r) >> 1;
  build(lid, l, m), build(rid, m + 1, r);
  mn[id] = min(mn[lid], mn[rid]);
  mx[id] = max(mx[lid], mx[rid]);
  flag[id] = flag[lid] && flag[rid] && (a[m] <= a[m + 1]);
}

// Modify a value in the segment tree
inline void modify(int id, int l, int r, int i, int x) {
  if (l == r) {
    mn[id] = mx[id] = x;
    return;
  }
  int m = (l + r) >> 1;
  if (i <= m)
    modify(lid, l, m, i, x);
  else
    modify(rid, m + 1, r, i, x);
  mn[id] = min(mn[lid], mn[rid]), mx[id] = max(mx[lid], mx[rid]);
  flag[id] = flag[lid] && flag[rid] && (a[m] <= a[m + 1]);
}

// Find leftmost index in sorted subarray for which the array can be sorted
inline int query1(int id, int l, int r, int y) {
  if (l == r)
    return l;
  int m = (l + r) >> 1;
  if (flag[lid] && a[m] <= min(y, mn[rid]))
    return query1(rid, m + 1, r, y);
  return query1(lid, l, m, min(y, mn[rid]));
}

// Find rightmost index in sorted subarray for which the array can be sorted
inline int query2(int id, int l, int r, int x) {
  if (l == r)
    return l;
  int m = (l + r) >> 1;
  if (flag[rid] && max(x, mx[lid]) <= a[m + 1])
    return query2(lid, l, m, x);
  return query2(rid, m + 1, r, max(x, mx[lid]));
}

// Solve function to determine the minimal subarray to sort
inline void solve() {
  if (flag[1])
    return void(cout << "-1 -1\n");
  int x = query1(1, 1, n, 0x3f3f3f3f), y = query2(1, 1, n, -0x3f3f3f3f);
  cout << x << ' ' << y << '\n';
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n, a[0] = -0x3f3f3f3f, a[n + 1] = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    cin >> q, build(1, 1, n), solve();
    while (q--) {
      int p, x;
      cin >> p >> x, a[p] = x, modify(1, 1, n, p, x);
      solve();
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/