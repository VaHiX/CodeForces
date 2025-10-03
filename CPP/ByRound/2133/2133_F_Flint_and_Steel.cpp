// Problem: CF 2133 F - Flint and Steel
// https://codeforces.com/contest/2133/problem/F

/*
F. Flint and Steel
Algorithms/Techniques: Segment Tree with Lazy Propagation, Dynamic Programming, Greedy Approach

Time Complexity: O(n log n) per test case due to sorting and segment tree operations
Space Complexity: O(n) for arrays and segment trees

Problem Description:
Steve needs to kill all creepers by detonating them in order such that each detonation kills all creepers within its explosive range.
We aim to find the minimum number of detonations needed to kill all creepers or determine impossibility.

The solution uses a greedy approach with dynamic programming:
1. Sort indices based on (position + explosive_power)
2. For each creeper in sorted order, determine the best previous creeper to detonate from
3. Use two segment trees to track valid detonation points efficiently:
   - One for point updates and queries in range [0, i-aa[i]]
   - Another for point updates and queries in range [i+aa[i], n-1]
4. Reconstruct the path using parent pointers stored in pp[]
5. Optimize output by reversing segments that form consecutive chains
*/

#include <stddef.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 500000;
const int N_ = 1 << 19;
const int INF = 0x3f3f3f3f;
int aa[N], ii[N], dp[N], pp[N], qu[N];
int st0[N_ << 1], st1[N_ << 1], n_;
void upd(int &i, int j) {
  if (j != -1 && (i == -1 || dp[i] > dp[j]))
    i = j;
}
void pul0(int i) {
  int l = i << 1, r = l ^ 1;
  st0[i] = st0[l], upd(st0[i], st0[r]);
}
void pul1(int i) {
  int l = i << 1, r = l ^ 1;
  st1[i] = st1[l], upd(st1[i], st1[r]);
}
void build(int n) {
  for (n_ = 1; n_ < n; n_ <<= 1)
    ;
  for (int i = 0; i < n_; i++)
    st0[i + n_] = st1[i + n_] = -1;
  for (int i = n_ - 1; i; i--)
    pul0(i), pul1(i);
}
void update0(int l, int r, int i) {
  for (l += n_, r += n_; l <= r; l >>= 1, r >>= 1) {
    if (l & 1)
      upd(st0[l++], i);
    if (!(r & 1))
      upd(st0[r--], i);
  }
}
int query0(int i) {
  int i_ = -1;
  for (i += n_; i; i >>= 1)
    upd(i_, st0[i]);
  return i_;
}
void update1(int i, int i_) {
  upd(st1[i += n_], i_);
  while (i >>= 1)
    pul1(i);
}
int query1(int l, int r) {
  int i_ = -1;
  for (l += n_, r += n_; l <= r; l >>= 1, r >>= 1) {
    if (l & 1)
      upd(i_, st1[l++]);
    if (!(r & 1))
      upd(i_, st1[r--]);
  }
  return i_;
}
int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
      cin >> aa[ii[i] = i];
    sort(ii, ii + n, [](int i, int j) { return i + aa[i] < j + aa[j]; });
    build(n);
    int i_ = -1;
    for (int h = 0; h < n; h++) {
      int i = ii[h], p = -1;
      if (aa[i] > i)
        p = i;
      else {
        upd(p, query0(i - aa[i]));
        upd(p, query1(i - aa[i] + 1, i));
      }
      if (p == -1)
        dp[i] = INF;
      else {
        dp[i] = p == i ? 1 : dp[p] + 1;
        pp[i] = p;
        if (i + aa[i] < n) {
          update0(i, i + aa[i] - 1, i);
          update1(i + aa[i], i);
        } else if (i_ == -1 || dp[i_] > dp[i])
          i_ = i;
      }
    }
    if (i_ == -1) {
      cout << "-1\n";
      continue;
    }
    int k = 0;
    for (int i = i_;; i = pp[i]) {
      qu[k++] = i;
      if (pp[i] == i)
        break;
    }
    reverse(qu, qu + k);
    for (int l = 0, r; l < k; l = r) {
      for (r = l + 1; r < k && qu[r - 1] + aa[qu[r - 1]] <= qu[r]; r++)
        ;
      reverse(qu + l, qu + r);
    }
    cout << k << '\n';
    while (k--)
      cout << qu[k] + 1 << ' ';
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/