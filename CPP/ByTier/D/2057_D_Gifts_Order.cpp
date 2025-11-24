// Problem: CF 2057 D - Gifts Order
// https://codeforces.com/contest/2057/problem/D

/*
Purpose: This code solves the "Gifts Order" problem, which involves finding the maximum convenience value
         for selecting a contiguous subsegment of sweaters. The convenience is defined as:
         max(a[l], ..., a[r]) - min(a[l], ..., a[r]) - (r - l).
         It uses a segment tree to efficiently compute the maximum convenience and update values after changes.

Algorithms/Techniques: Segment Tree with range queries and point updates.
Time Complexity: O(n * log n) for building the segment tree, O(log n) for each update/query.
Space Complexity: O(n) for the segment tree storage.

The segment tree maintains for each node:
- xp: max(a[i] + i) in the range
- xm: max(a[i] - i) in the range
- np: min(a[i] + i) in the range
- nm: min(a[i] - i) in the range
- ans: maximum convenience in the range

The key insight to optimize the computation:
For a subsegment from l to r, the convenience = max - min - (r - l)
Rewriting: (max - l) - (min - l) - (r - l) = (max - l) - (min - l) - (r - l)
Which can be expressed as:
(max - l) + (l - min) - (r - l) = (max - l) + (l - min) - (r - l)
This reduces to:
(max - l) - (min - l) - (r - l) = (a[r] - r) - (a[l] - l) - (r - l)

So we define:
- a[i] + i -> contributes to max in the range
- a[i] - i -> contributes to min in the range

Then, for any range l to r, convenience = max(a[i] + i) - min(a[i] - i) - (r - l)
But the segment tree stores the max and min values directly from expressions:
a[i] + i and a[i] - i
The update and query logic computes max(a[i] - i) - min(a[i] + i) and vice versa
*/

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 2e5 + 2;
int T, n, q, a[N];
struct node {
  int xp, xm, np, nm, ans;
  void init(int i) { xp = np = a[i] + i, xm = nm = a[i] - i, ans = 0; }
} t[N * 4];
void pushup(int x) {
  node &s = t[x], &l = t[x * 2], &r = t[x * 2 + 1];
  s.xp = max(l.xp, r.xp);
  s.xm = max(l.xm, r.xm);
  s.np = min(l.np, r.np);
  s.nm = min(l.nm, r.nm);
  s.ans = max({l.ans, r.ans, r.xm - l.nm, l.xp - r.np});
}
void build(int x, int l, int r) {
  if (l == r)
    return t[x].init(l);
  int mid = (l + r) >> 1;
  build(x * 2, l, mid);
  build(x * 2 + 1, mid + 1, r);
  pushup(x);
}
void modify(int x, int l, int r, int L) {
  if (l == r)
    return t[x].init(l);
  int mid = (l + r) >> 1;
  L > mid ? modify(x * 2 + 1, mid + 1, r, L) : modify(x * 2, l, mid, L);
  pushup(x);
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    build(1, 1, n);
    cout << t[1].ans << '\n';
    for (int x; q--;) {
      cin >> x;
      cin >> a[x];
      modify(1, 1, n, x);
      cout << t[1].ans << '\n';
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/