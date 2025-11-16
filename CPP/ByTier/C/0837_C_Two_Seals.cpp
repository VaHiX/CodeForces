// Problem: CF 837 C - Two Seals
// https://codeforces.com/contest/837/problem/C

/*
Code Purpose:
This program solves the problem of selecting two different seals to place on a rectangular piece of paper such that their combined impression area is maximized, under the constraint that each seal can be rotated and impressions must not overlap.

Algorithms/Techniques:
- Brute-force approach: Try all combinations of two seals (including rotations).
- For each pair of seals, check if both fit on the paper and can be placed without overlapping.
- Compute the maximum total area among valid combinations.

Time Complexity:
O(n^2), where n is the number of seals. Since we iterate through all pairs of seals (including rotations), and each check involves constant-time operations.

Space Complexity:
O(n), to store the dimensions of the seals (original and rotated versions).
*/

#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const ll N = 1e5 + 100;
int n, a, b, x[N], y[N], ans = 0;
int main() {
  cin >> n >> a >> b;
  // Read seal dimensions and store both original and rotated versions
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> y[i];
    x[i + n] = y[i], y[i + n] = x[i];  // Store rotated version
  }
  // Check all pairs of seals (including rotations)
  for (int i = 1; i < 2 * n; i++) {
    for (int j = i + 1; j <= 2 * n; j++) {
      // Ensure that we are not picking same seal twice (in original and rotated form)
      // Also check if both seals fit on the paper in their current orientation
      // And verify that the two impressions don't overlap
      if (j != i + n && (x[i] <= a) && (y[i] <= b) && (x[j] <= a) &&
          (y[j] <= b) && (x[i] + x[j] <= a || y[i] + y[j] <= b)) {
        ans = max(ans, x[i] * y[i] + x[j] * y[j]);  // Update max area
      }
    }
  }
  cout << ans;
}


// https://github.com/VaHiX/CodeForces/