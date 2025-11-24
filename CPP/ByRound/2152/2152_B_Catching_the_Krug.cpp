// Problem: CF 2152 B - Catching the Krug
// https://codeforces.com/contest/2152/problem/B

#include <algorithm>
#include <iostream>

#define int long long
using namespace std;

// Flowerbox describing the code purpose, algorithms, time and space complexity
/*
 * Problem: Catching the Krug
 * Purpose: Determine the survival time of the Krug in a grid-based game where 
 *          the Krug and Doran move optimally.
 * Algorithms/Techniques:
 *   - Mathematical analysis of movement patterns on a grid.
 *   - Greedy strategy for optimal play by both players.
 *   - Grid distance calculation with Manhattan and Chebyshev metrics.
 *
 * Time Complexity: O(1) per test case.
 * Space Complexity: O(1).
 */

void solve() {
  int n, rk, ck, rd, cd;
  cin >> n >> rk >> ck >> rd >> cd;
  int ans1 = 0, ans2 = 0;
  
  // Calculate minimal turns needed for Krug to escape in row direction
  if (rk > rd) {
    ans1 = n - rk + rk - rd; // Distance calculation based on grid constraints
  } else if (rk < rd) {
    ans1 = rd; // Direct distance to reach the target
  }
  
  // Calculate minimal turns needed for Krug to escape in column direction
  if (ck > cd) {
    ans2 = n - ck + ck - cd; // Distance calculation based on grid constraints
  } else if (ck < cd) {
    ans2 = cd; // Direct distance to reach the target
  }
  
  // Output maximum time, or -1 if infinite survival is possible
  cout << max(ans1, ans2) << '\n';
}

signed main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/