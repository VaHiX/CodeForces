// Problem: CF 2052 F - Fix Flooded Floor
// https://codeforces.com/contest/2052/problem/F

/*
F. Fix Flooded Floor
Time Complexity: O(n) where n is the length of the parquet stripe.
Space Complexity: O(1) excluding input storage.

Algorithms/Techniques:
- Greedy approach to fill 1x2 tiles on a 2xN grid.
- Process column by column from left to right.
- When a '.' is found, try to place a tile either horizontally or vertically depending on available space.
- Track possible states (unique, multiple, none) based on placement constraints and conflicts.

*/

#include <iostream>
#include <string>

using namespace std;
int t, f, n;           // t: number of test cases, f: flag for state, n: length of parquet
string a, b;           // a, b: rows of the 2xN grid represented as strings
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> a >> b;
    f = 0;             // reset flag for each test case
    for (int i = 0; i < n; i++) {
      if (a[i] == '#' && b[i] == '#')  // both cells are already filled
        continue;
      if (a[i] == '.' && b[i] == '#') {  // cell in top row is empty, bottom is filled
        if (i == n - 1 || a[i + 1] == '#') {  // can't extend horizontally, no valid tile
          cout << "None\n";
          f = 1;
          break;
        }
        a[i] = a[i + 1] = '#';  // place horizontal tile covering both cells in current and next column
      } else if (b[i] == '.' && a[i] == '#') {  // cell in bottom row is empty, top is filled
        if (i == n - 1 || b[i + 1] == '#') {  // can't extend horizontally, no valid tile
          cout << "None\n";
          f = 1;
          break;
        }
        b[i] = b[i + 1] = '#';  // place horizontal tile covering both cells in current and next column
      } else {  // both cells are empty
        if (i < n - 1 && a[i + 1] == '.' && b[i + 1] == '.') {
          f = 2;  // multiple ways to proceed when two adjacent positions can be filled with vertical tiles
        }
        a[i] = b[i] = '#';  // fill both cells (place vertical tile)
      }
    }
    if (f == 0)
      cout << "Unique\n";     // exactly one way to complete the grid
    else if (f == 2)
      cout << "Multiple\n";   // more than one valid arrangement
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/