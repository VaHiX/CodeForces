// Problem: CF 1374 D - Zero Remainder Array
// https://codeforces.com/contest/1374/problem/D

/*
D. Zero Remainder Array
Algorithm: Greedy with Map
Time Complexity: O(n log n) per test case
Space Complexity: O(n) per test case

We want to make all elements of array divisible by k using minimum moves.
Each move either:
1. Increases x by 1 and adds x to one element (at most once per element)
2. Only increases x by 1

Key idea:
For each element a[i] % k != 0, we need to add some value to make it divisible by k.
If a[i] % k = r, we need to add (k - r) to make it divisible.
We can only do operation 1 once per element, and it must be done before x becomes too large.

Strategy:
- For each element not already divisible by k, calculate how many operations it needs.
- Group these by the number of operations needed (k - a[i] % k).
- For each group with g elements, we need g operations, but all elements can be added in sequence.
- Total moves for this group = (k - r) + k*(g - 1) = k*g - r

We want to minimize total moves, so find the maximum such value among all groups.
Also add 1 at the end if needed.

*/
#include <cstdio>
#include <map>
#include <utility>

typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::map<ll, ll> cnt; // key: operations needed, value: count of elements
    for (ll p = 0; p < n; p++) {
      ll a;
      scanf("%lld", &a);
      if (a % k == 0) {
        continue; // already divisible, no moves needed
      }
      ++cnt[k - a % k]; // count how many elements need 'k - a%k' operations to become divisible
    }
    ll mx(0);
    for (std::map<ll, ll>::iterator it = cnt.begin(); it != cnt.end(); it++) {
      ll cur = (it->first) + k * ((it->second) - 1); // compute total moves needed for this group
      mx = (mx > cur) ? mx : cur; // track maximum among all groups
    }
    printf("%lld\n", mx + (mx > 0)); // add 1 if there's at least one operation, else 0
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/