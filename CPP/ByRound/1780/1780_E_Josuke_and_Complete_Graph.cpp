// Problem: CF 1780 E - Josuke and Complete Graph
// https://codeforces.com/contest/1780/problem/E

/*
 * Problem: Josuke and Complete Graph
 * Algorithm: Number theory, inclusion-exclusion, mathematical optimization
 * 
 * Purpose:
 *   Given a complete graph with vertices labeled from 1 to 10^18, where the weight of the edge
 *   between vertices u and v is gcd(u, v), we are to find the number of distinct edge weights
 *   in a subgraph defined by vertices in the range [l, r].
 * 
 * Approach:
 *   - The key insight is that for any edge (u, v), its weight is gcd(u, v).
 *   - We iterate over all possible values of gcd(u, v) = d, which means d divides both u and v.
 *   - If d = gcd(u, v), then we can write u = d * u', v = d * v', where gcd(u', v') = 1.
 *   - So, for a fixed d, we count how many pairs (u', v') exist in [l/d, r/d] such that gcd(u', v') = 1.
 *   - This can be done efficiently using inclusion-exclusion principle or Euler's totient function concept,
 *     but here we use an optimized mathematical trick involving grouping values based on quotients.
 * 
 * Time Complexity: O(sqrt(r)) per test case due to the optimized iteration over divisors
 * Space Complexity: O(1) - only using a few variables
 */

#include <algorithm>
#include <iostream>

#define int long long
using namespace std;

int t, j, l, r, ans;

signed main() {
  cin >> t;
  while (t--) {
    cin >> l >> r;
    ans = 0;
    // Loop to compute number of distinct GCD values.
    // We process ranges of i such that (l-1)/i remains constant.
    for (int i = 1; i < l; i = j + 1) {
      j = (l - 1) / ((l - 1) / i);  // Find the largest j such that (l-1)/i == (l-1)/j
      // Count number of valid pairs in ranges [i, j] with respect to the condition.
      ans += max(0ll, min(j, r / ((l - 1) / i + 2)) - i + 1);
    }
    // Add contribution from the range [l, r] where gcd(u,v) = 1 for some u in [l, r], v in [l, r]
    cout << ans + max(0ll, r / 2 - l + 1) << endl;
  }
}


// https://github.com/VaHiX/CodeForces/