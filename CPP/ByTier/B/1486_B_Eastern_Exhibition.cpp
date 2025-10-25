// Problem: CF 1486 B - Eastern Exhibition
// https://codeforces.com/contest/1486/problem/B

/**
 * Problem: Eastern Exhibition
 * 
 * Purpose:
 *   This code determines the number of optimal positions to build an exhibition
 *   such that the sum of Manhattan distances from all houses to the exhibition is minimized.
 *   
 * Algorithm:
 *   - For each test case, we sort the x-coordinates and y-coordinates of the houses.
 *   - The optimal x-coordinate for the exhibition lies in the range [x[n/2], x[(n-1)/2]] inclusive.
 *   - Similarly for y-coordinates.
 *   - The number of valid positions is the product of ranges of x and y coordinates.
 *   
 * Time Complexity: O(n log n) per test case due to sorting.
 * Space Complexity: O(n) for storing the coordinates.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> x(n), y(n); // Store x and y coordinates separately
    for (ll p = 0; p < n; p++) {
      scanf("%lld %lld", &x[p], &y[p]); // Read each house's coordinates
    }
    sort(x.begin(), x.end()); // Sort x-coordinates
    sort(y.begin(), y.end()); // Sort y-coordinates
    
    ll dx = x[n / 2] - x[(n - 1) / 2] + 1; // Width of optimal x range
    ll dy = y[n / 2] - y[(n - 1) / 2] + 1; // Height of optimal y range
    
    ll ans = dx * dy; // Total number of valid positions
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/