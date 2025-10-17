// Problem: CF 1760 E - Binary Inversions
// https://codeforces.com/contest/1760/problem/E

/*
E. Binary Inversions
Algorithms/Techniques: Prefix sums, single pass optimization
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem involves maximizing the number of inversions in a binary array by performing at most one flip operation.
An inversion is a pair (i,j) such that i < j and a[i] > a[j]. Since we're dealing with binary arrays, inversions occur when a 1 appears before a 0.

Approach:
1. Precompute prefix sums for zeros and ones to quickly calculate how many 1s are before a position and how many 0s are after.
2. For each position, compute the potential gain if we flip that element.
3. The maximum gain among all flips plus the initial inversion count gives the answer.

Initial inversions are calculated using running sum of 0s encountered so far, multiplied by number of 1s seen before.
For each element, consider flipping it and compute resulting change in inversions based on prefix sums.
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
    std::vector<ll> v(n, 0), a(n, 0), z(n, 0); // a: prefix count of 1s, z: prefix count of 0s
    ll total(0);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
      z[p] = (p > 0 ? z[p - 1] : 0) + (v[p] == 0); // Running count of zeros
      a[p] = (p > 0 ? a[p - 1] : 0) + (v[p] == 1); // Running count of ones
      total += (v[p] ? 0 : a[p]); // Count of inversions initially (0s contribute to inversions based on 1s before)
    }
    ll mx(0);
    for (ll p = 0; p < n; p++) {
      ll diff = (p > 0 ? a[p - 1] : 0) - (z.back() - z[p]); // Change in inversions if we flip v[p]
      if (!v[p]) { // If current element is 0, flipping increases inversion count
        diff = -diff;
      }
      mx = (mx > diff ? mx : diff); // Keep track of maximum gain from a single flip
    }
    printf("%lld\n", total + mx); // Final result: initial inversions + max possible gain from one flip
  }
}


// https://github.com/VaHiX/codeForces/