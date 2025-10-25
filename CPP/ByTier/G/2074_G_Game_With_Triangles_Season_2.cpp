// Problem: CF 2074 G - Game With Triangles: Season 2
// https://codeforces.com/contest/2074/problem/G

/*
G. Game With Triangles: Season 2
Algorithms/Techniques: Dynamic Programming (DP) with interval DP approach
Time Complexity: O(N^3) per test case
Space Complexity: O(N^2) for the DP table

The problem involves selecting non-overlapping triangles from a polygon such that the total score (product of three vertices) is maximized.
This is solved using interval DP where dp[l][r] represents the maximum score obtainable from the subpolygon formed by vertices [l, r).
Triangles are constructed by choosing three distinct vertices i < j < k, and the product a[i]*a[j]*a[k] contributes to the score.
Overlapping triangles are not allowed, so we must use a partitioning strategy in DP.
*/

#include <algorithm>
#include <iostream>

using namespace std;
int N, A[400];
long long dp[400][401]; // dp[l][r] stores max score for polygon defined by [l, r)
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (; T--;) {
    cin >> N;
    for (int i = 0; i < N; i++)
      cin >> A[i];
    // Initialize dp table to 0
    for (int l = 0; l < N; l++)
      for (int r = l; r <= N; r++)
        dp[l][r] = 0;
    
    // Fill DP table using increasing interval lengths
    for (int k = 3; k <= N; k++)
      for (int l = 0; l + k <= N; l++) {
        int r = l + k;
        long long cur = max(dp[l + 1][r], dp[l][r - 1]);
        // Try all possible middle points m to split interval [l, r)
        for (int m = l + 1; m < r; m++) {
          // Consider splitting into left and right parts
          cur = max(cur, dp[l][m] + dp[m][r]);
          // If there's a valid triangle with l, m, r-1, compute score
          if (m < r - 1)
            cur = max(cur,
                      dp[l + 1][m] + dp[m + 1][r - 1] + A[l] * A[m] * A[r - 1]);
        }
        dp[l][r] = cur;
      }
    cout << dp[0][N] << "\n";
  }
}


// https://github.com/VaHiX/codeForces/