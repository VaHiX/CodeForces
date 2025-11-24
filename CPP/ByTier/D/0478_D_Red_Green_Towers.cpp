// Problem: CF 478 D - Red-Green Towers
// https://codeforces.com/contest/478/problem/D

/*
Code Purpose:
This program determines the number of different red-green towers that can be built with given numbers of red and green blocks,
such that the tower has maximum possible height (h) and each level consists of blocks of a single color.

Algorithm:
- First, compute the maximum number of levels (h) such that total blocks needed (1+2+...+h = h*(h+1)/2) is <= r+g.
- Then, use dynamic programming to count all valid combinations of red blocks used in the tower.
- For each valid number of red blocks, add up the number of ways to build such a tower.
- The DP uses a rolling array technique to save space and efficiently compute binomial-like sums.

Time Complexity: O(r * h) where h is the maximum height of the tower
Space Complexity: O(r + h) for the DP array and auxiliary variables

Techniques:
- Dynamic Programming with rolling array optimization
- Mathematical calculation of maximum tower height
- Modular arithmetic for result handling
*/

#include <cstdio>
typedef long long ll;
int main() {
  const ll MOD = 1e9 + 7;
  const ll MAX = 4e5 + 7;
  ll r, g;
  scanf("%lld %lld", &r, &g);
  ll n(0);
  // Find the maximum number of levels possible
  while (n * (n + 1) / 2 <= (r + g)) {
    ++n;
  };
  --n;  // Adjust n to be the actual maximum height
  ll f[MAX] = {0};
  f[0] = 1;  // Base case: One way to build 0 red blocks
  // DP: iterate through levels and update combinations of red blocks
  for (ll p = 1; p <= n; p++) {
    for (ll q = r; q >= 0; q--) {
      f[p + q] = (f[p + q] + f[q]) % MOD;  // Update combinations using previous values
    }
  }
  ll ans(0);
  // Calculate how many red blocks are used in a tower with green blocks
  ll x = n * (n + 1) / 2 - g;
  if (x < 0) {
    x = 0;  // Ensure non-negative minimum
  }
  // Sum all valid combinations from x to r red blocks
  for (ll p = x; p <= r; p++) {
    ans = (ans + f[p]) % MOD;
  }
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/