// Problem: CF 2169 E - Points Selection
// https://codeforces.com/contest/2169/problem/E

/*
Code Purpose:
This code solves the game problem where Alice removes some points and Bob draws a rectangle enclosing the remaining points.
Alice wants to maximize the total score (sum of removed point costs + rectangle perimeter), while Bob wants to minimize it.
The solution uses a mathematical approach to find the optimal strategy for both players.

Algorithms/Techniques:
- Game theory optimization with min-max strategy
- Coordinate compression and geometric optimization
- Mathematical transformation of the problem into maximizing linear combinations

Time Complexity: O(n) - Single pass through all points
Space Complexity: O(1) - Only using constant extra space (arrays are of fixed size)
*/

#include <algorithm>
#include <iostream>

#define int long long
using namespace std;
const int mxn = 3e5 + 5;
int x[mxn], y[mxn], c[mxn], n;
void solve() {
  int sum = 0;
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> x[i];
  for (int i = 1; i <= n; i++)
    cin >> y[i];
  int mn = 1145141919810233333ll, ans = -1145141919810233333ll;
  for (int i = 1; i <= n; i++)
    cin >> c[i], mn = min(mn, c[i]), sum += c[i];
  ans = max(ans, -mn); // Handle case where Alice removes no points (minimal cost point)
  int xf = 0, yf = 0, xz = 0, yz = 0;
  int xfyf = 0, xfyz = 0, xzyf = 0, xzyz = 0;
  xf = yf = xz = yz = -1145141919810233333ll;
  xfyf = xfyz = xzyf = xzyz = -1145141919810233333ll;
  for (int i = 1; i <= n; i++) {
    // Calculate maximum values for different combinations of x and y coordinates
    // These represent the optimal rectangle boundaries for different point removal strategies
    xf = max(xf, -c[i] - 2 * x[i]); // For x_min boundary
    xz = max(xz, -c[i] + 2 * x[i]); // For x_max boundary
    yf = max(yf, -c[i] - 2 * y[i]); // For y_min boundary
    yz = max(yz, -c[i] + 2 * y[i]); // For y_max boundary
    xfyf = max(xfyf, -c[i] - 2 * x[i] - 2 * y[i]); // Both x_min and y_min
    xfyz = max(xfyz, -c[i] - 2 * x[i] + 2 * y[i]); // x_min and y_max
    xzyf = max(xzyf, -c[i] + 2 * x[i] - 2 * y[i]); // x_max and y_min
    xzyz = max(xzyz, -c[i] + 2 * x[i] + 2 * y[i]); // Both x_max and y_max
  }
  // Combine the best possible combinations of x and y boundaries
  xfyf = max(xfyf, xf + yf); // Best x_min + y_min combination
  xfyz = max(xfyz, xf + yz); // Best x_min + y_max combination  
  xzyf = max(xzyf, xz + yf); // Best x_max + y_min combination
  xzyz = max(xzyz, xz + yz); // Best x_max + y_max combination
  ans = max(ans, xfyf + xzyz); // Combine opposite corners for optimal rectangle
  ans = max(ans, xzyf + xfyz); // Another combination of opposite corners
  cout << ans + sum << endl; // Add original sum of all points to get final score
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  for (; T--;)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/