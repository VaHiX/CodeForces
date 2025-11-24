// Problem: CF 2018 E2 - Complex Segments (Hard Version)
// https://codeforces.com/contest/2018/problem/E2

// Flowerbox Start: Problem Description & Complexity
/*
 * Problem Title: E2. Complex Segments (Hard Version)
 *
 * Purpose:
 * Given n segments on a line, find the maximum size of a subset that forms a "complex" set.
 * A set of segments is complex if it can be partitioned into subsets such that:
 * 1. All subsets have the same size.
 * 2. Two segments intersect if and only if they are in the same subset.
 *
 * Algorithms/Techniques Used:
 * - Coordinate compression
 * - Dynamic Segment Tree / DSU (Disjoint Set Union)
 * - Binary search over answer
 * - Sweep line technique with events
 *
 * Time Complexity: O(n log n log n)
 * Space Complexity: O(n)
 */
// Flowerbox End

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#pragma GCC optimize("Ofast")
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define rep1(i, n) for (int i = 1; i < (n); ++i)
#define rep1n(i, n) for (int i = 1; i <= (n); ++i)
#define repr(i, n) for (int i = (n) - 1; i >= 0; --i)
#define pb push_back
#define eb emplace_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define each(x, a) for (auto &x : a)
#define ar array
#define vec vector
#define range(i, n) rep(i, n)
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using str = string;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pair<int, int>>;
using vvi = vector<vi>;
int Bit(int mask, int b) { return (mask >> b) & 1; }
template <class T> bool ckmin(T &a, const T &b) {
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}
template <class T> bool ckmax(T &a, const T &b) {
  if (b > a) {
    a = b;
    return true;
  }
  return false;
}
template <typename T, typename F> T FindFirstTrue(T l, T r, const F &predicat) {
  --l;
  while (r - l > 1) {
    T mid = l + (r - l) / 2;
    if (predicat(mid)) {
      r = mid;
    } else {
      l = mid;
    }
  }
  return r;
}
template <typename T, typename F> T FindLastFalse(T l, T r, const F &predicat) {
  return FindFirstTrue(l, r, predicat) - 1;
}
const ll INF = 2e18;
const int INFi = 1e9;
const int N = 5e5 + 5;
const int LG = 20;
int dsu[N];
int root(int v) { return v == dsu[v] ? v : dsu[v] = root(dsu[v]); }
void unite(int u, int v) { dsu[v] = u; }
int val[N];
void solve() {
  int n;
  cin >> n;
  vi L(n), R(n);
  rep(i, n) cin >> L[i];
  rep(i, n) cin >> R[i];
  vector<pair<int, int>> xx;
  rep(i, n) xx.emplace_back(R[i], i); // Store right endpoints with indices
  sort(all(xx));                      // Sort by right endpoint
  xx.resize(unique(all(xx)) - xx.begin()); // Remove duplicate right endpoints
  int sz = xx.size();                  // Compressed size
  vi lt(n + 1, -1);                    // For storing left boundaries after compressed coordinate mapping

  rep(i, n) {
    int l = L[i], r = R[i];            // Original left/right of segment i
    l = lower_bound(all(xx), make_pair(l, -1)) - xx.begin(); // Compress l
    r = lower_bound(all(xx), make_pair(r, i)) - xx.begin();   // Compress r
    l++; r++;                                         // 1-indexed for simplicity
    lt[r] = l;                                        // Map compressed right to left
  }
  int ans = 0;
  auto solve = [&](int one) { // Function to calculate count for a fixed group size 'one'
    for (int i = 0; i <= sz; ++i)
      dsu[i] = i;                    // Reset DSU
    for (int i = 0; i <= sz; ++i)
      val[i] = 0;                    // Reset values
    int l = 1;
    val[l - 1] = n + 2;            // Initialize starting cost
    int cnt = 0;
    for (int r = l; r <= sz; r++) {
      {
        int j = lt[r];              // Get left boundary for current segment
        if (j >= l) {
          val[r]++;
          int pos = root(j - 1);   // Union-find based on root
          val[pos]--;
          if (val[pos] == 0) {
            unite(pos - 1, pos);   // Merge components
          }
        }
      }
      int cost = n + 2 - val[l - 1]; // Compute cost at current left pointer
      if (cost >= one) {             // If we can form a group of size one
        cnt++;
        l = r + 1;                        // Move start pointer forward
        val[l - 1] = n + 2;               // Reset cost at new start
      } else if (!val[r]) {
        unite(r - 1, r);                  // Merge adjacent segments
      }
    }
    ckmax(ans, cnt * one);  // Update global maximum
    return cnt;
  };
  function<void(int, int, int, int)> rec = [&](int l, int r, int low,
                                               int high) {
    if (low == high)
      return;
    while (r > l && min(high, n / (r - 1)) * (r - 1) <= ans)
      r--; // Pruning to avoid redundant computation
    if (l >= r)
      return;
    int mid = (l + r) >> 1;           // Midpoint of current range
    int mid_val = solve(mid);         // Try solving with group size 'mid'
    rec(l, mid, mid_val, high);       // Left part recursion
    rec(mid + 1, r, low, mid_val);    // Right part recursion
  };
  rec(1, n + 1, 0, n);                 // Start binary search
  cout << ans << '\n';
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << setprecision(12) << fixed;
  int t = 1;
  cin >> t;
  rep(i, t) { solve(); }
  return 0;
}


// https://github.com/VaHiX/codeForces/