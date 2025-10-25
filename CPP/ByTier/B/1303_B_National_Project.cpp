// Problem: CF 1303 B - National Project
// https://codeforces.com/contest/1303/problem/B

/*
B. National Project
Purpose: 
  Given a highway of length n, and a repeating pattern of g good days followed by b bad days,
  determine the minimum number of days to repair the entire highway such that at least half
  of the units have high-quality pavement (i.e., laid on good days).

Algorithm:
  - For each test case, calculate how many good days are needed to achieve at least ceil(n/2) good units.
  - Use a greedy approach: group good days into periods of (g + b) days, and count full cycles needed.
  - Handle leftover good days appropriately.
  - Return the maximum between total required days and n (if all days are needed due to constraint).

Time Complexity: O(1) per test case
Space Complexity: O(1)
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, g, b;
    scanf("%lld %lld %lld", &n, &g, &b);
    
    // Calculate minimum good days needed to ensure at least half of the highway is high-quality
    ll h = (n + 1) / 2; // ceil(n/2)
    
    // Number of full cycles of (g + b) days needed to cover 'h' good days
    ll r = h / g; // Full groups of g good days
    
    // Remaining good days after full groups
    ll m = h % g; 

    // Calculate total days required based on full cycles and remaining good days
    // Each group is g good + b bad days = (g + b) total days per cycle
    // If there are no remaining 'm' good days, subtract 'b' since the last group was incomplete
    ll res = r * (g + b) + (m ? m : -b);
    
    // Ensure we don't return fewer than n days, as all units must be repaired
    res = (res > n) ? res : n;
    
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/