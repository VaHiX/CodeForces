// Problem: CF 1713 A - Traveling Salesman Problem
// https://codeforces.com/contest/1713/problem/A

#include <algorithm>
#include <iostream>

using namespace std;
/*
 * Problem: Collect all boxes on x or y axis starting and ending at (0, 0)
 * Algorithm:
 *   - For each box, store its coordinates (x_i, y_i) where either x_i = 0 or y_i = 0
 *   - Find the maximum x, maximum y, minimum x, and minimum y among all boxes
 *   - The minimal path is to go from (0,0) to (max_x, max_y), collect boxes,
 *     then return along the same path in reverse.
 *   - Since we visit all points once and return, the total distance is:
 *     2 * (max_x + max_y - min_x - min_y)
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int x, y;
    int mx = 0, my = 0, a = 0, b = 0; // mx, my: max x and y; a, b: min x and y
    for (int i = 0; i < n; i++) {
      cin >> x;
      cin >> y;
      mx = max(mx, x);          // Track maximum x coordinate
      my = max(my, y);          // Track maximum y coordinate
      a = min(x, a);            // Track minimum x coordinate
      b = min(y, b);            // Track minimum y coordinate
    }
    cout << 2 * (mx + my - a - b) << endl; // Output the minimal number of moves
  }
}

// https://github.com/VaHiX/codeForces/