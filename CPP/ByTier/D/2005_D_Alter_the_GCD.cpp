// Problem: CF 2005 D - Alter the GCD
// https://codeforces.com/contest/2005/problem/D

/*
D. Alter the GCD
Algorithm: 
  - Preprocess prefix and suffix GCD arrays for both arrays a and b to quickly compute GCDs of subarrays.
  - Use a technique similar to "sliding window" with states tracking GCDs of segments to compute the maximum sum of GCDs after one swap operation (l, r).
  - Use efficient data structures and caching to avoid recomputation.

Time Complexity: O(n log(max(a[i], b[i]))) per test case; log factor comes from GCD computation.
Space Complexity: O(n) for storing prefix/suffix arrays and temporary states.

*/
#include <iostream>
#include <utility>

using namespace std;
using i64 = long long;
using intN = int[202333];
intN a, b, pa, pb, sa, sb;
using intV = int[33][3];
intV qwq[2];
int GCD(int x, int y) {
  for (; y; swap(x, y))
    x = x % y;
  return x;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T = 1;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    for (int i = 1; i <= n; ++i)
      cin >> b[i];
    pa[0] = pb[0] = sa[n + 1] = sb[n + 1] = 0;
    // Compute prefix GCDs for arrays a and b
    for (int i = 1; i <= n; ++i)
      pa[i] = GCD(a[i], pa[i - 1]);
    for (int i = 1; i <= n; ++i)
      pb[i] = GCD(b[i], pb[i - 1]);
    // Compute suffix GCDs for arrays a and b
    for (int i = n; i >= 1; --i)
      sa[i] = GCD(a[i], sa[i + 1]);
    for (int i = n; i >= 1; --i)
      sb[i] = GCD(b[i], sb[i + 1]);
    int ans = 0;
    i64 cnt = 0;
    auto chk = [&](int aa, i64 cc) {
      if (aa > ans)
        ans = aa, cnt = 0;
      if (aa >= ans)
        cnt += cc;
    };
    // State management: cur and pos hold the current and next states of GCD combinations
    auto cur = qwq[0], pos = qwq[1];
    int s_cur = 0, s_pos = 0;
    for (int L = n; L >= 1; --L) {
      // Initialize state with boundary condition: GCD from suffix
      cur[0][0] = L, cur[0][1] = GCD(b[L], sa[L + 1]),
      cur[0][2] = GCD(a[L], sb[L + 1]);
      s_cur = 1;
      int las = L;
      // Evaluate case where we swap a single element (or no swap if we consider prefix)
      chk(GCD(pa[L - 1], cur[0][1]) + GCD(pb[L - 1], cur[0][2]), 1);
      for (int i = 0; i < s_pos; ++i) {
        // Process previous computed states
        auto [p, ma, mb] = pos[i];
        ma = GCD(b[L], ma), mb = GCD(a[L], mb);
        chk(GCD(pa[L - 1], ma) + GCD(pb[L - 1], mb), p - las);
        // Optimize by merging identical states
        while (s_cur && cur[s_cur - 1][1] == ma && cur[s_cur - 1][2] == mb)
          --s_cur;
        cur[s_cur][0] = p, cur[s_cur][1] = ma, cur[s_cur][2] = mb;
        ++s_cur;
        las = p;
      }
      // Swap current and previous states
      swap(cur, pos), swap(s_cur, s_pos);
    }
    cout << ans << ' ' << cnt << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/