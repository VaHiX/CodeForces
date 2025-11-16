// Problem: CF 1793 F - Rebrending
// https://codeforces.com/contest/1793/problem/F

/*
Algorithm: Segment Tree with Coordinate Compression and Merge Sort Tree
Time Complexity: O(n log n + q log^2 n)
Space Complexity: O(n log n)

This code solves the problem of finding the minimum absolute difference 
between any two elements in a given range [l, r] for multiple queries.

The approach uses a merge sort tree where each node stores a sorted list 
of elements in its range. For each query, we find the minimum difference 
by checking neighbors in the sorted list and using the segment tree to 
efficiently process updates and queries.
*/

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
const int N = 1e6 + 6;
namespace fast_io {
char ib[N], ob[N + 66], stk[66];
int it, ed, ot, f, t, c;
#define gc                                                                     \
  (it == ed && (ed = (it = 0) + fread(ib, 1, N, stdin), it == ed)) ? EOF       \
                                                                   : ib[it++]
template <typename _Tp> inline void read(_Tp &x) {
  for (c = gc, f = 0; c < 48; c = gc)
    if (c == '-')
      f = !f;
  for (x = 0; c > 47; x = x * 10 + (48 ^ c), c = gc)
    ;
  if (f)
    x = -x;
}
template <typename _Tp, typename... _tps> inline void read(_Tp &x, _tps &...y) {
  read(x), read(y...);
}
inline void write(int x) {
  for (t = 0; x > 9; stk[++t] = 48 ^ (x % 10), x /= 10)
    ;
  for (ob[ot++] = 48 ^ (x % 10); t; ob[ot++] = stk[t--])
    ;
  ob[ot++] = '\n';
  if (ot > N)
    fwrite(ob, 1, ot, stdout), ot = 0;
}
inline void fls() { fwrite(ob, 1, ot, stdout), ot = 0; }
} // namespace fast_io
using fast_io::read;
using fast_io::write;
int n, a[N], m, t[N][2], de[N];
int dp[N], mxdp, cnt, ans[N];
#define ls t[x][0]
#define rs t[x][1]
vector<pair<int, int>> lk[N];
int A[22][N];
int build(int l, int r, int d) {
  int x = ++cnt;
  de[x] = d, dp[x] = 2e9;
  if (l == r) {
    A[d][l] = a[l];
    return x;
  }
  int md = l + r >> 1;
  ls = build(l, md, d + 1), rs = build(md + 1, r, d + 1);
  merge(A[d + 1] + l, A[d + 1] + md + 1, A[d + 1] + md + 1, A[d + 1] + r + 1,
        A[d] + l);
  return x;
}
void ins(int x, int l, int r, int R) {
  if (r < R) {
    int p = lower_bound(A[de[x]] + l, A[de[x]] + r + 1, a[R]) - A[de[x]];
    if (p <= r)
      dp[x] = min(dp[x], A[de[x]][p] - a[R]);
    if (--p >= l)
      dp[x] = min(dp[x], a[R] - A[de[x]][p]);
    if (dp[x] >= mxdp)
      return;
  }
  if (l < r) {
    int md = l + r >> 1;
    if (md < R)
      ins(rs, md + 1, r, R);
    ins(ls, l, md, R), dp[x] = min(dp[ls], dp[rs]);
  }
  mxdp = min(mxdp, dp[x]);
}
void qry(int x, int l, int r, int L) {
  if (l >= L)
    mxdp = min(mxdp, dp[x]);
  else {
    int md = l + r >> 1;
    if (ls && L <= md)
      qry(ls, l, md, L);
    if (rs)
      qry(rs, md + 1, r, L);
  }
}
int main() {
  read(n, m);
  int i, x, y, l, r;
  for (i = 1; i <= n; ++i)
    read(a[i]);
  for (x = 1; x <= m; ++x) {
    read(l, r);
    lk[r].emplace_back(l, x);
  }
  build(1, n, 1);
  for (x = 2; x <= n; ++x) {
    mxdp = 2e9, ins(1, 1, n, x);
    for (auto at : lk[x]) {
      mxdp = 2e9, qry(1, 1, n, at.first);
      ans[at.second] = mxdp;
    }
  }
  for (x = 1; x <= m; ++x)
    printf("%d\n", ans[x]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/