// Problem: CF 1700 E - Serega the Pirate
// https://codeforces.com/contest/1700/problem/E

/*
Code Purpose:
This program determines the minimum number of swaps needed to make a puzzle solvable. 
A puzzle is solvable if there exists a path visiting cells in ascending order of their values.
The algorithm checks for invalid positions that prevent a solution and evaluates whether one swap can fix the issue.

Algorithms/Techniques:
- Preprocessing to identify "bad" cells where the sequence would fail.
- Brute-force checking of possible swaps to see if any makes the puzzle solvable.
- Set-based approach to avoid counting duplicate swaps.

Time Complexity: O(n * m * sqrt(n * m)) in the worst case due to brute-force checks of possible swaps.
Space Complexity: O(n * m) for storing grid and auxiliary data structures.
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
vector<pair<int, int>> d = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}, shit;
int i, j, k, n, m, t;
vector<vector<int>> a;
set<pair<int, int>> sb;

// Checks if a cell is valid for solving the puzzle
bool chk0(int x, int y) {
  if (a[x][y] == 1) // Starting cell is always valid
    return 1;
  if (a[x][y] > n * m) // Out of bounds
    return 1;
  for (auto [dx, dy] : d) {
    dx += x;
    dy += y;
    if (a[dx][dy] < a[x][y]) // If neighbor is smaller, path is invalid
      return 1;
  }
  return 0;
}

// Evaluates a specific swap between two cells
void chk(int x1, int y1, int x2, int y2) {
  swap(a[x1][y1], a[x2][y2]); // Perform swap
  int i, j, k, res = 1, r1, r2;
  for (auto [x, y] : shit)
    if (!chk0(x, y)) { // Check if any bad cell becomes valid
      res = 0;
      goto aaa; // Jump to end
    }
  if (!chk0(x1, y1) || !chk0(x2, y2)) { // Check if swapped cells are valid
    res = 0;
    goto aaa;
  }
  for (auto [dx, dy] : d)
    if (!chk0(dx + x1, dy + y1) || !chk0(dx + x2, dy + y2)) { // Check neighbors
      res = 0;
      goto aaa;
    }
  r1 = x1 * m + y1, r2 = x2 * m + y2;
  sb.insert({min(r1, r2), max(r1, r2)}); // Add valid swap to set to avoid duplicates
aaa:
  swap(a[x1][y1], a[x2][y2]); // Revert swap
}

int main() {
  ios::sync_with_stdio(0);
  cin >> n >> m;
  a = vector<vector<int>>(n + 2, vector<int>(m + 2, 1e9)); // Initialize grid with large values
  for (i = 1; i <= n; i++)
    for (j = 1; j <= m; j++)
      cin >> a[i][j];
  for (i = 1; i <= n; i++)
    for (j = 1; j <= m; j++) {
      if (a[i][j] == 1) // Skip starting cell
        continue;
      if (!chk0(i, j)) // If cell is invalid, add to list
        shit.push_back({i, j});
    }
  if (shit.empty()) { // All cells are valid, no swaps needed
    cout << "0";
    return 0;
  }
  if (shit.size() > 6) { // If too many invalid cells, minimum is at least 2
    cout << "2";
    return 0;
  }
  auto [x, y] = shit[0]; // Choose one invalid cell
  for (i = 1; i <= n; i++)
    for (j = 1; j <= m; j++) {
      chk(i, j, x, y); // Swap with invalid cell
      for (auto [dx, dy] : d) {
        dx += x;
        dy += y;
        if (a[dx][dy] > n * m) // Skip if neighbor out of bounds
          continue;
        chk(i, j, dx, dy); // Swap with valid neighbor
      }
    }
  int res = sb.size(); // Number of unique valid swaps
  if (res)
    cout << 1 << ' ' << res; // One swap sufficient
  else
    cout << 2; // Two swaps needed (minimum)
}


// https://github.com/VaHiX/CodeForces/