// Problem: CF 2019 B - All Pairs Segments
// https://codeforces.com/contest/2019/problem/B

/*
B. All Pairs Segments
Algorithm: Difference Array + Map
Time Complexity: O(n log n + q), where n is the number of points and q is the number of queries.
Space Complexity: O(n), due to map usage for storing segment counts.

This problem involves computing how many integer points lie on exactly k segments 
for various values of k. Each segment [x_i, x_j] represents a range from point i to point j.
The approach uses a difference array technique via a map to track the change in count 
of overlapping segments efficiently. For each pair (i,j) with i < j, we calculate how the
segment contributes to the count of points. The final result is computed per query by looking up
the precomputed counts in the map.

Key techniques:
- Difference array concept using std::map for sparse updates.
- Use of segment overlaps calculated based on positions x_i and x_j.
- Efficient map lookups for answering queries.
*/

#include <cstdio>
#include <map>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, q;
    scanf("%lld %lld", &n, &q);
    std::map<ll, ll> m; // Map to store segment overlap counts
    
    // Preprocessing the contribution of all pairs (i,j) where i < j
    for (ll p = 1; p <= n; p++) {
      // Calculate base value for each point contribution
      m[n * p - p * p + p - 1] += 1;
    }
    
    ll prev;
    scanf("%lld", &prev); // Read first point
    
    // Process differences between adjacent points and update map accordingly
    for (ll p = 1; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      // Update the difference array with contribution from current pair
      m[p * (n - p)] += x - prev - 1;
      prev = x;
    }
    
    // Process queries
    while (q--) {
      ll k;
      scanf("%lld", &k);
      // Find answer by looking up in map
      ll res = m.count(k) ? m[k] : 0;
      printf("%lld ", res);
    }
    puts(""); // Newline after each test case
  }
}


// https://github.com/VaHiX/codeForces/