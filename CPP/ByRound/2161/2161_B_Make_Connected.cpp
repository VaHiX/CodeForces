// Problem: CF 2161 B - Make Connected
// https://codeforces.com/contest/2161/problem/B

/*
Algorithm: Grid Analysis for Connected Black Cells
Techniques:
- Snake Pattern Detection: Checks if the black cells form a path where the difference in row and column distances is at most 1.
- Staircase Pattern Detection: Checks if black cells can be sorted in a way that they form a staircase pattern.
- 2x2 Pattern Detection: Checks for a 2x2 square of black cells.

Time Complexity: O(n^2) per test case, where n is the size of the grid.
Space Complexity: O(k) where k is the number of black cells in the grid.

This solution detects if the existing black cells in a grid can form a valid connected component
with no three consecutive black cells aligned horizontally or vertically,
and whether they can be connected without violating the constraints.
*/

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
int t, n;
// Checks if the black cells form a "snake" pattern (path with limited angular turns)
bool snake(vector<pair<int, int>> &black) {
  for (auto [i1, j1] : black) {
    for (auto [i2, j2] : black) {
      // If the difference in row and column is more than 1, it's not a snake
      if (abs(abs(i1 - i2) - abs(j1 - j2)) > 1)
        return 0;
    }
  }
  return 1;
}
// Checks if the black cells form a "staircase" pattern (monotonic in row/column)
bool staircase(vector<pair<int, int>> &black) {
  sort(black.begin(), black.end(), [](auto p1, auto p2) {
    if (p1.first == p2.first)
      return p1.second < p2.second;
    return p1.first < p2.first;
  });
  int sz = black.size();
  vector<int> v(sz);
  for (int i = 0; i < sz; i++) {
    v[i] = black[i].second;
  }
  bool f1 = is_sorted(v.begin(), v.end());
  sort(black.begin(), black.end(), [](auto p1, auto p2) {
    if (p1.first == p2.first)
      return p1.second > p2.second;
    return p1.first < p2.first;
  });
  for (int i = 0; i < sz; i++) {
    v[i] = black[i].second;
  }
  reverse(v.begin(), v.end());
  bool f2 = is_sorted(v.begin(), v.end());
  return f1 or f2;
}
// Checks if the black cells form a 2x2 pattern
bool twobytwo(vector<pair<int, int>> &black) {
  if (black.size() != 4)
    return 0;
  sort(black.begin(), black.end());
  auto [i0, j0] = black[0];
  auto [i1, j1] = black[1];
  if (i0 != i1 or j0 + 1 != j1)
    return 0;
  auto [i2, j2] = black[2];
  if (i0 + 1 != i2 or j0 != j2)
    return 0;
  auto [i3, j3] = black[3];
  if (i2 != i3 or j2 + 1 != j3)
    return 0;
  return 1;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> t;
  while (t--) {
    cin >> n;
    vector<pair<int, int>> black;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        char c;
        cin >> c;
        if (c == '.')
          continue;
        // Add black cell position to list
        black.emplace_back(i, j);
      }
    }
    // Check if the pattern is valid (snake or staircase or 2x2)
    if ((staircase(black) and snake(black)) or twobytwo(black))
      cout << "YES" << '\n';
    else
      cout << "NO" << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/