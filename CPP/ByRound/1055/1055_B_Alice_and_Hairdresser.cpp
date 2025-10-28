// Problem: CF 1055 B - Alice and Hairdresser
// https://codeforces.com/contest/1055/problem/B

/*
B. Alice and Hairdresser
Algorithms/Techniques: Segment processing, greedy approach with tracking of segments that need cutting.

Time Complexity: O(n + m)
Space Complexity: O(n)

The solution keeps track of how many "segments" (contiguous ranges of hairlines longer than l)
need to be cut. For each query of type 0, it outputs the number of such segments.
For updates of type 1, it efficiently recalculates the number of required segments
by checking neighboring hairlines when a hairline's length changes.
*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n, m, l;
  scanf("%lld %lld %lld", &n, &m, &l);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  ll cnt(0);
  // Count the number of segments where hairlines > l and each segment
  // starts at a position where previous hairline <= l or it's the start
  for (ll p = 0; p < n; p++) {
    if (a[p] <= l) {
      continue;
    }
    if (p == 0 || a[p - 1] <= l) {
      ++cnt;
    }
  }
  while (m--) {
    ll t;
    scanf("%lld", &t);
    if (t) {
      // Type 1 update: increase hairline p by d
      ll x, d;
      scanf("%lld %lld", &x, &d);
      --x; // Convert to 0-based indexing
      a[x] += d;
      // Check conditions for potential impact on cnt
      if (l < a[x] && a[x] <= l + d) {
        // Hairline x transitions from <= l to > l
        // Check if it starts a new segment or affects an existing one
        if (((x == 0) || ((x > 0) && (a[x - 1] <= l))) &&
            ((x == n - 1) || ((x + 1 < n) && (a[x + 1] <= l)))) {
          // x starts a new segment
          ++cnt;
        }
        if ((x > 0) && (a[x - 1] > l) && (x + 1 < n) && (a[x + 1] > l)) {
          // x was in a segment but now it's removed from the middle of a segment
          --cnt;
        }
      }
    } else {
      // Type 0 query: output number of segments (cnt)
      printf("%lld\n", cnt);
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/