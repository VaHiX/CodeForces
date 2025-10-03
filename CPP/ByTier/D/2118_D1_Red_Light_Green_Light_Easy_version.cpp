// Problem: CF 2118 D1 - Red Light, Green Light (Easy version)
// https://codeforces.com/contest/2118/problem/D1

/*
 * Problem: D1. Red Light, Green Light (Easy version)
 *
 * Purpose:
 *   Simulates a movement on a strip with traffic lights that switch between red and green.
 *   The task is to determine if a player starting at various positions will eventually leave the strip.
 *
 * Algorithms/Techniques:
 *   - Preprocessing of traffic light states based on periodic patterns (modular arithmetic).
 *   - Using maps to track leftmost/rightmost occurrence of each modular class for efficient lookups.
 *   - Simulation with cycle detection (visited tracking) to avoid infinite loops.
 *
 * Time Complexity: O(n * k + q * n)
 * Space Complexity: O(n * k)
 */

#include <iostream>
#include <map>
#include <string.h>
#define int long long
using namespace std;
const int N = 1e5 + 1;
int T, n, k, q, x, p[N], a[N], l[N], r[N], v[N][2];
map<int, int> L, R; // L maps (p[i] + a[i]) % k to last index, R maps (p[i] - a[i]) % k to last index
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
      cin >> p[i];
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    L.clear();
    R.clear();
    
    // Forward pass to compute 'l' array: leftmost cell with same (p[i] + a[i]) % k
    for (int i = 1; i <= n; i++) {
      l[i] = L[(p[i] + a[i]) % k]; // l[i] = previous index having same (p[i] + a[i]) % k
      L[(p[i] + a[i]) % k] = i;    // update latest index for this key in L
    }

    // Backward pass to compute 'r' array: rightmost cell with same (p[i] - a[i]) % k
    for (int i = n; i >= 1; i--) {
      if (!R.count(((p[i] - a[i]) % k + k) % k))
        r[i] = n + 1;
      else
        r[i] = R[((p[i] - a[i]) % k + k) % k];
      R[((p[i] - a[i]) % k + k) % k] = i;
    }

    cin >> q;
    while (q--) {
      cin >> x;
      int pos = n + 1, dir = 0, yes = 1;
      
      // Find the rightmost position from which you can start moving towards increasing positions
      for (int j = n; j >= 1; j--)
        if (p[j] >= x && (x + a[j]) % k == p[j] % k)
          pos = j;

      memset(v, 0, sizeof(v)); // mark all visited states as unvisited

      while (pos != 0 && pos != n + 1) {
        if (v[pos][dir]) {       // cycle detected
          cout << "No\n";
          yes = 0;
          break;
        }
        v[pos][dir] = 1;         // mark current (position, direction) as visited

        if (dir)
          pos = r[pos];        // move to rightmost cell with same key
        else
          pos = l[pos];        // move to leftmost cell with same key
        
        dir ^= 1;                // toggle direction
      }
      
      if (yes)
        cout << "Yes\n";
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/