// Problem: CF 1680 E - Moving Chips
// https://codeforces.com/contest/1680/problem/E

/*
Purpose: This code solves the problem of moving chips on a 2xN board to leave exactly one chip,
         minimizing the total number of moves. It uses a greedy approach to simulate the process
         of capturing chips by moving them to adjacent cells.

Algorithm: 
- Identify the leftmost and rightmost chips.
- Iterate from left to right, counting moves and simulating capture.
- For each column with chips, if both rows have chips, it's a capture (costs 2 moves),
  otherwise, it's movement (costs 1 move) and the chip gets moved to the next column.

Time Complexity: O(n) where n is the length of the board. We iterate through the board a constant number of times.
Space Complexity: O(1) excluding input storage. Only using a fixed amount of extra variables.

Techniques:
- Greedy simulation of chip movement
- Tracking of leftmost and rightmost chip positions
- Efficient traversal and updating of chip locations
*/

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 2e5 + 10;
int n;
char c[2][N];
void solve() {
  cin >> n >> c[0] >> c[1];
  int l = 1e9, r = -1, res = 0;
  for (int i = 0; i < n; i++)
    if (c[0][i] == '*' || c[1][i] == '*')  // Find the range of chips
      l = min(l, i), r = i;
  for (int i = l; i <= r; i++) {  // Process chips from left to right
    res++;  // Count move for current chip
    if (c[0][i] == '*' && c[1][i] == '*')  // If both chips present, simulate capture
      res++;
    else if (c[0][i] == '*')  // Move chip from top to bottom of next column
      c[0][i + 1] = '*';
    else if (c[1][i] == '*')  // Move chip from bottom to top of next column
      c[1][i + 1] = '*';
  }
  cout << res - 1 << endl;  // Adjust for overcounting
}
int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/