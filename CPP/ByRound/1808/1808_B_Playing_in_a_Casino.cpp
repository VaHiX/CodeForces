// Problem: CF 1808 B - Playing in a Casino
// https://codeforces.com/contest/1808/problem/B

/*
B. Playing in a Casino

Purpose:
This program calculates the total winnings from all possible pairwise games between players, where each player holds a card with m numbers. For each pair of players, the winner receives chips equal to the sum of absolute differences between corresponding numbers on their cards.

Algorithms/Techniques:
- Sorting and mathematical optimization
- Column-wise processing to compute contribution of each number position across all pairs

Time Complexity: O(n * m * log(n) + n * m)
Space Complexity: O(n * m)

*/
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    std::vector<std::vector<ll>> f(n, std::vector<ll>(m, 0));
    for (ll row = 0; row < n; row++) {
      for (ll col = 0; col < m; col++) {
        scanf("%lld", &f[row][col]);
      }
    }
    ll total(0);
    for (int col = 0; col < m; col++) {
      std::vector<ll> v(n);                  // Collect all values from column 'col'
      for (ll row = 0; row < n; row++) {
        v[row] = f[row][col];
      }
      sort(v.begin(), v.end());              // Sort the values to facilitate efficient calculation
      for (ll p = 0; p < n; p++) {
        total += (2 * p - (n - 1)) * v[p];   // Contribution of v[p] in all pairwise differences
      }
    }
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/