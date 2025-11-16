// Problem: CF 1741 F - Multi-Colored Segments
// https://codeforces.com/contest/1741/problem/F

/*
Purpose: 
This code solves the problem of finding the minimum distance from each segment to the nearest segment of a different color.
The approach uses a sweep line technique with coordinate compression:
1. For each segment, we create two events (left and right endpoints)
2. We sort all events by x-coordinate
3. We process events using a sweep line to maintain the furthest right endpoint seen so far for each color
4. For each right endpoint, we calculate the minimum distance to segments of different colors

Algorithms/Techniques:
- Sweep line algorithm
- Coordinate compression
- Event processing with two passes (forward and reverse)
- Segment intersection and distance calculation

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing events and results
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

#define int long long
using namespace std;
const int N = 2e6 + 50;
const int inf = 2e9;
signed main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<array<int, 5>> v(n << 1); // Create 2*n events (left and right for each segment)
    for (int i = 0; i < n; i++) {
      int l, r, c;
      cin >> l >> r >> c;
      // Store left endpoint with flag 0
      v[i << 1] = {l, r, c, i, 0};
      // Store right endpoint with flag 1 (this helps us distinguish left/right during sweep)
      v[i << 1 | 1] = {r, l, c, i, 1};
    }
    sort(v.begin(), v.end()); // Sort by x-coordinate (l or r)
    vector<int> res(n, inf); // Result array for each segment
    for (int k = 0; k < 2; k++) {
      array<int, 2> f[2]; // Maintain two furthest right endpoints for each color
      f[0] = f[1] = {-inf, -1}; // Initialize with -inf and -1
      for (auto [l, r, c, i, o] : v) 
        if (o) {
          // Process right endpoint
          // For each right endpoint, check the furthest right endpoints of different colors
          for (auto [ll, cc] : f)
            if (cc != c) // Different color
              res[i] = min(res[i], max(0LL, r - ll)); // Calculate distance (or 0)
        } else {
          // Process left endpoint  
          array<int, 2> g = {r, c}; // Current right endpoint and color
          if (g > f[0]) // Update the maximum if current is greater
            swap(g, f[0]);
          if ((g > f[1] && g[1] != f[0][1]) || f[0][1] == f[1][1]) 
            f[1] = g; // Update second maximum
        }
      reverse(v.begin(), v.end()); // Reverse to process in the opposite direction
      for (auto &[l, r, c, i, o] : v) {
        // Negate coordinates to simulate reverse sweep
        l = -l;
        r = -r;
        o ^= 1; // Toggle flag (0->1, 1->0)
      }
    }
    for (auto it : res) // Output results
      cout << it << " ";
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/