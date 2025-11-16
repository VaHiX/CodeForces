// Problem: CF 1821 D - Black Cells
// https://codeforces.com/contest/1821/problem/D

/*
Algorithm: Greedy + Two Pointers Approach
Time Complexity: O(n), where n is the number of segments
Space Complexity: O(1), only using a few variables for computation

The problem involves coloring cells using a pointer and a "Shift" button.
We are given segments where we can color cells.
We want to find the minimum number of moves to color at least k cells.

Approach:
1. For each segment:
   - If segment has length 1, increment counter c (single cell segments).
   - Otherwise, add segment length to sum and increment counter c2 (multi-cell segments).
2. For each segment, check if total colored cells (sum + c) is sufficient to meet k:
   - If sum >= k, compute minimum moves to color exactly k cells.
   - If sum + c >= k, compute moves to color remaining cells.
3. Return the minimum moves found, or -1 if impossible.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i)
      cin >> l[i];
    for (int i = 0; i < n; ++i)
      cin >> r[i];
    int sum = 0;
    int ans = 2e9;
    int c = 0;
    int c2 = 0;
    for (int i = 0; i < n; ++i) {
      int len = r[i] - l[i] + 1;
      if (len == 1) {
        c++;
      } else {
        sum += len;
        c2++;
      }
      if (sum >= k) {
        // If we can color k cells using only multi-cell segments
        ans = min(ans, r[i] - (sum - k) + 2 * c2);
      } else if (sum + c >= k) {
        // If we need to use single-cell segments to complete coloring
        ans = min(ans, r[i] + 2 * c2 + 2 * (k - sum));
      }
    }
    cout << (ans == 2e9 ? -1 : ans) << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/