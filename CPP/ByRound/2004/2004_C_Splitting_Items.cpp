// Problem: CF 2004 C - Splitting Items
// https://codeforces.com/contest/2004/problem/C

/*
C. Splitting Items

Algorithm:
- Greedy approach with optimal play simulation.
- Sort items in descending order to simulate optimal choices.
- Alice picks first (odd turns), Bob picks second (even turns).
- For each pair of picks (Alice then Bob), we try to minimize the difference A - B by increasing Bob's selected value optimally within k.
- The key idea is that when Alice chooses an item, Bob will take the next best item. We want to distribute the total increment k so as to reduce A - B as much as possible.

Time Complexity: O(n log n) per test case due to sorting; overall O(t * n log n)
Space Complexity: O(n) for storing the array of items

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
    sort(a.rbegin(), a.rend()); // Sort in descending order to ensure optimal selection
    ll A(0), B(0);
    for (ll p = 0; p < n; p++) {
      if (p % 2) {
        // Bob's turn: he takes item at index p
        // Compute how much we can increase it to match Alice's previous choice minus the gap
        ll diff = (a[p - 1] - a[p]); // Difference between last two items in the sorted list
        diff = (diff < k ? diff : k); // Cap the increment at k
        k -= diff; // Decrease available increments
        B += a[p] + diff; // Add Bob's value plus applied increment to his total
      } else {
        // Alice's turn: she takes item at index p, so add directly to A
        A += a[p];
      }
    }
    printf("%lld\n", A - B); // Output final score difference
  }
}


// https://github.com/VaHiX/codeForces/