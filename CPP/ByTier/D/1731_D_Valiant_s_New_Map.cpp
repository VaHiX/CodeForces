// Problem: CF 1731 D - Valiant's New Map
// https://codeforces.com/contest/1731/problem/D

/*
Algorithm: 
- The problem asks for the largest square subgrid where all elements are at least as large as the side length of the square.
- We use a technique based on prefix minimums and dynamic programming to efficiently find the maximum square.
- For each possible square size l from 1 up to n:
  - We compute the minimum height in each l x l square using a sliding window approach.
  - If any such square has all elements >= l, we update the answer.
- Time Complexity: O(n^2 * m^2) in worst case due to nested loops and min computation.
- Space Complexity: O(n * m) for storing the grid.

Techniques Used:
- Dynamic Programming with minimum computation.
- Iterative approach on square sizes.
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> a[i][j];
  
  int ans = 1; // Initialize answer to at least 1
  for (int l = 1; l < n; l++) { // Try all possible square sizes
    for (int i = 0; i < n - l; i++)
      for (int j = 0; j < m - l; j++) {
        // Update current cell with minimum of the 2x2 square it represents
        a[i][j] = min({a[i][j], a[i + 1][j], a[i][j + 1], a[i + 1][j + 1]});
        // If this element qualifies as a valid square center (minimum >= l), update answer
        if (a[i][j] > l)
          ans = l + 1;
      }
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/