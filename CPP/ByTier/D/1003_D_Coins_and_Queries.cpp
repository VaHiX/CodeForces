// Problem: CF 1003 D - Coins and Queries
// https://codeforces.com/contest/1003/problem/D

/*
Algorithm: Greedy with Bit Manipulation and Map
Approach:
- For each query, we decompose the target value into powers of 2 (binary representation).
- We iterate through each power of 2 (from 1 to 2^30) and check how many coins of that value are needed.
- We greedily use available coins of higher denominations to "merge" into smaller ones when necessary.
- This simulates a greedy coin change algorithm but with precomputed coin counts stored in a map.

Time Complexity: O(q * log(max_value) * log(n)) where q is number of queries, and log(max_value) is due to iterating through powers of 2.
Space Complexity: O(n) for storing the coin counts in the map.

*/
#include <cstdio>
#include <map>
typedef long long ll;

int main() {
  ll n, q;
  scanf("%lld %lld", &n, &q);
  std::map<ll, ll> m;
  for (ll p = 0; p < n; p++) {
    ll x;
    scanf("%lld", &x);
    ++m[x]; // Count occurrences of each coin value
  }
  while (q--) {
    ll b;
    scanf("%lld", &b);
    std::map<ll, ll> cur(m); // Copy of current coin counts
    ll cnt(0); // Total coins used
    for (ll pow = 1; pow <= 2e9; pow *= 2) {
      ll val = pow * ((b / pow) % 2); // Extract bit at position 'pow'
      if (val == 0) {
        continue; // Skip if this bit is not set in b
      }
      for (ll u = pow; u >= 1; u /= 2) {
        if (!cur.count(u)) {
          continue; // Skip if no coins of denomination u available
        }
        if (cur[u] * u >= val) {
          // Use as few coins as possible of denomination u
          cur[u] -= val / u;
          cnt += val / u;
          val = 0;
          break;
        } else {
          // Use all available coins of denomination u
          cnt += cur[u];
          val -= cur[u] * u;
          cur[u] = 0;
        }
      }
      if (val > 0) {
        // Cannot form the required value
        cnt = -1;
        break;
      }
    }
    printf("%lld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/