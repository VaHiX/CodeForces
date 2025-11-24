// Problem: CF 1520 D - Same Differences
// https://codeforces.com/contest/1520/problem/D

/*
D. Same Differences
Algorithm: 
    The problem asks to count pairs (i, j) such that i < j and a[j] - a[i] = j - i.
    Rearranging the equation: a[j] - j = a[i] - i.
    Thus, for each element, we compute val = a[i] - i and count how many times this value has appeared before.
    This is a classic two-sum-like problem using a hash map to store counts.

Time Complexity: O(n) per test case
Space Complexity: O(n) for the map storage

Techniques:
    - Hash map for frequency counting
    - Prefix-like transformation of the condition
*/

#include <cstdio>
#include <map>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::map<ll, ll> m;  // Map to store frequency of (a[i] - i)
    ll ans(0);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      x -= p;  // Transform a[i] to a[i] - i
      if (m.count(x)) {  // If this transformed value has been seen before
        ans += m[x];  // Add previous count to result
      }
      ++m[x];  // Increment frequency of current transformed value
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/