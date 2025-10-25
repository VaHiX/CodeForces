// Problem: CF 1679 B - Stone Age Problem
// https://codeforces.com/contest/1679/problem/B

#include <cstdio>
#include <set>
#include <vector>
typedef long long ll;
int main() {
  ll n, q;
  scanf("%lld %lld", &n, &q);
  ll sum(0), reset(-1);
  std::set<ll> s; // Tracks indices that have been explicitly set (not reset)
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
    sum += a[p];
    s.insert(p); // Initially all elements are considered explicit
  }
  for (ll p = 0; p < q; p++) {
    ll t;
    scanf("%lld", &t);
    if (t == 1) {
      ll idx, x;
      scanf("%lld %lld", &idx, &x);
      --idx;
      // Calculate delta: if idx was reset, we add x - reset. Else we add x - original value
      sum += (x - (s.count(idx) ? a[idx] : reset));
      a[idx] = x;
      s.insert(idx); // Mark this index as explicitly set
    } else if (t == 2) {
      ll x;
      scanf("%lld", &x);
      reset = x; // Record the value for new resets
      s.clear(); // Clear set since all future elements are reset
      sum = n * x; // Total sum is now n*x
    }
    printf("%lld\n", sum);
  }
}
/*
B. Stone Age Problem

Algorithms/Techniques: Offline processing with lazy updates and set-based tracking of explicit values.
Time Complexity: O(n + q log n) where n is the array size and q is number of queries.
Space Complexity: O(n) for storing the array and set.

The problem uses a set to track which indices have been explicitly set (not reset).
Type 1 query updates an element, adjusting the total sum accordingly by checking if the index was previously reset.
Type 2 query resets all elements to a new value; it efficiently updates the total sum without modifying individual elements.
*/

// https://github.com/VaHiX/codeForces/