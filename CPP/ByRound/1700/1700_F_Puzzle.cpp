// Problem: CF 1700 F - Puzzle
// https://codeforces.com/contest/1700/problem/F

/*
 * Puzzle Problem Solution
 *
 * Purpose:
 *   This program determines the minimum number of adjacent swaps needed to transform
 *   a 2xN puzzle from its current configuration to a desired configuration.
 *   Each cell in the puzzle contains either 0 or 1. Adjacent cells are defined as
 *   those that share an edge (Manhattan distance = 1).
 *
 * Approach:
 *   - For each column, compare the current and target values for both rows.
 *   - Track the imbalance in each row (how many more 1s exist in current vs target).
 *   - Use greedy approach to reduce imbalances through swaps:
 *     - When one row has excess 1s and the other has deficit, perform swaps to balance.
 *   - If at the end, both rows are balanced (imbalances are zero), return total swaps.
 *     Otherwise, return -1 (impossible to achieve).
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Algorithms/Techniques:
 *   - Greedy approach with two-pass balancing
 *   - Difference tracking between current and target states
 *   - Manhattan distance adjacency in grid
 */

#include <bits/std_abs.h>
#include <algorithm>
#include <iostream>

#define int long long
using namespace std;
int const N = 233333;
int n, ans, u, d, a[5][N];
signed main() {
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= 4; i++)
    for (int j = 1; j <= n; j++)
      cin >> a[i][j];
  for (int i = 1, t; i <= n; i++) {
    u += a[1][i] - a[3][i], d += a[2][i] - a[4][i]; // Calculate row imbalances
    if (u > 0 && 0 > d) // If row 1 has surplus, row 2 has deficit
      t = min(u, -d), ans += t, u -= t, d += t; // Resolve balance with swaps
    if (u < 0 && 0 < d) // If row 1 has deficit, row 2 has surplus
      t = min(-u, d), ans += t, u += t, d -= t; // Resolve balance with swaps
    ans += abs(u) + abs(d); // Add remaining imbalance to total steps
  }
  cout << (u || d ? -1 : ans) << "\n"; // If any imbalance remains, impossible
}


// https://github.com/VaHiX/CodeForces/