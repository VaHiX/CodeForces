// Problem: CF 1585 C - Minimize Distance
// https://codeforces.com/contest/1585/problem/C

/*
C. Minimize Distance
Algorithms/Techniques: Greedy, Sorting
Time Complexity: O(n log n) per test case due to sorting; overall is O(n log n) over all test cases
Space Complexity: O(n) for storing the vectors a and b

The problem involves finding the minimum distance to deliver bags to depots on a number line.
We split the depots into positive (a) and negative (b) positions, sort them,
and use a greedy approach to minimize total travel by picking the furthest depot
in each trip. We must account for the fact that we need to go back to the origin
after delivering a bag, so we double the distance. However, one final trip to the
farthest depot (either positive or negative) doesn't require returning to origin,
so we subtract it once.
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
    std::vector<ll> a, b; // 'a' stores positive positions, 'b' stores negative positions
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      if (x > 0) {
        a.push_back(x); // Store positive depot positions
      } else {
        b.push_back(-x); // Store absolute value of negative depot positions
      }
    }
    sort(a.begin(), a.end()); // Sort positive positions in ascending order
    sort(b.begin(), b.end()); // Sort negative positions in ascending order
    ll total(0);
    for (long p = a.size() - 1; p >= 0; p -= k) {
      total += 2 * a[p]; // Add twice the distance for each trip to farthest unvisited depot (positive)
    }
    for (long p = b.size() - 1; p >= 0; p -= k) {
      total += 2 * b[p]; // Add twice the distance for each trip to farthest unvisited depot (negative)
    }
    if (a.empty()) {
      a.push_back(0); // Ensures at least one element for back() access
    } else if (b.empty()) {
      b.push_back(0); // Ensures at least one element for back() access
    }
    total -= (a.back() > b.back() ? a.back() : b.back()); // Subtract the final leg of journey that doesn't require return to origin
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/