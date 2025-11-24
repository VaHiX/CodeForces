// Problem: CF 1733 A - Consecutive Sum
// https://codeforces.com/contest/1733/problem/A

/*
Purpose: 
This code solves a problem where we are given an array of n integers and can perform at most k swaps between elements at indices i and j such that i mod k = j mod k. 
After swaps, we select k consecutive elements to maximize their sum. The approach uses grouping by modulo k to optimize selection.

Algorithms/Techniques:
- Grouping by modulo operation
- Greedy selection within groups

Time Complexity: O(n*k) per test case
Space Complexity: O(k) for storing group maximums
*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::vector<ll> a(k, 0); // a[i] will store the maximum value in group i (mod k)
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      // For each element, we find its group (p % k) and update the maximum in that group
      a[p % k] = (a[p % k] > x) ? a[p % k] : x;
    }
    ll res(0);
    // Sum up the maximum values from each group to get the best possible consecutive k elements sum
    for (ll p = 0; p < k; p++) {
      res += a[p];
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/