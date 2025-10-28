// Problem: CF 1430 B - Barrels
// https://codeforces.com/contest/1430/problem/B

/*
B. Barrels
Algorithms/Techniques: Sorting, Greedy approach

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the barrel capacities

Problem Description:
Given n barrels with initial water amounts, we can pour water at most k times.
Goal is to maximize the difference between the maximum and minimum water levels.

Approach:
1. Sort the barrels in descending order to prioritize the largest values.
2. Take the first (k+1) elements and sum them up — this represents the best way to concentrate
   as much water as possible into a subset of barrels to maximize the difference.
3. The maximum difference will be achieved by putting all available water into the highest
   buckets, while leaving others at zero (or minimal values).

Key Insight:
To maximize difference = max - min, we want max to be as large as possible and min to be as small as possible.
So, add k operations to concentrate water into the largest elements.

*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    sort(a.rbegin(), a.rend()); // Sort in descending order to get largest elements first
    ll res(0);
    for (ll p = 0; p <= k && p < n; p++) {
      res += a[p]; // Sum the largest (k+1) elements to maximize difference
    }
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/