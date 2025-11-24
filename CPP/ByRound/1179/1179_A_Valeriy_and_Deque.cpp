// Problem: CF 1179 A - Valeriy and Deque
// https://codeforces.com/contest/1179/problem/A

/*
 * Problem: Valeriy and Deque
 * Algorithms/Techniques: Simulation with deque operations, optimization by observing pattern after first n-1 steps
 * Time Complexity: O(n + q) where n is the size of the deque and q is the number of queries.
 * Space Complexity: O(n) for storing the deque and auxiliary arrays.
 *
 * The algorithm simulates the deque operations until the maximum element reaches the front,
 * then uses a pattern to answer queries beyond that point efficiently.
 */

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll n, q;
  scanf("%lld %lld", &n, &q);
  std::vector<ll> a(2 * n + 1); // Double the size to allow easy rotation
  for (ll p = 1; p <= n; p++) {
    scanf("%lld", &a[p]);
  }
  
  // Arrays to store original values at each position for queries
  std::vector<ll> ca(2 * n + 7), cb(2 * n + 7);
  
  // Initialize the arrays with first n elements and simulate first few operations
  for (ll p = 1; p <= n; p++) {
    ca[p] = a[p];
    cb[p] = a[p + 1];
    if (a[p] > a[p + 1]) {
      ll tmp = a[p];
      a[p] = a[p + 1];
      a[p + 1] = tmp;
    }
    a[n + p] = a[p]; // Duplicate the deque to handle wrap-around
  }

  while (q--) {
    ll x;
    scanf("%lld", &x);
    
    // If the query is within first n steps, directly return stored values
    if (x <= n) {
      printf("%lld %lld\n", ca[x], cb[x]);
    } else {
      // After first n-1 operations, maximum element will be at front.
      // So we can directly calculate result from known pattern.
      printf("%lld %lld\n", a[n + 1], a[n + 2 + (x - 2) % (n - 1)]);
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/