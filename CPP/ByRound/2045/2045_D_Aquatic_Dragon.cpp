// Problem: CF 2045 D - Aquatic Dragon
// https://codeforces.com/contest/2045/problem/D

/*
 * Problem: D. Aquatic Dragon
 * 
 * Algorithm/Techniques:
 * - Dynamic Programming with Segment Tree and Fenwick Tree
 * - Optimal strategy involves choosing between swimming, flying, and walking
 * - Segment tree is used to maintain minimum costs over intervals
 * - Fenwick tree is used to track visited islands for tunnel usage
 * 
 * Time Complexity: O(N * log N)
 * Space Complexity: O(N * log N)
 * 
 * The approach uses a combination of segment tree and fenwick tree to efficiently 
 * maintain and query the minimum time required to reach each position with different 
 * stamina levels, considering the constraints of swimming, flying, and walking through tunnels.
 */
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
#define mp make_pair
#define fr first
#define sc second
const int MXN = 2e5;
const long long INF = 1e18;
struct Segtree {
  int l, r;
  long long mn, lazy;
  Segtree *lef, *rig;
  void bld(int lb, int rb) {
    l = lb;
    r = rb;
    mn = INF;
    lazy = 0;
    if (l < r) {
      int mid = (l + r) / 2;
      lef = new Segtree;
      rig = new Segtree;
      lef->bld(l, mid);
      rig->bld(mid + 1, r);
    }
  }
  inline void propa() {
    lef->mn += lazy;
    lef->lazy += lazy;
    rig->mn += lazy;
    rig->lazy += lazy;
    lazy = 0;
  }
  void ins(int x, long long w) {
    if (x < l || r < x)
      ;
    else if (x <= l && r <= x) {
      mn = w;
    } else {
      propa();
      lef->ins(x, w);
      rig->ins(x, w);
      mn = min(lef->mn, rig->mn);
    }
  }
  void upd(int lb, int rb, long long w) {
    if (rb < l || r < lb)
      ;
    else if (lb <= l && r <= rb) {
      mn += w;
      lazy += w;
    } else {
      propa();
      lef->upd(lb, rb, w);
      rig->upd(lb, rb, w);
      mn = min(lef->mn, rig->mn);
    }
  }
  long long qry(int lb, int rb) {
    if (rb < l || r < lb) {
      return INF;
    } else if (lb <= l && r <= rb) {
      return mn;
    } else {
      propa();
      return min(lef->qry(lb, rb), rig->qry(lb, rb));
    }
  }
};
int N, fenwick[MXN + 69];
inline void fenwickUpd(int x, int w) {
  for (int fi = x; fi <= N; fi += fi & -fi) {
    fenwick[fi] += w;
  }
}
inline int fenwickQry(int lb, int rb) {
  int sum = 0;
  for (int fi = rb; fi > 0; fi -= fi & -fi) {
    sum += fenwick[fi];
  }
  for (int fi = lb - 1; fi > 0; fi -= fi & -fi) {
    sum -= fenwick[fi];
  }
  return sum;
}
int main() {
  int D, Ts, Tf, Tw;
  scanf("%d%d%d%d%d", &N, &D, &Ts, &Tf, &Tw);
  if (Tf <= Ts) {
    printf("%lld\n", (long long)Tf * (N - 1));
    return 0;
  }
  int P[N + 69];
  for (int i = 1; i <= N; i++) {
    scanf("%d", P + i);
  }
  long long pref[N + 69];
  pref[0] = 0;
  for (int i = 1; i <= N; i++) {
    pref[i] = pref[i - 1] + P[i];
  }
  vector<pair<long long, pair<int, int>>> queries;
  vector<pair<long long, int>> updates;
  for (int i = 1; i <= N; i++) {
    queries.push_back({pref[i - 1] - (long long)D * i, {i, 0}});
    queries.push_back({pref[i] - (long long)D * i, {i, 1}});
    updates.push_back({pref[i - 1] - (long long)D * i, i});
  }
  sort(queries.begin(), queries.end());
  sort(updates.begin(), updates.end());
  Segtree segtree;
  segtree.bld(1, N * 2);
  int ud = 0, qr2 = 0;
  for (int qr = 0; qr < (int)queries.size(); qr++) {
    long long w;
    int p, e;
    w = queries[qr].fr;
    p = queries[qr].sc.fr;
    e = queries[qr].sc.sc;
    while (ud < (int)updates.size()) {
      long long w2;
      int p2;
      w2 = updates[ud].fr;
      p2 = updates[ud].sc;
      if (w2 >= w) {
        break;
      }
      segtree.upd(p2 * 2 + 1, N * 2, Tw * 2);
      fenwickUpd(p2, 1);
      ud++;
    }
    while (true) {
      long long w2;
      int p2, e2;
      w2 = queries[qr2].fr;
      p2 = queries[qr2].sc.fr;
      e2 = queries[qr2].sc.sc;
      if (w2 + D > w) {
        break;
      }
      segtree.ins(p2 * 2 - 1 + e2, INF);
      qr2++;
    }
    long long mn = segtree.qry(p * 2 + 1, N * 2) - (long long)Ts * p + Tf -
                   (long long)Tw * 2 * fenwickQry(1, p - 1);
    if (pref[N - 1] - (long long)D * N >= w) {
      mn = min(mn, (long long)Ts * (N - p) +
                       (long long)Tw * 2 * fenwickQry(p, N - 1));
    }
    if (pref[N] - (long long)D * N >= w) {
      mn = min(mn, (long long)Ts * (N - p) +
                       (long long)Tw * 2 * (fenwickQry(p, N - 1) + 1));
    }
    if (p == 1 && e == 0) {
      printf("%lld\n", mn);
      return 0;
    }
    segtree.ins(p * 2 - 1 + e, mn + (long long)Ts * (p - 1) +
                                   (long long)Tw * 2 * fenwickQry(1, p - 1));
  }
}


// https://github.com/VaHiX/CodeForces/