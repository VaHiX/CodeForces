// Problem: CF 1110 B - Tape
// https://codeforces.com/contest/1110/problem/B

/*
B. Tape
Algorithms/Techniques: Greedy algorithm with sorting
Time complexity: O(n log n)
Space complexity: O(n)

The problem asks to cover all broken segments on a stick using at most k pieces of tape,
minimizing the total length of tape used.

Approach:
1. We sort the broken segments.
2. We calculate the gaps between consecutive broken segments.
3. To minimize total tape length, we should place our k pieces optimally.
   This means we want to "skip" the largest gaps to reduce the total needed tape.
4. Sort the gaps in ascending order and ignore the largest (n - k) gaps,
   since placing a piece there would be wasteful.
5. The minimum tape length is the total length of gaps plus the full stick length minus
   the sum of ignored largest gaps.

Key idea: The problem is essentially choosing k intervals to cover n points optimally,
which can be reduced to choosing (n - k) gaps to skip among all adjacent gaps.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll n, m, k;
  scanf("%lld %lld %lld", &n, &m, &k);
  
  if (n <= k) {
    // If number of broken segments is <= number of pieces allowed,
    // we can place one piece per segment.
    printf("%lld\n", n);
    return 0;
  }
  
  std::vector<ll> b(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &b[p]);
  }
  
  // Compute gaps between consecutive broken segments
  std::vector<ll> d(n - 1);
  for (ll p = 0; p < n - 1; p++) {
    d[p] = b[p + 1] - b[p] - 1;  // Gap between segment b[p] and b[p+1]
  }
  
  // Sort gaps to identify the largest ones
  sort(d.begin(), d.end());
  
  // Start with total length of stick
  ll dist(n);
  
  // Subtract the sum of the largest (n - k) gaps to avoid covering them
  for (ll p = 0; p < n - k; p++) {
    dist += d[p];
  }
  
  printf("%lld\n", dist);
  return 0;
}


// https://github.com/VaHiX/codeForces/