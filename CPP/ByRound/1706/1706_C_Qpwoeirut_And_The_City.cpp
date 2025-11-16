// Problem: CF 1706 C - Qpwoeirut And The City
// https://codeforces.com/contest/1706/problem/C

/*
C. Qpwoeirut And The City
Problem Description:
Given a sequence of building heights, we want to maximize the number of "cool" buildings.
A building is cool if it is taller than both its left and right neighbors.
We are allowed to add floors to increase building heights.
Goal: Find the minimum number of additional floors needed to maximize the number of cool buildings.

Approach:
- If n is odd, we process pairs of indices (1,3), (5,7), ..., checking if middle buildings can be made cool.
- If n is even, we use a more complex DP approach with prefix and suffix arrays:
  - Precompute minimum operations needed to make each building cool from left and right directions.
  - Try all valid positions where the optimal solution may occur.
  - Time Complexity: O(n) for each test case.
  - Space Complexity: O(n) for storing prefix and suffix arrays.

Time Complexity: O(n) per test case
Space Complexity: O(n)
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
    std::vector<ll> h(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &h[p]);
    }
    ll res(0);
    if (n % 2) {
      // For odd n, only one pass through all odd-indexed nodes
      for (ll p = 1; p < n; p += 2) {
        ll target = 1 + ((h[p - 1] > h[p + 1]) ? h[p - 1] : h[p + 1]);
        ll diff = target - h[p];
        res += (diff > 0) * diff;
      }
    } else {
      // For even n, compute prefix and suffix costs
      std::vector<ll> u(n, 0), v(n, 0);
      for (ll p = 1; p + 1 < n; p += 2) {
        ll target = 1 + ((h[p - 1] > h[p + 1]) ? h[p - 1] : h[p + 1]);
        ll diff = target - h[p];
        u[p] = u[p - 1 - (p >= 2)] + (diff > 0) * diff;
      }
      for (ll p = n - 2; p >= 1; p -= 2) {
        ll target = 1 + ((h[p - 1] > h[p + 1]) ? h[p - 1] : h[p + 1]);
        ll diff = target - h[p];
        v[p] = v[p + 1 + (p + 2 < n)] + (diff > 0) * diff;
      }
      ll cur = (u[n - 3] < v[2]) ? u[n - 3] : v[2];
      for (ll p = 2; p + 2 < n; p += 2) {
        ll tst = u[p - 1] + v[p + 2];
        cur = (cur < tst) ? cur : tst;
      }
      res = cur;
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/