// Problem: CF 1534 B - Histogram Ugliness
// https://codeforces.com/contest/1534/problem/B

/*
B. Histogram Ugliness
Algorithms/Techniques: Greedy approach with histogram manipulation
Time Complexity: O(n) per test case
Space Complexity: O(n) for the vector storage

The problem involves minimizing the "ugliness" of a histogram, defined as:
- Sum of the vertical length of the outline
- Plus the number of operations performed (reducing bar heights)

Approach:
1. For each bar, we process it and determine if it can be reduced to improve the outline.
2. We traverse the array and adjust heights greedily to reduce the overall outline length.
3. The key insight is to reduce local maxima to match neighboring bars, but only when beneficial.
4. Operations are tracked via difference calculations from previous bar heights.
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
    std::vector<ll> a(n + 1); // Use 1-based indexing
    for (ll p = 1; p <= n; p++) {
      scanf("%lld", &a[p]);
    }
    a.push_back(0); // Sentinel value to avoid bounds checking
    
    ll total(0);
    for (ll p = 1; p <= n; p++) {
      // Check if current bar is a local maximum
      if (a[p - 1] < a[p] && a[p] > a[p + 1]) {
        // Reduce the peak to the smaller of its neighbors
        ll x = (a[p - 1] > a[p + 1] ? a[p - 1] : a[p + 1]);
        total += (a[p] - x); // Count operations performed
        a[p] = x; // Update height
      }
      // Add absolute difference between current and previous bar to total outline length
      ll diff = a[p] - a[p - 1];
      if (diff < 0) {
        diff = -diff;
      }
      total += diff;
    }
    total += a[n]; // Add last bar's height to final tally
    
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/