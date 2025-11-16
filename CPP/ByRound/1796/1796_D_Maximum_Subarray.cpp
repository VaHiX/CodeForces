// Problem: CF 1796 D - Maximum Subarray
// https://codeforces.com/contest/1796/problem/D

/*
 *
 * Problem: D. Maximum Subarray
 * Algorithm: Dynamic Programming with Sliding Window Optimization
 * Time Complexity: O(n * k), where n is the size of array and k is the number of elements to add x to.
 * Space Complexity: O(n * k), due to the DP table f[i][j] storing maximum subarray sum ending at index i with j operations applied.
 *
 * The solution uses dynamic programming where:
 * - f[i][j] represents the maximum subarray sum ending at index i having applied exactly j operations (adding x).
 * - For each element, we decide whether to:
 *   1. Not include the element in the current subarray (starting new subarray).
 *   2. Include it as part of a previous subarray (either adding x or subtracting x).
 * - We iterate over all valid combinations of choosing positions to add x.
 * - We track the maximum subarray sum across all valid configurations.
 *
 */

#include <stdio.h>
#include <algorithm>
#include <limits>

#define ll long long
#define ull unsigned long long
#define srt short
#define MAX(v)                                                                 \
  (v < 0 ? static_cast<srt>(~(1 << 15)) : (v ? ~(1ll << 63) : ~(1 << 31)))
#define MIN(v) (v < 0 ? static_cast<srt>(1 << 15) : (v ? 1ll << 63 : 1 << 31))
template <class _Tp> struct GT {
  constexpr bool operator()(const _Tp &a, const _Tp &b) const { return a > b; }
};
template <class _Tp> struct LS {
  constexpr bool operator()(const _Tp &a, const _Tp &b) const { return a < b; }
};
template <class _Tp> _Tp Max(const _Tp &v) { return v; }
template <class _Tp, class... TpArgs>
_Tp Max(const _Tp &v, const TpArgs &...rest) {
  _Tp tmp = Max(rest...);
  return v > tmp ? v : tmp;
}
template <class _Tp> _Tp Min(const _Tp &v) { return v; }
template <class _Tp, class... TpArgs>
_Tp Min(const _Tp &v, const TpArgs &...rest) {
  _Tp tmp = Min(rest...);
  return v < tmp ? v : tmp;
}
const int N = 200010, M = 21;
ll f[N][M];
int t, n, k, x;
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d", &n, &k, &x);
    ll ans = 0, v;
    // Initialize DP table with minimum possible value
    for (int i = 0; i < n; i++)
      std::fill_n(f[i], M, std::numeric_limits<int>::min());
    f[0][0] = 0; // Base case: before processing any elements, max subarray sum is 0
    
    for (int i = 1; i <= n; i++) {
      scanf("%lld", &v);
      int tot = Min(i, k); // Maximum valid value of j for this position
      int restCnt = n - i; // Number of remaining elements to process
      for (int j = Max(0, k - restCnt); j <= tot; j++) {
        // Case when no operation is applied
        if (!j)
          f[i][0] = Max(v - x, v - x + f[i - 1][0]);
        else {
          // Update f[i][j] by considering adding x to this element or not
          f[i][j] = Max(v + x, v - x + f[i - 1][j], v + x + f[i - 1][j - 1]);
          if (j <= i - 1)
            f[i][j] = Max(f[i][j], v - x); // Also consider not adding x to this element
        }
        ans = Max(ans, f[i][j]); // Keep track of the overall maximum
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/