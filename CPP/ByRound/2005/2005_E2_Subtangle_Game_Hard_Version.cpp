// Problem: CF 2005 E2 - Subtangle Game (Hard Version)
// https://codeforces.com/contest/2005/problem/E2

/*
 * Problem: E2. Subtangle Game (Hard Version)
 * 
 * Purpose: Determine the winner of a two-player game where players alternately 
 *          pick elements from a matrix following specific rules about submatrices.
 * 
 * Algorithm:
 *   - Use dynamic programming with backward traversal.
 *   - For each cell (i, j) in the matrix, calculate the minimum index of an 
 *     element in the array that can be matched at this point, considering 
 *     the constraints of previous moves.
 *   - The game state transitions by moving to a submatrix starting at (r+1, c+1).
 * 
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(n * m) for the DP table and auxiliary arrays
 * 
 * Techniques:
 *   - Dynamic Programming with memoization
 *   - Backward traversal for optimal state calculation
 *   - Efficient input/output handling via std::ios_base::sync_with_stdio
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
int id[maxn * maxn]; // id[x] = index of element x in array a, 0 if not present

void solve() {
  int l, n, m;
  cin >> l >> n >> m;
  
  // Initialize dp table with large values (inf)
  f1(i, n + 1) f1(j, m + 1) f0(x, 2) dp[i][j] = 1e9;
  
  // Read array a and map element to its index
  f1(i, l) {
    cin >> a[i];
    if (!id[a[i]])
      id[a[i]] = i;
  }
  
  // Read matrix b
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> b[i][j];
  
  // Traverse matrix from bottom-right to top-left
  for (int i = n; i; i--)
    for (int j = m; j; j--) {
      // Update dp[i][j] with minimum of going down or right
      dp[i][j] = min(dp[i + 1][j], dp[i][j + 1]);
      
      // If current element exists in array:
      // Update dp[i][j] with the index in array if we can choose it at this position
      if (id[b[i][j]] && dp[i + 1][j + 1] > id[b[i][j]] + 1)
        dp[i][j] = min(dp[i][j], id[b[i][j]]);
    }
  
  // If dp[1][1] is 1, Tsovak wins (first player), otherwise Narek wins
  if (dp[1][1] == 1)
    cout << "T";
  else
    cout << "N";
  el;
  
  // Reset id array for next test case
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


// https://github.com/VaHiX/CodeForces/