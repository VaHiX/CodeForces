// Problem: CF 1919 F2 - Wine Factory (Hard Version)
// https://codeforces.com/contest/1919/problem/F2

/*
 * Problem: F2. Wine Factory (Hard Version)
 * Algorithm: Segment Tree with Lazy Propagation
 * Time Complexity: O((n + q) * log n)
 * Space Complexity: O(n)
 *
 * This solution uses a segment tree to efficiently handle updates and queries
 * on the wine production process. Each node in the segment tree maintains
 * information about the flow of water and wine production through the pipeline.
 * The key insight is that for each water tower, we compute:
 * - ans: total wine produced so far
 * - out: remaining water that can flow out to next tower
 * - mxans: maximum possible wine that can be produced from current segment
 * - mxout: maximum flow out from current segment
 */

#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <iostream>

#define For(i, j, k) for (int i = (j); i <= (k); i++)
#define ForD(i, j, k) for (int i = (j); i >= (k); i--)
#define int long long
#define endl '\n'
using namespace std;
bool Mbe;
const int N = 5e5 + 5;
int a[N], b[N], c[N];
struct Node {
  int ans, out, mxans, mxout;
  Node operator+(const Node &o) const {
    Node res;
    // Combine answers: current answer + right subtree answer + flow between segments
    res.ans = ans + o.ans + min(out, o.mxans);
    // Combine out flows: right subtree out flow + valid flow from current to right
    res.out = o.out + max(0ll, min(out - o.mxans, o.mxout));
    // Max answer for combined segment: current max + flow to right subtree
    res.mxans = mxans + min(o.mxans, min(mxout, o.mxans - min(out, o.mxans)));
    // Max out for combined segment: bounded flow constraints
    res.mxout = min(o.mxout - max(0ll, min(out - o.mxans, o.mxout)),
                    mxout - min(mxout, o.mxans - min(out, o.mxans)));
    return res;
  }
} tr[N << 2];
void build(int u, int l, int r) {
  if (l == r)
    // Initialize leaf node with values for that tower
    return tr[u] = {min(a[l], b[l]), min(c[l], a[l] - min(a[l], b[l])),
                    b[l] - min(a[l], b[l]),
                    c[l] - min(c[l], a[l] - min(a[l], b[l]))},
           void();
  int mid = (l + r) >> 1;
  build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
  tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
void modify(int u, int l, int r, int p) {
  if (l == r)
    // Update leaf node with new values
    return tr[u] = {min(a[l], b[l]), min(c[l], a[l] - min(a[l], b[l])),
                    b[l] - min(a[l], b[l]),
                    c[l] - min(c[l], a[l] - min(a[l], b[l]))},
           void();
  int mid = (l + r) >> 1;
  if (p <= mid)
    modify(u << 1, l, mid, p);
  else
    modify(u << 1 | 1, mid + 1, r, p);
  tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
void solve() {
  int n, m;
  cin >> n >> m;
  For(i, 1, n) cin >> a[i];
  For(i, 1, n) cin >> b[i];
  For(i, 1, n - 1) cin >> c[i];
  c[n] = 0;
  build(1, 1, n);
  while (m--) {
    int p, x, y, z;
    cin >> p >> x >> y >> z;
    a[p] = x, b[p] = y, c[p] = z;
    modify(1, 1, n, p);
    cout << tr[1].ans << endl;
  }
}
bool Med;
signed main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int _ = 1;
  while (_--)
    solve();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/