// Problem: CF 1993 E - Xor-Grid Problem
// https://codeforces.com/contest/1993/problem/E

/*
Algorithm: Bitmask Dynamic Programming + Graph Optimization
Time Complexity: O(2^n * n^2 + 2^m * m^2 + n * m)
Space Complexity: O(2^n * n + 2^m * m + n * m)
*/

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const ll e18 = 1e18;
int dp[1 << 16][16];
void sailor_problem(int n, const vector<vector<int>> &ds, vector<int> &ans) {
  // Initialize dp table with large values
  for (int i = 0; i < (1 << n); i++)
    for (int j = 0; j < n; j++)
      dp[i][j] = 1e9;
  
  // Base case: single element subset
  for (int i = 0; i < n; i++) {
    dp[1 << i][i] = 0;
  }
  
  // Fill dp table using bitmask
  for (int ms = 0; ms < (1 << n); ms++) {
    for (int ls = 0; ls < n; ls++) {
      if ((ms & (1 << ls)) == 0)
        continue;
      int nms = ms ^ (1 << ls); // Remove current element from mask
      for (int i = 0; i < n; i++)
        dp[ms][ls] = min(dp[ms][ls], dp[nms][i] + ds[ls][i]); // Update minimum cost
    }
  }
  
  // Calculate final answer
  for (int ex = 0; ex < n; ex++) {
    for (int i = 0; i < n; i++) {
      ans[ex] = min(ans[ex], dp[((1 << n) - 1) ^ (1 << ex)][i]); // Exclude current element and find minimum
    }
  }
}
int a[16][16];
vector<vector<vector<int>>> ds1(16, vector<vector<int>>(16, vector<int>(16))),
    ds2(16, vector<vector<int>>(16, vector<int>(16)));
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    // Initialize border elements to 0
    for (int i = 0; i <= n; i++)
      a[i][0] = 0;
    for (int j = 0; j <= m; j++)
      a[0][j] = 0;
    
    // Read matrix data and compute XOR sums for rows and columns
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        cin >> a[i][j];
        a[i][0] ^= a[i][j]; // XOR of all elements in row i
        a[0][j] ^= a[i][j]; // XOR of all elements in column j
        a[0][0] ^= a[i][j]; // XOR of all elements in matrix
      }
    
    int ans = 1e9;
    
    // Precompute costs for row operations (when fixing column j)
    for (int frj = 0; frj <= m; frj++) {
      for (int i1 = 0; i1 <= n; i1++)
        for (int i2 = i1 + 1; i2 <= n; i2++) {
          ds1[frj][i1][i2] = 0;
          ds1[frj][i2][i1] = 0;
          for (int j = 0; j <= m; j++) {
            if (j == frj)
              continue;
            ds1[frj][i1][i2] += abs(a[i1][j] - a[i2][j]);
            ds1[frj][i2][i1] += abs(a[i1][j] - a[i2][j]);
          }
        }
    }
    
    // Precompute costs for column operations (when fixing row i)
    for (int fri = 0; fri <= n; fri++) {
      for (int j1 = 0; j1 <= m; j1++)
        for (int j2 = j1 + 1; j2 <= m; j2++) {
          ds2[fri][j1][j2] = 0;
          ds2[fri][j2][j1] = 0;
          for (int i = 0; i <= n; i++) {
            if (i == fri)
              continue;
            ds2[fri][j1][j2] += abs(a[i][j1] - a[i][j2]);
            ds2[fri][j2][j1] += abs(a[i][j1] - a[i][j2]);
          }
        }
    }
    
    // Initialize cost matrices
    vector<vector<int>> r(m + 1, vector<int>(n + 1, 1e9)),
        c(n + 1, vector<int>(m + 1, 1e9));
    
    // Apply DP to find minimum cost for row operations
    for (int frj = 0; frj <= m; frj++)
      sailor_problem(n + 1, ds1[frj], r[frj]);
    
    // Apply DP to find minimum cost for column operations
    for (int fri = 0; fri <= n; fri++)
      sailor_problem(m + 1, ds2[fri], c[fri]);
    
    // Combine results to find overall minimum beauty
    for (int fri = 0; fri <= n; fri++)
      for (int frj = 0; frj <= m; frj++) {
        ans = min(ans, r[frj][fri] + c[fri][frj]);
      }
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/