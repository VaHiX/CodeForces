// Problem: CF 1629 A - Download More RAM
// https://codeforces.com/contest/1629/problem/A

/*
 * Problem: A. Download More RAM
 * Purpose: Given initial RAM 'k', and a list of software upgrades with costs 'a' and benefits 'b',
 *          determine the maximum possible RAM after optimally applying upgrades.
 *          Each upgrade can only be used once, and must be affordable with current RAM.
 *
 * Algorithm: Greedy approach
 *   - Sort the software by cost 'a' in ascending order
 *   - Apply upgrades in order of increasing cost (as long as we have enough RAM)
 *   - Add benefit 'b' to available RAM after each successful application
 *
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing the pairs of (cost, benefit)
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<std::pair<long, long>> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p].first);  // Read cost 'a'
    }
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p].second); // Read benefit 'b'
    }
    sort(v.begin(), v.end());       // Sort by cost ascending
    long ram(k);
    for (long p = 0; p < n; p++) {
      if (ram < v[p].first) {       // If we can't afford this upgrade
        break;
      }
      ram += v[p].second;           // Apply the upgrade and gain benefit
    }
    printf("%ld\n", ram);
  }
}


// https://github.com/VaHiX/codeForces/