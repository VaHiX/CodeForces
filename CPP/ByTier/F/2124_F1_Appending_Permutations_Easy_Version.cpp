// Problem: CF 2124 F1 - Appending Permutations (Easy Version)
// https://codeforces.com/contest/2124/problem/F1

/*
F1. Appending Permutations (Easy Version)
time limit per test3 seconds
memory limit per test1024 megabytes

Algorithms/Techniques: Dynamic Programming with State Compression and Check for Validity

Time Complexity: O(n^4) per test case
Space Complexity: O(n^2) 

This problem involves counting valid arrays of length n constructed by appending cyclic shifts of [1,2,...,s] to an initially empty array,
subject to m restrictions that some positions must not equal certain values.
We use dynamic programming where dp[i] represents the number of ways to build a prefix of length i,
and dp2[i][j] tracks additional state related to valid segments ending at position i with length j.
The check function verifies if placing a segment from x to y starting at position st is valid given the restrictions.
*/

#include <string.h>
#include <iostream>

using namespace std;
#define int long long
#define mod 998244353
int t, n, m, vis[101][101], dp[101], dp2[101][101];

// Function to check if placing a segment from x to y starting at st is valid
bool check(int x, int y, int st) {
  int now = 0;
  // Check the part of the segment from st to y
  for (int i = st; i <= y; i++)
    if (vis[i][++now])  // If a position is restricted to be 0, it's not valid
      return false;
  // Check the part from x to st-1
  for (int i = x; i < st; i++)
    if (vis[i][++now])  // If a position is restricted to be 0, it's not valid
      return false;
  return true;
}

signed main() {
  cin >> t;
  while (t--) {
    memset(vis, 0, sizeof(vis));   // Reset visibility matrix for each test case
    memset(dp, 0, sizeof(dp));     // Reset dp array
    memset(dp2, 0, sizeof(dp2));   // Reset dp2 array
    cin >> n >> m;
    for (int i = 1, id, x; i <= m; i++)  // Read and mark the restrictions
      cin >> id >> x, vis[id][x] = 1;
    dp[0] = 1;  // Base case: one way to form an empty array
    for (int i = 1; i <= n; i++) {   // For each position from 1 to n
      for (int j = 1; j <= i; j++)   // For each possible start position of block ending at i
        for (int k = j; k <= i; k++) // For each possible start point of cyclic shift within the block
          if (check(j, i, k)) {     // If valid placement
            dp[i] += dp[j - 1] - dp2[j - 1][i - k + 1] * (j != k),  // Update dp with contribution from previous states
            dp[i] = (dp[i] % mod + mod) % mod;   // Ensure non-negative modulo
          }
      for (int j = 1; j <= i; j++)   // Update dp2 for the current prefix
        if (check(j, i, j))        // If valid placement starting at j
          dp2[i][i - j + 1] += dp[j - 1], dp2[i][i - j + 1] %= mod;
    }
    cout << dp[n] << "\n";  // Final answer for this test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/