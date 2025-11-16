// Problem: CF 1500 E - Subset Trick
// https://codeforces.com/contest/1500/problem/E

/*
 * Problem: E. Subset Trick
 * 
 * Approach:
 * This solution uses a segment tree with coordinate compression to efficiently
 * handle dynamic addition and removal of elements from a set, and to compute
 * the number of "unsuitable" integers x for the current set.
 * 
 * The key insight is that an integer x is unsuitable if there exists at least
 * one pair of subsets of the same size, such that one has sum <= x and the other
 * has sum > x. This means the illusionist cannot determine whether the sum is <= x
 * just by knowing the subset size.
 * 
 * We use coordinate compression on the elements of the set and build a segment tree
 * to maintain information about subsets of different sizes. The algorithm calculates
 * a value related to the difference in sums of subsets of certain sizes to determine
 * the number of unsuitable x values.
 * 
 * Time Complexity: O((n + q) * log(n + q) * log(max_element))
 * Space Complexity: O((n + q) * log(max_element))
 */

#include <stdio.h>
#include <algorithm>

#define ps(a) lower_bound(b + 1, b + t + 1, a) - b
typedef long long ll;
using namespace std;
int n, m, t = 0;
ll a[200010], b[400010];
struct opr {
  int t;
  ll a;
} q[200010];
struct dat {
  int c;
  ll s, si;
} tr[1600010];
dat operator+(dat a, dat b) {
  return {a.c + b.c, a.s + b.s, a.si + b.si + b.s * a.c};
}
void upd(int a, int l, int r, int t, int c) {
  if (l == r) {
    tr[t].c += c, tr[t].s += c * b[l];
    tr[t].si = tr[t].s * (tr[t].c + 1) / 2;
    return;
  }
  int mid = (l + r) >> 1;
  a <= mid ? upd(a, l, mid, t << 1, c) : upd(a, mid + 1, r, t << 1 | 1, c);
  tr[t] = tr[t << 1] + tr[t << 1 | 1];
}
dat qry(int l, int r, int t, int k) {
  if (l == r)
    return {k, k * b[l], k * b[l] * (k + 1) / 2};
  int mid = (l + r) >> 1;
  return tr[t << 1].c >= k
             ? qry(l, mid, t << 1, k)
             : tr[t << 1] + qry(mid + 1, r, t << 1 | 1, k - tr[t << 1].c);
}
ll f(int k) {
  return qry(1, t, 1, k + 1).s - (tr[1].s - qry(1, t, 1, tr[1].c - k).s);
}
ll qry() {
  if (!tr[1].c)
    return 0;
  int l = 0, r = (tr[1].c - 1) / 2, mid, k = r;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (f(mid) > 0)
      k = mid, l = mid + 1;
    else
      r = mid - 1;
  }
  dat p = qry(1, t, 1, k + 1), q = qry(1, t, 1, tr[1].c - k);
  ll res = 2 * (((k + 2) * p.s - p.si) -
                (tr[1].si - q.si - (tr[1].c - k) * (tr[1].s - q.s)));
  if (tr[1].c & 1)
    res -= max(f(tr[1].c / 2), 0ll);
  return tr[1].s - res;
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%lld", &a[i]), b[++t] = a[i];
  for (int i = 1; i <= m; i++)
    scanf("%d%lld", &q[i].t, &q[i].a), b[++t] = q[i].a;
  sort(b + 1, b + t + 1), t = unique(b + 1, b + t + 1) - b - 1;
  for (int i = 1; i <= n; i++)
    upd(ps(a[i]), 1, t, 1, 1);
  printf("%lld\n", qry());
  for (int i = 1; i <= m; i++) {
    upd(ps(q[i].a), 1, t, 1, q[i].t == 1 ? 1 : -1);
    printf("%lld\n", qry());
  }
}


// https://github.com/VaHiX/CodeForces/