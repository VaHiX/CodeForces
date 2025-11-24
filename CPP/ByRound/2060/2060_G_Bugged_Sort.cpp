// Problem: CF 2060 G - Bugged Sort
// https://codeforces.com/contest/2060/problem/G

/*
G. Bugged Sort
Algorithms/Techniques: Graph coloring, sorting, dynamic programming on pairs
Time Complexity: O(n log n) per test case due to sorting step; overall O(T * n log n)
Space Complexity: O(n) for the arrays and DP table

The problem involves determining whether two sequences can be sorted simultaneously using a special swap operation.
Each swap exchanges elements between the two arrays such that a[i] <-> b[j] and b[i] <-> a[j].
We model this as a graph where each pair (a[i], b[i]) is connected to all other pairs that can be reached via valid swaps.
The idea is to check if we can transform both sequences into sorted order by choosing appropriate swaps.

This code uses dynamic programming with four states:
dp[i][0]: current state of (a[i], b[i])
dp[i][1]: current state of (a[i], b[j]) where j > i and b[j] < a[i]
dp[i][2]: current state of (b[i], a[j]) where j > i and a[j] < b[i]
dp[i][3]: current state of (b[i], b[j]) where j > i and b[j] < b[i]

This is actually a simplified model to check if a valid path exists from first to last element.

*/
#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
const int kn = 2e5 + 25;
int n;
class ARR {
public:
  int x, y;
  bool operator<(const ARR &v) const {
    return (x < y ? x : y) < (v.x < v.y ? v.x : v.y); // Sort by min of pair
  }
} a[kn];
int dp[kn][4];
inline void _solv() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    dp[i][0] = dp[i][1] = dp[i][2] = dp[i][3] = 0; // Initialize DP table
  for (int i = 1; i <= n; ++i)
    cin >> a[i].x; // Read a values
  for (int i = 1; i <= n; ++i)
    cin >> a[i].y; // Read b values
  sort(a + 1, a + n + 1); // Sort pairs based on min of elements in each pair
  dp[1][0] = dp[1][3] = 1; // Base case: first pair can have state 0 or 3
  for (int i = 2; i <= n; ++i) {
    if (a[i].x > a[i - 1].x && a[i].y > a[i - 1].y) { // Check transition valid
      dp[i][0] |= dp[i - 1][0]; // From same pair to next pair 
      dp[i][1] |= dp[i - 1][3];
      dp[i][2] |= dp[i - 1][2];
      dp[i][3] |= dp[i - 1][1];
    }
    if (a[i].x > a[i - 1].y && a[i].y > a[i - 1].x) { // Check transition valid: swap
      dp[i][0] |= dp[i - 1][1]; // From swapped pair to next pair
      dp[i][1] |= dp[i - 1][2];
      dp[i][2] |= dp[i - 1][3];
      dp[i][3] |= dp[i - 1][0];
    }
  }
  printf((dp[n][0] | dp[n][1]) ? "YES\n" : "NO\n"); // If final state is reachable, YES
}
signed main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--)
    _solv();
  return 0;
}


// https://github.com/VaHiX/codeForces/