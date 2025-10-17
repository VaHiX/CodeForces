// Problem: CF 2005 E2 - Subtangle Game (Hard Version)
// https://codeforces.com/contest/2005/problem/E2

/*
E2. Subtangle Game (Hard Version)

Algorithms/Techniques: Dynamic Programming with memoization, Game Theory

Time Complexity: O(n * m * l) per test case
Space Complexity: O(n * m + l) per test case

This is a game theory problem where two players (Tsovak and Narek) take turns finding elements of array 'a' in matrix 'b'.
Each player must choose an element from a submatrix that starts at (r+1, c+1) where (r,c) is the previous choice.
The goal is to determine who wins when both play optimally.

The solution uses dynamic programming:
- dp[i][j] represents the minimum "turn" number needed to reach position (i,j) in the game.
- The key idea is to compute backward: for each cell (i,j), we look at possible moves to (i+1,j) and (i,j+1).
- If element b[i][j] exists in array 'a', it marks a valid move and influences future decisions.
*/

#include <algorithm>
#include <iostream>
#define el cout << "\n"
#define f0(i, n) for (int i = 0; i < n; ++i)
#define f1(i, n) for (int i = 1; i <= n; ++i)
#define maxn 1503
using namespace std;
int t;
int a[maxn], b[maxn][maxn];
int dp[maxn][maxn];
int id[maxn * maxn];

void solve() {
  int l, n, m;
  cin >> l >> n >> m;
  
  // Initialize dp table with large values
  f1(i, n + 1) f1(j, m + 1) f0(x, 2) dp[i][j] = 1e9;
  
  // Mark positions of elements in array 'a' for quick lookup
  f1(i, l) {
    cin >> a[i];
    if (!id[a[i]])
      id[a[i]] = i;
  }
  
  // Read matrix 'b'
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> b[i][j];
      
  // DP computation from bottom-right to top-left
  for (int i = n; i; i--)
    for (int j = m; j; j--) {
      // Take minimum of going down or right
      dp[i][j] = min(dp[i + 1][j], dp[i][j + 1]);
      
      // If current cell contains an element from array 'a'
      if (id[b[i][j]] && dp[i + 1][j + 1] > id[b[i][j]] + 1)
        dp[i][j] = min(dp[i][j], id[b[i][j]]);
    }
    
  // If the value at dp[1][1] is 1, Tsovak (first player) wins
  if (dp[1][1] == 1)
    cout << "T";
  else
    cout << "N";
  el;
  
  // Clear id array for next test case
  f1(i, l) id[a[i]] = 0;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/codeForces/