// Problem: CF 1515 C - Phoenix and Towers
// https://codeforces.com/contest/1515/problem/C

/*
 * Problem: Phoenix and Towers
 * Algorithm: Greedy with Multiset
 * Time Complexity: O(n * log m) per test case
 * Space Complexity: O(n + m)
 * 
 * Approach:
 * - We need to distribute n blocks into m towers such that the height difference
 *   between any two towers is at most x.
 * - To achieve this, we use a greedy strategy with a multiset to keep track of
 *   the current heights of each tower. The multiset stores pairs of (tower_height, tower_index).
 * - For each block, we place it on the tower with the smallest current height.
 * - This greedy approach ensures that the difference between the tallest and shortest
 *   towers is minimized, which helps in maintaining the constraint that the difference
 *   doesn't exceed x.
 * 
 * Key Idea:
 * - Use a multiset to efficiently get the tower with minimum height.
 * - Update the height of the selected tower after placing the block.
 * - Record which tower each block belongs to.
 */

#include <cstdio>
#include <set>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m, x;
    scanf("%lld %lld %lld", &n, &m, &x);
    std::multiset<std::pair<ll, ll>> s;
    for (ll p = 0; p < m; p++) {
      s.insert(std::make_pair(0, p)); // Initialize all towers with height 0
    }
    std::vector<ll> w(n);
    for (ll p = 0; p < n; p++) {
      ll u;
      scanf("%lld", &u);
      std::multiset<std::pair<ll, ll>>::iterator lowest = s.begin(); // Get tower with minimum height
      ll where = lowest->second;
      u += lowest->first; // Add block to this tower
      s.erase(lowest);    // Remove the old entry
      s.insert(std::make_pair(u, where)); // Insert updated tower height
      w[p] = where;       // Record which tower this block belongs to
    }
    puts("YES");
    for (ll p = 0; p < n; p++) {
      printf("%lld ", 1 + w[p]); // Output 1-based index of tower
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/