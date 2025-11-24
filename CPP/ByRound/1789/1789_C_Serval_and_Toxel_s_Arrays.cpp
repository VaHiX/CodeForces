// Problem: CF 1789 C - Serval and Toxel's Arrays
// https://codeforces.com/contest/1789/problem/C

/*
C. Serval and Toxel's Arrays

Purpose:
This code computes the sum of values over all pairs of arrays A_i and A_j (0 <= i < j <= m),
where the value of a pair is defined as the number of distinct elements in the concatenation of A_i and A_j.

Algorithm:
- For each element in the initial array, we track how long it stayed in its current position across operations.
- When an element changes position, we compute how many operations it was present in previous states.
- We use a map to accumulate these counts and then compute final result using inclusion-exclusion principle:
    Total = m*(m+1)*n - sum (count[i] * (count[i]-1) / 2)
  
Time Complexity: O(n log n + m log m) per test case due to map operations.
Space Complexity: O(n + m) for storing the arrays and maps.

*/

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    std::vector<ll> v(n);
    std::map<ll, ll> start, cntmap; // 'start' tracks when each element was last updated; 'cntmap' stores count of time spent by each value
    for (int p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
      start[p] = 0; // Initialize start times for all positions
    }
    for (int p = 1; p <= m; p++) {
      ll pos, num;
      scanf("%lld %lld", &pos, &num);
      --pos;
      cntmap[v[pos]] += p - start[pos]; // Add duration this value was in its current position
      start[pos] = p; // Update the time when this position was last modified
      v[pos] = num;   // Apply the update to the array
    }
    for (int p = 0; p < n; p++) {
      cntmap[v[p]] += m + 1 - start[p]; // Account for remaining time after last modification
    }
    ll total(0);
    for (std::pair<ll, ll> x : cntmap) {
      total += x.second * (x.second - 1) / 2; // Sum of combinations of count taken 2 at a time
    }
    printf("%lld\n", m * (m + 1) * n - total); // Final answer using inclusion-exclusion principle
  }
}


// https://github.com/VaHiX/codeForces/