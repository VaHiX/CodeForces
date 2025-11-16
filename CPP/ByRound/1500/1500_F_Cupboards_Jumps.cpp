// Problem: CF 1500 F - Cupboards Jumps
// https://codeforces.com/contest/1500/problem/F

/* 
 * Problem: F. Cupboards Jumps
 * 
 * Purpose: Given the differences between the maximum and minimum heights in every 
 *          three consecutive cupboards, reconstruct a sequence of n cupboards 
 *          that satisfies these constraints.
 * 
 * Algorithm: 
 *   - Use a greedy approach with a set to maintain valid ranges of height differences.
 *   - For each consecutive triplet, update the range of possible heights and 
 *     determine the appropriate values to maintain the constraints.
 *   - Finally, adjust the sequence to meet all constraints and ensure non-negative values.
 * 
 * Time Complexity: O(n log n) due to set operations in the main loop.
 * Space Complexity: O(n) for storing the heights and auxiliary arrays.
 * 
 * Approach:
 *   - Start with initial range [0, inf].
 *   - For each w_i, determine valid range for the next cupboard height.
 *   - Use a set to manage constraints and validate the solution.
 *   - Adjust final heights to ensure non-negativity.
 */

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>

using namespace std;
#define int long long
const int inf = 0x3f3f3f3f3f3f3f3f;
int n, k, a[1000009], b[1000009], t[1000009], op[1000009];
set<int> s;
int k1 = 1, k2, L, R;
int f(int x) { return x * k1 + k2; } // Helper function to transform values
int rf(int x) { return (x - k2) * k1; } // Reverse helper function
int get() { return (s.empty() ? f(L) : f(*s.begin())); } // Get next valid height
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n - 2; i++)
    cin >> a[i];
  L = 0;
  R = inf;
  for (int i = 1; i <= n - 2; i++) {
    int xl = rf(0), xr = rf(a[i]); // Calculate valid range for current value
    if (xl > xr)
      swap(xl, xr); // Ensure xl <= xr
    L = max(L, xl); // Update left bound
    R = min(R, xr); // Update right bound
    while (!s.empty() && (*s.begin()) < xl) // Remove values outside updated range
      s.erase(s.begin());
    while (!s.empty() && (*s.rbegin()) > xr)
      s.erase(--s.end());
    if (L > R && s.empty()) // Check if range is invalid
      return cout << "No\n", 0;
    if (s.find(rf(a[i])) != s.end() || L <= rf(a[i]) && rf(a[i]) <= R) // Check if value is valid
      L = 0, R = a[i], k1 = 1, k2 = 0, s.clear(), t[i + 1] = a[i]; // Reset for new phase
    else {
      t[i + 1] = get(); // Take first valid value from set or L
      k1 = -k1; // Flip sign for next phase
      k2 = -k2;
      k2 += a[i]; // Adjust offset
      s.insert(rf(a[i])); // Add current value to set
    }
  }
  t[n] = get(); // Final value
  for (int i = n - 1; i > 1; i--)
    if (t[i] != a[i - 1] && t[i + 1] != a[i - 1]) // Adjust remaining values to satisfy constraint
      t[i] = a[i - 1] - t[i + 1];
  for (int i = n - 1, op = 1; i > 1; i--) {
    if (op * t[i] + t[i + 1] < -a[i - 1] || op * t[i] + t[i + 1] > a[i - 1]) // Check constraint satisfaction
      op = -op; // Flip operation
    t[i] *= op; // Apply operation
  }
  for (int i = 1; i <= n; i++)
    b[i] = b[i - 1] + t[i]; // Build cumulative heights
  cout << "Yes\n";
  for (int i = 3; i <= n; i++)
    assert(max({b[i], b[i - 1], b[i - 2]}) - min({b[i], b[i - 1], b[i - 2]}) ==
           a[i - 2]); // Validate constraints
  int mn = inf;
  for (int i = 1; i <= n; i++)
    mn = min(mn, b[i]); // Find minimum height
  for (int i = 1; i <= n; i++)
    cout << b[i] - mn << ' '; // Output adjusted heights
  cout << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/