// Problem: CF 2065 D - Skibidus and Sigma
// https://codeforces.com/contest/2065/problem/D

/*
D. Skibidus and Sigma

Purpose:
This code solves the problem of maximizing the "sigma score" of a concatenated array formed by arranging n arrays of m elements each.
The sigma score of an array b of length k is defined as sum of prefix sums: S_1 + S_2 + ... + S_k where S_i is the sum of first i elements.

Algorithm:
- For each input array, calculate its total sum and store.
- Sort these sums in descending order.
- To compute the final score:
   - Initially account for contributions from individual arrays' prefix sums (weighted by their positions in original array).
   - Then add to this value the contribution from concatenating sorted arrays.
     Each array contributes based on how many times its elements appear in prefix sums of the final concatenated array.

Time Complexity: O(n log n + nm) per test case due to sorting and processing all elements once.
Space Complexity: O(n) for storing sums of arrays.

*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    std::vector<ll> v(n); // Stores sum of elements in each array
    ll total(0); // Total score accumulator
    for (ll p = 0; p < n; p++) {
      ll sum(0); // Sum of current array
      for (size_t q = 0; q < m; q++) {
        ll x;
        scanf("%lld", &x);
        total += (m - q) * x; // Add contribution of this element to total score based on its position in original array
        sum += x; // Accumulate current array's sum
      }
      v[p] = sum; // Store the sum for this array
    }
    sort(v.rbegin(), v.rend()); // Sort in descending order to maximize impact of larger sums later
    for (size_t p = 0; p < n; p++) {
      total += (n - 1 - p) * m * v[p]; // Add contributions from concatenating arrays, using weights based on remaining positions
    }
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/