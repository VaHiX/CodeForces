// Problem: CF 1832 F - Zombies
// https://codeforces.com/contest/1832/problem/F

/*
Algorithm: Dynamic Programming with Optimized Range Queries
Time Complexity: O(n^2 * log(n) + n^2 * log^2(n)) where n is the number of entrances
Space Complexity: O(n^2 + n * log(n)) for storing DP states, segments, and BITs.

This solution uses dynamic programming with segment trees and coordinate compression
to find the maximum number of zombies that can enter the base after optimally
assigning generators to entrances and choosing their activation times. The approach
involves:
1. Coordinate compression for efficient range updates and queries
2. Segment tree with lazy propagation (BIT) for range updates
3. Dynamic programming with optimal substructure and range optimization
4. Divide and conquer optimization for the DP transitions
*/

#include <stdio.h>
#include <algorithm>
#include <array>
#include <utility>
#include <vector>

#define forn(i, n) for (int i = 0; i < int(n); i++)
using namespace std;
struct seg {
  int l, r;
};
int n;
vector<long long> dp_before, dp_cur;
vector<vector<long long>> bst;
void compute(int l, int r, int optl, int optr) {
  if (l > r)
    return;
  int mid = (l + r) / 2;
  pair<long long, int> best = {-1, -1};
  for (int k = optl; k <= min(mid, optr); k++)
    best = max(best, {(k ? dp_before[k - 1] : 0) + bst[k][mid], k});
  dp_cur[mid] = best.first;
  int opt = best.second;
  compute(l, mid - 1, optl, opt);
  compute(mid + 1, r, opt, optr);
}
struct node {
  long long c0;
  int c1;
};
vector<node> f;
void update(int x, int a, int b) {
  for (int i = x; i < int(f.size()); i |= i + 1) {
    f[i].c0 += b;
    f[i].c1 += a;
  }
}
void update(int l, int r, int a, int b) {
  update(l, a, b);
  update(r, -a, -b);
}
long long get(int pos, int x) {
  long long res = 0;
  for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
    res += f[i].c0 + f[i].c1 * 1ll * pos;
  return res;
}
int main() {
  int k, x, m;
  scanf("%d%d%d%d", &n, &k, &x, &m);
  vector<seg> a(n);
  forn(i, n) scanf("%d%d", &a[i].l, &a[i].r);
  sort(a.begin(), a.end(),
       [&](const seg &a, const seg &b) { return a.l + a.r < b.l + b.r; });
  vector<int> pos;
  forn(i, n) {
    pos.push_back(a[i].l);
    pos.push_back(a[i].r - m);
  }
  sort(pos.begin(), pos.end());
  pos.resize(unique(pos.begin(), pos.end()) - pos.begin());
  int cds = pos.size();
  vector<array<int, 4>> npos(n);
  forn(i, n) {
    npos[i][0] = lower_bound(pos.begin(), pos.end(), a[i].l - m) - pos.begin();
    npos[i][1] = lower_bound(pos.begin(), pos.end(), a[i].l) - pos.begin();
    npos[i][2] = lower_bound(pos.begin(), pos.end(), a[i].r - m) - pos.begin();
    npos[i][3] = lower_bound(pos.begin(), pos.end(), a[i].r) - pos.begin();
  }
  vector<long long> pr(n + 1);
  forn(i, n) pr[i + 1] = pr[i] + x - (m + a[i].r - a[i].l);
  auto upd = [&](int i) {
    if (a[i].r - a[i].l >= m) {
      update(npos[i][0], npos[i][1], 1, m - a[i].l);
      update(npos[i][1], npos[i][2], 0, m);
      update(npos[i][2], npos[i][3], -1, a[i].r);
    } else {
      update(npos[i][0], npos[i][2], 1, m - a[i].l);
      update(npos[i][2], npos[i][1], 0, a[i].r - a[i].l);
      update(npos[i][1], npos[i][3], -1, a[i].r);
    }
  };
  bst.resize(n, vector<long long>(n, -1));
  vector<vector<int>> opt(n, vector<int>(n));
  forn(r, n) for (int l = r; l >= 0; --l) {
    if (l == r)
      f.assign(cds, {0, 0});
    upd(l);
    int L = (l == r ? (l == 0 ? 0 : opt[l - 1][l - 1]) : opt[l][r - 1]);
    int R = (l == r ? int(pos.size()) - 1 : opt[l + 1][r]);
    for (int k = L; k <= R; ++k) {
      long long cur = pr[r + 1] - pr[l] + get(pos[k], k);
      if (cur > bst[l][r]) {
        bst[l][r] = cur;
        opt[l][r] = k;
      }
    }
  }
  dp_before.resize(n);
  dp_cur.resize(n);
  for (int i = 0; i < n; i++)
    dp_before[i] = bst[0][i];
  for (int i = 1; i < k; i++) {
    compute(0, n - 1, 0, n - 1);
    dp_before = dp_cur;
  }
  printf("%lld\n", dp_before[n - 1]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/