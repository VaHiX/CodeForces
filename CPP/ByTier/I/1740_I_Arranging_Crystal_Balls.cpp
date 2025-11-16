// Problem: CF 1740 I - Arranging Crystal Balls
// https://codeforces.com/contest/1740/problem/I

/*
Algorithm: 
This solution solves the problem of minimizing operations to reduce all crystal ball values to 0 in a circular arrangement.
It uses a combination of:
1. Difference constraint technique to transform the circular problem into a linear one
2. Dynamic programming with sliding window optimization for minimizing operations
3. Mathematical properties (GCD, modular arithmetic) for cycle detection and optimization

Time Complexity: O(nm + m^2)
Space Complexity: O(n + m)

The approach:
1. Uses difference array to convert circular constraints into linear ones
2. Applies DP with slope optimization to find minimum operations for each cycle
3. Combines results using GCD properties to get final answer
*/

#include <iostream>
#include <algorithm>

using namespace std;
const long long N = 1e6 + 10, inf = 1e18;
int n, l, m, c, d, g, a[N], ta[N], b[N], L[N], R[N], q[N], ql, qr;
long long dp[N], p[N * 2], w[N], W[N], ans = inf;
int gcd(int a, int b) { return (b == 0 ? a : gcd(b, a % b)); }
int main() {
  cin >> n >> m >> c;
  d = gcd(n, c); // Calculate GCD of n and c to find cycle length
  l = n / d; // Number of elements in each cycle
  for (int i = 0; i < n; i++)
    cin >> ta[i]; // Read initial values
  a[0] = (ta[0] - ta[n - 1] + m) % m; // First difference
  g = ta[n - 1]; // Store the last element for final check
  for (int i = 1; i < n; i++)
    a[i] = (ta[i] - ta[i - 1] + m) % m; // Compute differences
  for (int i = 1; i < m; i++)
    dp[i] = inf; // Initialize dp array
  for (int i = 0, t, tp; i < d; i++) { // Process each cycle
    for (int j = 0; j < l; j++) {
      b[j] = a[t = (i + 1ll * j * c) % n]; // Get elements in current cycle
      if (j)
        (b[j] += b[j - 1]) %= m; // Prefix sum of differences
      if (t + c >= n) // If we're near the end of array
        g = (g - b[j] + m) % m; // Update g with final difference
    }
    if (b[l - 1]) { // If last element is not 0, impossible to solve
      cout << -1 << '\n';
      return 0;
    }
    for (int j = 0; j < m; j++)
      w[j] = min(j, m - j); // Precompute cost to reduce to 0
    for (int j = 0; j < l - 1; j++) // Update costs based on prefix sums
      for (int k = 0; k < m; k++) {
        t = (b[j] + k) % m;
        w[k] += min(t, m - t); // Add cost for this offset
      }
    tp = 0; // Initialize number of segments
    tp++; // First segment starts at 0
    L[tp] = 0;
    R[tp] = 0;
    W[tp] = w[1] - w[0]; // Initial slope
    for (int j = 2; j < m; j++) { // Segment the slopes
      if (w[j] - w[j - 1] != W[tp]) { // If slope changes
        R[tp] = j - 1; // End current segment
        tp++; // Start new segment
        L[tp] = j;
        R[tp] = 0;
        W[tp] = w[j] - w[j - 1]; // Update slope
      }
    }
    R[tp] = m - 1; // End last segment
    for (int j = 0; j < m * 2; j++)
      p[j] = inf; // Initialize array for current cycle's DP
    for (int j = 1, TL, TR; j <= tp; j++) { // Process each segment
      ql = 1;
      qr = 0;
      TL = L[j];
      TR = R[j];
      for (int k = TL; k < m + TR; k++) {
        while (ql <= qr && q[ql] < k - TR) // Remove outdated elements
          ql++;
        if (k - TL < m) { // Add new element if in valid range
          while (ql <= qr && dp[k - TL] <= dp[q[qr]] + W[j] * (k - TL - q[qr]))
            qr--;
          q[++qr] = k - TL;
        }
        if (ql <= qr) // Update dp if valid
          p[k] = min(p[k], dp[q[ql]] + w[k - q[ql]]);
      }
    }
    for (int j = 0; j < m; j++)
      dp[j] = min(p[j], p[m + j]); // Update DP with current cycle's values
  }
  for (int i = 0; i < m; i++) // Find minimum answer
    if (g == 1ll * c / d * i % m) // Check if this combination is valid
      ans = min(ans, dp[i]); // Update minimum
  if (ans >= inf) // If no solution exists
    cout << -1 << '\n';
  else
    cout << ans << '\n'; // Print answer
  return 0;
}


// https://github.com/VaHiX/CodeForces/