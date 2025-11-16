// Problem: CF 1422 B - Nice Matrix
// https://codeforces.com/contest/1422/problem/B

/*
B. Nice Matrix
Purpose: Given an n x m matrix, make it "nice" by ensuring all rows and columns are palindromes,
         with minimum operations (each operation is increasing or decreasing any element by 1).
         For each group of 4 symmetric positions, choose the median to minimize moves.

Algorithms/Techniques:
- Group symmetric cells in the matrix for each position.
- For each such group of 4 elements, sort their values and choose the median
  to minimize sum of absolute differences.
- Time Complexity: O(n * m * log(4)) = O(n * m), since sorting 4 elements is constant time.
- Space Complexity: O(1) extra space (not counting input storage).

Time Complexity: O(n * m)
Space Complexity: O(1)
*/

#include <bits/std_abs.h>
#include <algorithm>
#include <cstdio>
#include <vector>

typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    std::vector<std::vector<ll>> w(n, std::vector<ll>(m, 0));
    for (ll row = 0; row < n; row++) {
      for (ll col = 0; col < m; col++) {
        scanf("%lld", &w[row][col]);
      }
    }
    ll total(0);
    for (ll row = 0; row < n; row++) {
      for (ll col = 0; col < m; col++) {
        // Collect values from symmetric positions
        std::vector<ll> v = {w[row][col], w[row][m - 1 - col],
                             w[n - 1 - row][m - 1 - col], w[n - 1 - row][col]};
        sort(v.begin(), v.end()); // Sort to get median in middle
        total += std::abs(v[1] - w[row][col]); // Add difference from median
      }
    }
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/