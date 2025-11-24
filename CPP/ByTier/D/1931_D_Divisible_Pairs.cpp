// Problem: CF 1931 D - Divisible Pairs
// https://codeforces.com/contest/1931/problem/D

/*
D. Divisible Pairs
Algorithm: Two Pointers + Map + Modular Arithmetic
Time Complexity: O(n * log n) per test case due to map operations
Space Complexity: O(n) for storing elements in the map

The problem asks to count pairs (i,j) where i < j such that:
- (a[i] + a[j]) % x == 0
- (a[i] - a[j]) % y == 0

Key insight:
From the constraints:
1. (a[i] + a[j]) % x == 0 => a[j] % x == (x - (a[i] % x)) % x
2. (a[i] - a[j]) % y == 0 => a[i] % y == a[j] % y

So for each element, we compute:
- key1 = (x - (a[i] % x)) % x
- key2 = a[i] % y
We then look for previous elements with same (key1, key2) pair and add count of such elements.

This uses a map to store frequency of pairs (remainder_mod_x, remainder_mod_y).
For each new element, we check how many prior elements have matching key,
and accumulate the count of valid pairs.
*/

#include <cstdio>
#include <map>
#include <set>
#include <utility>

typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, x, y;
    scanf("%lld %lld %lld", &n, &x, &y);
    std::map<std::pair<ll, ll>, std::set<ll>> mods;
    ll cnt(0);
    for (ll p = 0; p < n; p++) {
      ll a;
      scanf("%lld", &a);
      // Compute the key for current element
      std::pair<ll, ll> key = std::make_pair((x - (a % x)) % x, a % y);
      // Add number of previous elements with same key to result
      cnt += mods[key].size();
      // Insert current index into set for the key based on (a % x, a % y)
      mods[std::make_pair(a % x, a % y)].insert(p);
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/