// Problem: CF 1185 A - Ropewalkers
// https://codeforces.com/contest/1185/problem/A

/*
 * Problem: Ropewalkers
 * Algorithm: Greedy + Sorting
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * Given three initial positions of ropewalkers (a, b, c) and minimum required
 * distance d, find the minimum time to move them such that all pairwise
 * distances are at least d.
 *
 * Strategy:
 * - Sort the positions to simplify analysis
 * - Calculate how much each pair needs to be separated
 * - Determine minimal moves needed using greedy approach
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  std::vector<ll> x(3);  // Vector to hold sorted positions
  ll d;                  // Minimum required distance
  scanf("%lld %lld %lld %lld", &x[0], &x[1], &x[2], &d);  // Read input values
  sort(x.begin(), x.end());  // Sort positions to analyze gaps between adjacent

  // Calculate how much we need to move the first gap (between x[0] and x[1])
  ll t1 = x[0] - x[1] + d;
  // Calculate how much we need to move the second gap (between x[1] and x[2])
  ll t2 = x[1] + d - x[2];

  // Sum up required moves, ensuring non-negative values
  ll t = (t1 > 0 ? t1 : 0) + (t2 > 0 ? t2 : 0);
  printf("%lld\n", t);  // Output the result
  return 0;
}


// https://github.com/VaHiX/codeForces/