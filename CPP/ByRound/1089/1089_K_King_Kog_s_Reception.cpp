/*
 * Problem URL : https://codeforces.com/contest/1089/problem/K
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 7;
struct SegmentTree {
  struct Node {
    ll val, sum;
    void up(const Node &lc, const Node &rc) {
      sum = lc.sum + rc.sum;
      val = max(lc.val + rc.sum, rc.val);
    }
  } v[N * 4];
  void set(int p, ll val, int l = 1, int r = N, int rt = 1) {
    if (l >= r) {
      v[rt].sum = val, v[rt].val = val ? l + val : 0;
      return;
    }
    int m = l + r >> 1;
    if (p > m)
      set(p, val, m + 1, r, rt << 1 | 1);
    else
      set(p, val, l, m, rt << 1);
    v[rt].up(v[rt << 1], v[rt << 1 | 1]);
  }
  Node ask(int p, int q, int l = 1, int r = N, int rt = 1) {
    if (p <= l && r <= q)
      return v[rt];
    int m = l + r >> 1;
    if (m >= q)
      return ask(p, q, l, m, rt << 1);
    if (m < p)
      return ask(p, q, m + 1, r, rt << 1 | 1);
    return v[0].up(ask(p, q, l, m, rt << 1), ask(p, q, m + 1, r, rt << 1 | 1)),
           v[0];
  }
} t;
char s[9];
int n, a[N];
int main() {
  scanf("%d", &n);
  for (int i = 1, y; i <= n; ++i) {
    scanf("%s%d", s, &a[i]);
    if (s[0] == '+') {
      scanf("%d", &y);
      t.set(a[i], y);
    } else if (s[0] == '-')
      t.set(a[a[i]], 0);
    else
      printf("%lld\n", max(t.ask(1, a[i]).val - a[i], 0LL));
  }
}