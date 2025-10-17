// Problem: CF 2049 F - MEX OR Mania
// https://codeforces.com/contest/2049/problem/F

/*
F. MEX OR Mania
Time Complexity: O(n q log n) average case due to operations on multiset and merge logic
Space Complexity: O(n) for storing arrays and data structures

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) with path compression
- Multiset for maintaining lengths of good segments
- Bitwise operations with prefix checks
- Dynamic update processing over multiple thresholds

This solution maintains a structure where we process updates on array elements,
and for each update, calculates the length of longest "good" subarray.

A good subarray is one where:
mex(subarray) - OR(subarray) = 1
*/

#include <time.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <utility>
#include <vector>

using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
const int MAXN = 1e5 + 5;
int n, q, t, qx[MAXN], qy[MAXN], fa[MAXN];
int siz[MAXN], le[MAXN], ri[MAXN], uniq[MAXN], ans[MAXN];
ll a[MAXN], b[MAXN];
vector<int> cnt[MAXN];
multiset<int> good;
#define length(x) (ri[x] - le[x] + 1)
inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y)
    return;
  if (siz[x] < siz[y])
    swap(x, y);
  fa[y] = x;
  siz[x] += siz[y];
  int lenx = length(x);
  int leny = length(y);
  int maxv = 1 << t;
  if (uniq[x] == maxv)
    good.erase(good.lower_bound(lenx));
  if (uniq[y] == maxv)
    good.erase(good.lower_bound(leny));
  // Merge count arrays and update unique element counts
  if (!cnt[y].empty()) {
    for (int i = 0; i < maxv; i++) {
      if (!cnt[x][i] && cnt[y][i])
        uniq[x]++;
      cnt[x][i] += cnt[y][i];
    }
  } else if (!cnt[x].empty()) {
    for (int i = le[y]; i <= ri[y]; i++) {
      if (cnt[x][b[i]]++ == 0)
        uniq[x]++;
    }
  } else if (ri[x] - le[x] + 1 + ri[y] - le[y] + 1 >= (1 << t)) {
    cnt[x].resize(maxv);
    for (int i = le[x]; i <= ri[x]; i++) {
      if (cnt[x][b[i]]++ == 0)
        uniq[x]++;
    }
    for (int i = le[y]; i <= ri[y]; i++) {
      if (cnt[x][b[i]]++ == 0)
        uniq[x]++;
    }
  }
  le[x] = min(le[x], le[y]);
  ri[x] = max(ri[x], ri[y]);
  if (uniq[x] == maxv)
    good.insert(length(x));
}
void solve() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= q; i++)
    cin >> qx[i] >> qy[i], a[qx[i]] += qy[i], ans[i] = 0;
  // Iterate over all thresholds (t from 17 down to 0) 
  for (t = 17; t >= 0; t--)
    if ((1 << t) <= n) {
      int maxv = 1 << t;
      good.clear();
      for (int i = 1; i <= n; i++) {
        b[i] = a[i], fa[i] = le[i] = ri[i] = i, uniq[i] = 0, cnt[i].clear();
        siz[i] = 1;
        if (t == 0 && b[i] == 0) {
          good.insert(1);
          cnt[i].push_back(1), uniq[i] = 1;
        }
      }
      // Union adjacent elements which are less than (1 << t)
      for (int i = 1; i < n; i++)
        if (b[i] < (1 << t) && b[i + 1] < (1 << t))
          merge(i, i + 1);
      // Process queries backwards
      for (int i = q; i >= 1; i--) {
        if (!good.empty())
          ans[i] = max(ans[i], *(--good.end()));
        if (b[qx[i]] < (1 << t)) {
          int k = find(qx[i]);
          if (!cnt[k].empty() && --cnt[k][b[qx[i]]] == 0) {
            if (uniq[k]-- == (1 << t))
              good.erase(good.lower_bound(ri[k] - le[k] + 1));
          }
        }
        b[qx[i]] -= qy[i];
        // After update, re-evaluate neighbors and perform merges
        if (b[qx[i]] < (1 << t)) {
          int k = find(qx[i]);
          if (t == 0 && cnt[k].empty())
            cnt[k].push_back(0);
          if (!cnt[k].empty() && cnt[k][b[qx[i]]]++ == 0) {
            if (++uniq[k] == (1 << t))
              good.insert(ri[k] - le[k] + 1);
          }
          if (1 < qx[i] && b[qx[i] - 1] < (1 << t))
            merge(qx[i] - 1, qx[i]);
          if (qx[i] < n && b[qx[i] + 1] < (1 << t))
            merge(qx[i], qx[i] + 1);
        }
      }
    }
  for (int i = 1; i <= q; i++)
    cout << ans[i] << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  int _;
  cin >> _;
  while (_--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/