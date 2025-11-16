// Problem: CF 1334 C - Circle of Monsters
// https://codeforces.com/contest/1334/problem/C

/*
C. Circle of Monsters
Algorithm: Greedy with circular array simulation and prefix sum optimization
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing monster data

The problem involves killing monsters arranged in a circle where each monster has health (a[i]) and explosion damage (b[i]).
When a monster dies, it damages the next monster in the circle, possibly triggering a chain reaction.
We want to minimize total bullets required to kill all monsters.

The key insight is that we can choose the starting point such that we minimize the number of bullets needed.
We compute a "cost" array where cost[i] represents the minimum bullets required if we start killing from monster i+1 (mod n).

Approach:
1. First, calculate total bullets needed without any explosions: sum(a).
2. Then, for each possible starting position, simulate the chain reaction to find minimal total bullets.
3. Use prefix sums and circular indexing to efficiently calculate minimum over all rotations.

The main idea uses a sliding window concept on a circular array:
- We compute prefix sums of (a[i] - b[i]) differences
- Then we subtract from the base case sum, the minimum prefix value to account for the optimal starting position.
*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n), b(n);
    for (long p = 0; p < n; p++) {
      scanf("%lld %lld", &a[p], &b[p]);
    }
    ll s(0), carry(0);
    for (ll p = 0; p < n; p++) {
      ll tmp = (a[p] > carry) ? (a[p] - carry) : 0;
      s += tmp;
      carry = b[p];
    }
    ll cur(s), mn(s);
    for (ll p = 1; p < n; p++) {
      ll x = (a[p] < b[(n + p - 1) % n]) ? a[p] : b[(n + p - 1) % n];
      ll y = (b[(n + p - 2) % n] < a[(n + p - 1) % n]) ? b[(n + p - 2) % n]
                                                       : a[(n + p - 1) % n];
      cur += x - y;
      mn = (mn < cur) ? mn : cur;
    }
    printf("%lld\n", mn);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/