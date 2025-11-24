// Problem: CF 1945 D - Seraphim the Owl
// https://codeforces.com/contest/1945/problem/D

/*
D. Seraphim the Owl

Problem Description:
Kirill is in a queue of n people and wants to bribe people ahead of him to move to one of the first m positions.
For each person i, there are two values:
- a[i]: cost to bribe person i directly
- b[i]: ongoing cost for each person between i and Kirill's final position

Goal: Find minimum total coins needed for Kirill to reach any of the first m positions.

Algorithms/Techniques:
- Dynamic Programming with backward pass
- Prefix and suffix computations
- Greedy-like approach with optimal substructure

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing vectors and auxiliary arrays

*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    std::vector<ll> b(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &b[p]);
    }
    ll prev(0), rbs(0);
    std::vector<ll> f(n, 0);
    // Forward pass: compute minimum cost to reach each position from the end
    for (ll p = n - 1; p >= 0; p--) {
      f[p] = a[p] + rbs + prev;    // total cost to move to position p
      rbs += b[p];                 // accumulate b values for future costs
      if (a[p] <= b[p]) {          // if bribing this person is beneficial
        rbs = 0;                   // reset accumulated costs beyond this point
        prev = f[p];               // update previous best cost
      }
    }
    ll ans(f[0]);                  // initialize result with first position's cost
    for (ll p = 0; p < m; p++) {   // find minimum among first m positions
      ans = (ans < f[p] ? ans : f[p]);
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/