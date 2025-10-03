// Problem: CF 2075 F - Beautiful Sequence Returns
// https://codeforces.com/contest/2075/problem/F

/*
F. Beautiful Sequence Returns
time limit per test2 seconds
memory limit per test256 megabytes

Problem Description:
Given an array a of integers, find the length of the longest beautiful subsequence.
A sequence is beautiful if:
- For every element except the first one, there exists an element to its left which is smaller than it.
- For every element except the last one, there exists an element to its right which is larger than it.

Approach:
1. Preprocess arrays to compute:
   - pmn: indices of elements that are minimum from left to right
   - smx: indices of elements that are maximum from right to left
2. Compute prefix/suffix information for each index.
3. Use a segment tree with range updates and point queries to track the optimal answer efficiently.

Time Complexity:
- Overall time complexity is O(n log n) per test case due to preprocessing, sorting, and operations on segment trees.
- Space complexity is O(n) used by arrays, vectors, and segment tree storage.

Data Structures Used:
- Segment Tree with lazy propagation-like updates (interval range updates).
- Vectors for storing prefix/suffix information.
- Arrays for temporary storage during indexing and computation.

Algorithms/Techniques:
- Preprocessing arrays with monotonic properties
- Sorting with custom comparator
- Segment Tree with point update and range max query operations
- Two-pointer technique with indexing
*/
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
namespace qG {
const int sz = 1 << 18;
char buf[sz], *S, *T;
inline char g() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, sz, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
struct R {
  R &operator>>(int &x) {
    x = 0;
    char c = g();
    while (isdigit(c))
      x = x * 10 + (c - '0'), c = g();
    return *this;
  }
} r;
} // namespace qG
namespace qP {
const int sz = 1 << 16;
char buf[sz], *S = buf;
struct W {
  W &operator<<(int x) {
    static int s[6];
    int tp = 0;
    while (x) {
      s[tp++] = x % 10;
      x /= 10;
    }
    while (tp)
      *S++ = '0' + s[--tp];
    *S++ = '\n';
    return *this;
  }
} w;
struct E {
  ~E() { fwrite(buf, 1, S - buf, stdout); }
} e;
} // namespace qP
#define cin qG::r
#define cout qP::w
#define il inline
#define pb push_back
#define vi vector<int>
#define a3 array<int, 3>
#define all(x) begin(x), end(x)
using namespace std;
struct sgt {
  int sz;
  struct nd {
    int sum, pmx;
  };
  vector<nd> v;
  il void up(int pa) {
    int lp = pa << 1;
    auto &lc = v[lp], &rc = v[lp | 1];
    v[pa] = {lc.sum + rc.sum, max(lc.pmx, lc.sum + rc.pmx)};
    pa >>= 1;
    if (pa)
      up(pa);
  }
  void u2(int p, int x) {
    v[p].sum += x;
    v[p].pmx = max(v[p].sum, 0);
    up(p >> 1);
  }
  void upd(a3 &cur) {
    auto &[L, R, x] = cur;
    u2(L + sz, x);
    u2(R + sz, -x);
  }
  void ini(int n) {
    int e = ceil(log2(n));
    sz = 1 << e;
    v.resize(sz << 1);
  }
} tr;
void go() {
  int n;
  cin >> n;
  vi a(n);
  for (auto &x : a)
    cin >> x;
  if (is_sorted(all(a), greater<int>())) {
    cout << 1;
    return;
  }
  vi pmn{0};
  pmn.reserve(n);
  for (int i = 1; i < n; i++)
    if (a[i] < a[pmn.back()])
      pmn.pb(i);
  vi smx{n - 1};
  smx.reserve(n);
  for (int i = n - 2; i >= 0; i--)
    if (a[i] > a[smx.back()])
      smx.pb(i);
  reverse(all(smx));
  int psz = pmn.size(), ssz = smx.size();
  vi L1(n), R1(n), L2(n), R2(n);
  int cur = psz - 1;
  for (int i = n - 1; i >= 0; i--) {
    if (pmn[cur] >= i)
      cur--;
    R1[i] = cur;
  }
  vi idx(n);
  iota(all(idx), 0);
  sort(all(idx), [&](int i, int j) { return a[i] > a[j]; });
  cur = 0;
  for (int &i : idx) {
    if (cur < psz && a[pmn[cur]] >= a[i])
      cur++;
    L1[i] = cur;
  }
  cur = ssz - 1;
  reverse(all(idx));
  for (int &i : idx) {
    if (cur >= 0 && a[smx[cur]] <= a[i])
      cur--;
    R2[i] = cur;
  }
  cur = 0;
  for (int i = 0; i < n; i++) {
    if (smx[cur] <= i)
      cur++;
    L2[i] = cur;
  }
  int tt = 0;
  vector<a3> vr(n << 1);
  vi nx(n << 1), hd(psz + 1);
  for (int i = 0; i < n; i++)
    if (L1[i] <= R1[i] && L2[i] <= R2[i]) {
      vr[++tt] = {L2[i], R2[i] + 1, 1};
      nx[tt] = hd[L1[i]];
      hd[L1[i]] = tt;
      vr[++tt] = {L2[i], R2[i] + 1, -1};
      nx[tt] = hd[R1[i] + 1];
      hd[R1[i] + 1] = tt;
    }
  tr.ini(ssz + 1);
  int ans = 0;
  for (int i = 0; i <= psz; i++)
    if (hd[i]) {
      for (int e = hd[i]; e; e = nx[e])
        tr.upd(vr[e]);
      ans = max(ans, tr.v[1].pmx);
    }
  cout << ans + 2;
}
int main() {
  int T;
  cin >> T;
  while (T--)
    go();
}


// https://github.com/VaHiX/codeForces/