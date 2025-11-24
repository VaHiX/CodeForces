// Problem: CF 2038 K - Grid Walk
// https://codeforces.com/contest/2038/problem/K

/*
K. Grid Walk

Task: Find the minimum cost path from (1,1) to (n,n) in an n×n grid where each cell (i,j) has cost gcd(i,a) + gcd(j,b).
The movement is restricted to right or down only.

Algorithm:
- Uses dynamic programming with periodicity optimization.
- Observes that gcd values repeat every lcm(a, b) steps, and uses this to reduce the DP state space.
- Precompute sum of gcds for first period of a and b.
- Then use transition to compute minimum cost using previous states.

Time Complexity: O(n * (a + b)) - Due to DP transitions over reduced periods
Space Complexity: O(a + b) - For storing DP table over periods

*/

#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 150;
int n, a, b, x, y;
ll sum, dp[N][N];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> a >> b;
  // Find the largest x such that gcd(x, a) == 1
  for (x = n; x > 0; --x)
    if (__gcd(x, a) == 1)
      break;
  // Find the largest y such that gcd(y, b) == 1
  for (y = n; y > 0; --y)
    if (__gcd(y, b) == 1)
      break;
  // Compute prefix sums of gcd values for a and b in their period
  for (int i = 1; i <= x; ++i)
    sum += __gcd(i, a);
  for (int i = 1; i <= y; ++i)
    sum += __gcd(i, b);
  // Initialize dp table with large value
  memset(dp, 0x3f3f, sizeof dp);
  // Base case: dp[1][1] is the total cost from start to first period
  dp[1][1] = sum + x + y - 2;
  // Fill DP table using transitions considering periodic nature of gcd functions
  for (int i = x; i <= n; ++i)
    for (int j = y; j <= n; ++j) {
      if (i == x && j == y)
        continue;
      // Transition: take minimum from either coming from up or left
      dp[i - x + 1][j - y + 1] =
          min(dp[i - x][j - y + 1], dp[i - x + 1][j - y]);
      // Add current cell's cost to the accumulated sum
      dp[i - x + 1][j - y + 1] += __gcd(i, a) + __gcd(j, b);
    }
  // Output final result
  cout << dp[n - x + 1][n - y + 1];
  return 0;
}


// https://github.com/VaHiX/codeForces/