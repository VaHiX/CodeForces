// Problem: CF 2029 G - Balanced Problem
// https://codeforces.com/contest/2029/problem/G

/*
G. Balanced Problem
Algorithms/Techniques: Dynamic Programming with Optimization using Pruning and Sliding Window Concepts

Time Complexity: O(n * V^2 + m * n + sum(V^2))
Space Complexity: O(V^2)

This problem involves maximizing the "beauty" of an array `a` (initially all zeros),
which is defined as the sum of values in array `c` at positions where `a[i] == v`.
Kevin is allowed to perform prefix/suffix additions to the array.
The goal is to compute the maximum beauty for each value from 1 to V after optimal operations.

Initial operations are processed to compute an initial state of array `a`
and then compressed into segments based on the same value.
Dynamic Programming with pruning is used where dp[i][j] represents the maximum
beauty achievable with prefix sum up to i and suffix sum up to j.

The algorithm uses two key principles:
1. Compression of operations: merging equal consecutive elements.
2. Sliding window / pruning optimization: not iterating through all states,
   but only when necessary (based on `prv` tracking the last time a value was updated).
*/

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <random>
#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
#define pb push_back
typedef long long ll;
typedef long double ld;
int n;
int m;
int V;
const int maxN = 2e5 + 10;
ll c[maxN];
const int maxP = 2005;
ll dp[maxP][maxP]; // dp[i][j] stores max beauty with prefix sum i and suffix sum j
ll d[maxN]; // stores number of operations performed up to index
int prv[maxP]; // used to track last update for each prefix/suffix sum
ll f[maxP];
mt19937 rnd(228);
inline void umax(ll &a, const ll b) { a = max(a, b); }
void solve() {
  cin >> n >> m >> V;
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
    d[i] = 0;
  }
  for (int i = 1; i <= m; i++) {
    char c;
    cin >> c;
    int x;
    cin >> x;
    if (c == 'L') { // Prefix update
      d[1] += 1;
      d[x + 1] -= 1;
    } else { // Suffix update
      d[x] += 1;
    }
  }
  int sz = 1; // size of compressed array
  for (int i = 1; i <= n; i++) {
    d[i] += d[i - 1]; // compute prefix sum of operations
  }
  for (int i = 2; i <= n; i++) {
    if (d[i] == d[sz]) { // If current value same as previous, merge
      c[sz] += c[i];
    } else {
      sz++;
      assert(sz <= i);
      d[sz] = d[i]; // otherwise update and move forward
      c[sz] = c[i];
    }
  }
  n = sz;
  for (int i = 0; i <= V; i++) {
    for (int j = 0; j <= V; j++) {
      dp[i][j] = -1e18; // Initialize with negative infinity
    }
  }
  for (int i = 0; i <= V; i++) {
    prv[i] = -1;
  }
  int op = 0; // tracking number of operations to avoid TLE
  for (int i = 1; i <= n; i++) {
    assert(op <= m + n); // sanity check on operation count
    if (d[i] <= V) { // Only process if value is <= V
      int mx = -1;
      for (int j = 0; j <= V; j++) {
        f[j] = -1e18; // initialize new temporary array
      }
      f[d[i]] = c[i]; // base case: current element can be directly added
      for (int x = d[i]; x >= 0; x--) { // iterate backward from d[i]
        if (mx < prv[x]) {
          ++op;
          mx = prv[x];
          for (int S = x; S + d[i] - x <= V; S++) { // inner loop to update only valid combinations
            umax(f[S + d[i] - x], dp[S][x] + c[i]);
          }
        }
      }
      mx = prv[d[i]];
      for (int x = d[i] + 1; x <= V; x++) { // forward iteration from d[i]
        if (mx < prv[x]) {
          ++op;
          mx = prv[x];
          for (int S = x; S <= V; S++) { // again, iterate valid states
            f[S] = max(f[S], dp[S][x] + c[i]);
          }
        }
      }
      prv[d[i]] = i; // update last operation index for current value
      for (int x = d[i]; x <= V; x++)
        dp[x][d[i]] = f[x]; // update DP matrix with temporary values
    }
  }
  ll mx = 0;
  for (int x = 0; x <= V; x++) {
    for (int y = 0; y <= V; y++) {
      umax(mx, dp[x][y]); // find global maximum
    }
    if (x != 0)
      cout << mx << " ";
  }
  cout << '\n';
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef DEBUG
  freopen("input.txt", "r", stdin);
#endif
  int tst = 10000;
  cin >> tst;
  while (tst--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/