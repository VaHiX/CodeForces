// Problem: CF 2096 C - Wonderful City
// https://codeforces.com/contest/2096/problem/C

/*
C. Wonderful City

Algorithms/Techniques:
- Dynamic Programming with state compression
- Grid manipulation using transpose
- Exhaustive check for valid transitions between states
- Two-phase approach: process rows and columns separately

Time Complexity:
O(n^4) per test case, due to nested loops over all possible transitions between states.

Space Complexity:
O(n^2) for DP table and O(n^2) for the grid storage, total space is O(n^2).

Problem Summary:
Given an n x n grid of building heights and two arrays a and b indicating costs to
increase rows/columns by 1, find the minimum cost to make all adjacent buildings have
different heights. We can only perform operations once on each worker (row or column).
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
#define fi first
#define se second
constexpr ll INF = 1e18;

// Helper function to compute minimum cost for a single pass (row or column)
ll work(int n, vector<vector<int>> &h, vector<int> &a) {
  vector<vector<ll>> dp(n, vector<ll>(2, INF)); // DP table: [i][0] = no op, [i][1] = op applied
  dp[0][0] = 0, dp[0][1] = a[0]; // Base case: start with no operation or apply operation on first element

  for (int i = 1; i < n; i++) {
    for (int x = 0; x < 2; x++) {
      for (int y = 0; y < 2; y++) {
        bool flag = 1;
        // Check if applying operation x to row/column i and y to previous row/column i-1 results in valid grid
        for (int j = 0; j < n; j++)
          flag &= h[i - 1][j] + y != h[i][j] + x;
        
        if (flag) {
          // Update DP based on transition
          if (x == 0)
            dp[i][x] = min(dp[i][x], dp[i - 1][y]);
          else
            dp[i][x] = min(dp[i][x], dp[i - 1][y] + a[i]);
        }
      }
    }
  }
  return min(dp[n - 1][0], dp[n - 1][1]); // Return minimum cost to reach last element
}

// Transpose the matrix (swap rows and columns)
void transpose(int n, vector<vector<int>> &h) {
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      swap(h[i][j], h[j][i]);
}

// Main function to solve each test case
void solve() {
  int n;
  cin >> n;
  vector<vector<int>> h(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> h[i][j];
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];

  // First, solve for rows
  ll ans = work(n, h, a);
  
  // Transpose matrix and then solve for columns using b values
  transpose(n, h);
  ans += work(n, h, b);

  if (ans >= INF)
    cout << "-1\n"; // Impossible case
  else
    cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/