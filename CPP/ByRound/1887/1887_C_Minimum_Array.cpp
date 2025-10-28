// Problem: CF 1887 C - Minimum Array
// https://codeforces.com/contest/1887/problem/C

/*
 * Problem: C. Minimum Array
 * 
 * Purpose: Given an array and a series of range update operations, 
 *          find the lexicographically smallest array that can be obtained 
 *          by applying any prefix of these operations.
 * 
 * Algorithm: Segment Tree with Lazy Propagation to track the effect of 
 *            updates efficiently. A binary search approach is used to find 
 *            the optimal prefix of operations that minimizes the lexicographical 
 *            value of the resulting array.
 * 
 * Time Complexity: O(n log n + q log n)
 * Space Complexity: O(n)
 * 
 * Techniques:
 * - Segment Tree with lazy propagation
 * - Binary search for finding the minimal lexicographical result
 * - Difference array technique for efficient range updates
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
#define il inline
#define ll long long
#define ps push_back
namespace FastIO {
const int LEN = 1 << 20;
char buf[LEN], obuf[LEN], *p1 = buf, *p2 = buf, *p3 = obuf;
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, LEN, stdin), p1 == p2)         \
       ? EOF                                                                   \
       : *p1++)
#define flush() (fwrite(obuf, 1, p3 - obuf, stdout), p3 = obuf)
#define putchar(x) (p3 - obuf == LEN ? flush(), *p3++ = x : *p3++ = x)
il void read(int &x) {
  char ch = getchar();
  bool fl = 0;
  x = 0;
  while (ch < '0' || ch > '9')
    fl = ch == '-', ch = getchar();
  while (ch >= '0' && ch <= '9')
    x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  if (fl)
    x = -x;
}
template <typename... T> il void read(int &x, T &...y) { read(x), read(y...); }
il void write(ll x) {
  short top = 0, stk[20];
  if (x < 0)
    putchar('-'), x = -x;
  do
    stk[top++] = x % 10, x /= 10;
  while (x);
  while (top)
    putchar(stk[--top] | 48);
  putchar(' ');
}
} // namespace FastIO
using namespace FastIO;
const int N = 5e5 + 5, M = 1e6 + 5;
int T, n, q, tmp, a[N], l[N], r[N], x[N];
ll b[N], val[M];
bool vis[M];
il void Build(int id = 1, int l = 1, int r = n) {
  vis[id] = 1, val[id] = 0;
  if (l == r)
    return;
  int mid = (l + r) >> 1, ls = mid << 1, rs = mid << 1 | 1;
  Build(ls, l, mid), Build(rs, mid + 1, r);
}
il void Clear(int id = 1, int l = 1, int r = n) {
  if (vis[id])
    return;
  vis[id] = 1, val[id] = 0;
  if (l == r)
    return;
  int mid = (l + r) >> 1, ls = mid << 1, rs = mid << 1 | 1;
  Clear(ls, l, mid), Clear(rs, mid + 1, r);
}
il void Update(int p, int x, int id = 1, int l = 1, int r = n) {
  if (l == r)
    return val[id] += x, vis[id] = !val[id], void();
  int mid = (l + r) >> 1, ls = mid << 1, rs = mid << 1 | 1;
  p <= mid ? Update(p, x, ls, l, mid) : Update(p, x, rs, mid + 1, r),
      vis[id] = vis[ls] && vis[rs];
}
il bool Query(int id = 1, int l = 1, int r = n) {
  if (vis[id])
    return 0;
  if (l == r)
    return val[id] < 0;
  int mid = (l + r) >> 1, ls = mid << 1, rs = mid << 1 | 1;
  return vis[ls] ? Query(rs, mid + 1, r) : Query(ls, l, mid);
}
il void Run() {
  read(n), Build(), tmp = 0;
  for (int i = 1; i <= n; i++)
    read(a[i]), b[i] = 0;
  read(q);
  for (int i = 1; i <= q; i++) {
    read(l[i], r[i], x[i]), Update(l[i], x[i]);
    if (r[i] < n)
      Update(r[i] + 1, -x[i]);
    if (Query())
      tmp = i, Clear();
  }
  for (int i = 1; i <= tmp; i++)
    b[l[i]] += x[i], b[r[i] + 1] -= x[i];
  for (int i = 1; i <= n; i++)
    b[i] += b[i - 1];
  for (int i = 1; i <= n; i++)
    write(a[i] + b[i]);
  putchar('\n');
}
int main() {
  for (read(T); T; T--)
    Run();
  flush();
}


// https://github.com/VaHiX/CodeForces/