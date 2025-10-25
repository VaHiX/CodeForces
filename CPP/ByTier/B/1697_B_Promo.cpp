// Problem: CF 1697 B - Promo
// https://codeforces.com/contest/1697/problem/B

/*
B. Promo
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

The store sells n items, the price of the i-th item is p_i. The store's management is going to hold a promotion: if a customer purchases at least x items, y cheapest of them are free.
The management has not yet decided on the exact values of x and y. Therefore, they ask you to process q queries: for the given values of x and y, determine the maximum total value of items received for free, if a customer makes one purchase.

Algorithms/Techniques:
- Sorting
- Prefix sums
- Greedy approach

Time Complexity: O(n log n + q)
Space Complexity: O(n)

*/
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n, q;
  scanf("%lld %lld", &n, &q);
  std::vector<ll> v(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &v[p]);
  }
  sort(v.begin(), v.end()); // Sort prices in ascending order to apply greedy strategy
  std::vector<ll> f(n + 1, 0); // Prefix sum array to quickly compute sum of subarrays
  for (ll p = 1; p <= n; p++) {
    f[p] = f[p - 1] + v[p - 1]; // Build prefix sums
  }
  while (q--) {
    ll x, y;
    scanf("%lld %lld", &x, &y);
    // To maximize the value of free items:
    // Buy x items, and take the y cheapest among them as free.
    // So we want to minimize the sum of the y cheapest items from the x items we buy.
    // Thus, we should buy the largest x items (in descending order), and take
    // the y cheapest from those x items. That corresponds to taking the first y items
    // in sorted array, considering we have bought last x items.
    // In sorted ascending order: take elements at indices [n - x, n - x + 1, ..., n - 1]
    // and then take the first y of them (cheapest among these x).
    // So, we are taking from index (n - x) to (n - x + y - 1)
    // This is equivalent to sum of elements from (n - x) to (n - x + y - 1),
    // which equals f[n - x + y] - f[n - x].
    ll res = f[n - x + y] - f[n - x]; 
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/