// Problem: CF 2052 H - Hunting Hoglins in Hogwarts
// https://codeforces.com/contest/2052/problem/H

/*
 * Problem: Adrenaline Rush
 * Purpose: Determine the maximum number of overtakes that could have occurred in a race,
 *          given the final order of cars, such that no car overtakes another more than once.
 *
 * Algorithm/Techniques:
 *   - Binary search-like approach using intervals to simulate swaps and overtake events.
 *   - A recursive-like process where we split ranges and handle each half separately,
 *     maintaining a stack-like structure for backtracking.
 *   - Uses a clever way to detect if an overtaking event resulted in a change.
 *
 * Time Complexity:
 *   O(n log n) - Each element is processed a logarithmic number of times due to splitting intervals.
 *
 * Space Complexity:
 *   O(n) - For storing intervals and recursion stack (in practice, this is bounded by the depth of recursion).
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;

void solve(ll n) {
  vector<pair<ll, ll>> ran = {{1, n}}; // Initialize interval [1, n]
  while (true) {
    vector<pair<ll, ll>> nxt; // Next set of intervals
    bool ok = 0;              // Flag to indicate if we found a valid car to overtake
    for (auto [l, r] : ran) { // Iterate through current intervals
      if (l > r)
        continue;
      ll m = (l + r) >> 1;          // Midpoint of interval
      nxt.emplace_back(l, m - 1);   // Left half
      nxt.emplace_back(m + 1, r);   // Right half
      cout << m << endl;            // Output midpoint (candidate car for overtaking)
      int cu;
      cin >> cu;                    // Read result of this query
      if (cu >= 2)
        return;                     // If we already have multiple changes, stop
      if (cu == 1) {                // If the candidate car is in correct position at this step
        ok = 1;
        break;
      }
    }
    while (!ok) {
      cout << 0 << endl;            // Output 0 (placeholder)
      int cu;
      cin >> cu;
      ok = cu;                      // Wait until we get a valid response
    }
    reverse(nxt.begin(), nxt.end()); // Reverse to simulate proper backtracking
    ran = nxt;                       // Update intervals with new set
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ll n, t;
  cin >> n >> t;
  while (t--)
    solve(n);
}


// https://github.com/VaHiX/codeForces/