// Problem: CF 505 C - Mr. Kitayuta, the Treasure Hunter
// https://codeforces.com/contest/505/problem/C

/*
Algorithm: Dynamic Programming with State Compression
Approach:
- Use dynamic programming where f[i][j] represents the maximum number of gems that can be collected
  when landing on island i with the previous jump length being j.
- The state transitions consider the three possible next jump lengths: l-1, l, l+1.
- The jump length is tracked relative to the initial jump length d (mapped to index offset of 30000).

Time Complexity: O(n * d) where n <= 30000 and d <= 30000
Space Complexity: O(n * d) for the DP table f[i][j]

Note: The algorithm uses a fixed-size DP table to optimize space and speed. 
      The jump length is offset by 30000 to handle negative indices in the DP array.
*/

#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int ds = 305;
int n, m, p, f[30005][707], v[30005], ans;
signed main() {
  memset(f, 0x80, sizeof(f)); // Initialize DP array with negative infinity
  ios_base::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; v[p]++, i++) // Count gems at each island
    cin >> p;
  ans = f[m][ds] = v[0] + v[m]; // Initialize first jump from 0 to m
  for (int i = m + 1; i <= p; i++) // For each island after the first jump
    for (int j = -ds; j <= ds; j++) {
      if (((m + j) > 0) && ((m + j) <= i)) // Ensure jump length is positive and valid
        f[i][ds + j] = max(f[i][ds + j], max({f[i - (m + j)][ds + j],
                                              f[i - (m + j)][ds + j - 1],
                                              f[i - (m + j)][ds + j + 1]}) +
                                             v[i]); // Update DP state by considering all three possible previous jumps
      ans = max(ans, f[i][ds + j]); // Keep track of global maximum
    }
  cout << ans << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/