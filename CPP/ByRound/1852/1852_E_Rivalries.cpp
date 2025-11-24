// Problem: CF 1852 E - Rivalries
// https://codeforces.com/contest/1852/problem/E

/*
Algorithm: This code solves the problem of finding a rival array b to array a such that the sum of b is maximized, while preserving the "power" of all subarrays. The approach uses segment trees and careful processing to determine which elements can be increased while maintaining equality in the power of every subarray.

Time Complexity: O(n log n) per test case due to sorting, segment tree operations, and iterative processing.
Space Complexity: O(n) for storing arrays and segment tree structures.
*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
char *p1, *p2, buf[1048577];
#define gc                                                                     \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
template <typename T> inline void Read(T &x) {
  x = 0;
  char ch = gc;
  while (!isdigit(ch))
    ch = gc;
  while (isdigit(ch))
    x = (x << 3) + (x << 1) + (ch ^ 48), ch = gc;
}
typedef long long ll;
typedef pair<int, ll> pii;
const int maxn = 1e5 + 5;
const ll inf = 1e18;
bool ban[maxn];
int a[maxn], b[maxn], val[maxn], sz;
int L[maxn], R[maxn], low[maxn];
ll pre[maxn], suf[maxn], pre2[maxn], pre3[maxn];
vector<int> vec[maxn];
#define ls k << 1
#define rs k << 1 | 1
struct segtree {
  int mx[maxn << 2], l[maxn << 2], r[maxn << 2];
  void build(int k, int ld, int rd) {
    l[k] = ld, r[k] = rd, mx[k] = 0;
    if (ld == rd)
      return;
    int mid = (ld + rd) >> 1;
    build(ls, ld, mid);
    build(rs, mid + 1, rd);
  }
  void update(int k, int x, int d) {
    if (l[k] == r[k]) {
      mx[k] = max(mx[k], d);
      return;
    }
    int mid = (l[k] + r[k]) >> 1;
    if (x <= mid)
      update(ls, x, d);
    else
      update(rs, x, d);
    mx[k] = max(mx[ls], mx[rs]);
  }
  int query(int k, int L, int R) {
    if (L <= l[k] && r[k] <= R)
      return mx[k];
    int mid = (l[k] + r[k]) >> 1, ans = 0;
    if (L <= mid)
      ans = max(ans, query(ls, L, R));
    if (R > mid)
      ans = max(ans, query(rs, L, R));
    return ans;
  }
} T;
void work() {
  int n;
  cin >> n;
  sz = 0;
  T.build(1, 1, n);
  for (int i = 1; i <= n; i++)
    cin >> a[i], b[++sz] = a[i], vec[i].clear(), ban[i] = val[i] = 0;
  sort(b + 1, b + sz + 1);
  sz = unique(b + 1, b + sz + 1) - b - 1;
  b[0] = 0;
  for (int i = 1; i <= sz; i++)
    L[i] = n + 1, R[i] = 0;
  ban[n + 1] = 0;
  for (int i = 1; i <= n; i++) {
    a[i] = lower_bound(b + 1, b + sz + 1, a[i]) - b;
    L[a[i]] = min(L[a[i]], i);
    R[a[i]] = max(R[a[i]], i);
  }
  for (int i = 1; i <= sz; i++)
    if (L[i] <= R[i])
      vec[L[i]].emplace_back(i);
  for (int i = n; i; i--)
    for (int id : vec[i]) {
      if (T.query(1, i, R[id]) < id) {
        ban[L[id]] = ban[R[id]] = 1;
        val[L[id]] = val[R[id]] = id;
        T.update(1, R[id], id);
      }
    }
  T.build(1, 1, n);
  for (int i = 1; i <= n; i++) {
    if (ban[i])
      for (int id : vec[i])
        T.update(1, R[id], id);
    else
      val[i] = T.query(1, i, n);
  }
  pre[0] = suf[n + 1] = inf;
  for (int i = 1; i <= n; i++)
    pre[i] = min(pre[i - 1], (ban[i] ? inf : b[val[i]]));
  for (int i = n; i; i--)
    suf[i] = min(suf[i + 1], (ban[i] ? inf : b[val[i]]));
  for (int i = 0; i <= sz; i++)
    pre2[i] = pre3[i] = 0;
  for (int i = 1; i <= n; i++)
    if (!ban[i])
      pre2[val[i]]++, pre3[val[i]] += b[val[i]];
  for (int i = 1; i <= sz; i++)
    pre2[i] += pre2[i - 1], pre3[i] += pre3[i - 1];
  int lst = 0;
  for (int i = 1; i <= sz; i++) {
    if (!ban[L[i]] || L[i] > R[i])
      continue;
    low[i] = (b[i] == b[lst] + 1 ? low[lst] : b[i] - 1), lst = i;
  }
  ll ans = 0;
  int ansp = 0, ap2 = 0;
  for (int i = 1; i <= n; i++)
    if (!val[i])
      ans = -inf;
  for (int i = 1; i <= sz; i++) {
    if (!ban[L[i]] || L[i] > R[i])
      continue;
    int x = low[i];
    if (!x)
      continue;
    int pos = upper_bound(b + 1, b + sz + 1, x) - b - 1;
    ll con = (ll)x * pre2[pos] - pre3[pos];
    if (pre[L[i] - 1] > x)
      con -= (pre[L[i] - 1] - x);
    if (suf[R[i] + 1] > x)
      con -= (suf[R[i] + 1] - x);
    if (ans <= con)
      ans = con, ansp = x, ap2 = i;
  }
  for (int i = 1; i <= n; i++)
    val[i] = b[val[i]];
  if (ansp) {
    for (int i = 1; i <= n; i++)
      if (!ban[i] && val[i] < ansp)
        val[i] = ansp;
    if (pre[L[ap2] - 1] > ansp) {
      for (int i = 1; i < L[ap2]; i++)
        if (pre[L[ap2] - 1] == val[i] && !ban[i]) {
          val[i] = ansp;
          break;
        }
    }
    if (suf[R[ap2] + 1] > ansp) {
      for (int i = n; i > R[ap2]; i--)
        if (suf[R[ap2] + 1] == val[i] && !ban[i]) {
          val[i] = ansp;
          break;
        }
    }
  }
  for (int i = 1; i <= n; i++)
    cout << val[i] << " ";
  cout << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/