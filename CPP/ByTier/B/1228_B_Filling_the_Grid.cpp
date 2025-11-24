// Problem: CF 1228 B - Filling the Grid
// https://codeforces.com/contest/1228/problem/B

/*
B. Filling the Grid
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Suppose there is a h x w grid consisting of empty or full cells. Let's make some definitions:
r_i is the number of consecutive full cells connected to the left side in the i-th row (1 <= i <= h). In particular, r_i=0 if the leftmost cell of the i-th row is empty.
c_j is the number of consecutive full cells connected to the top end in the j-th column (1 <= j <= w). In particular, c_j=0 if the topmost cell of the j-th column is empty.

In other words, the i-th row starts exactly with r_i full cells. Similarly, the j-th column starts exactly with c_j full cells.

These are the r and c values of some 3 x 4 grid. Black cells are full and white cells are empty.

You have values of r and c. Initially, all cells are empty. Find the number of ways to fill grid cells to satisfy values of r and c. Since the answer can be very large, find the answer modulo 1000000007 (10^9 + 7). In other words, find the remainder after division of the answer by 1000000007 (10^9 + 7).

Algorithms/Techniques:
- Grid filling with constraints from row and column prefixes
- Dynamic programming approach using 2D grid tracking state of cells
- Counting free cells to determine number of combinations (2^free_cells)

Time Complexity: O(h * w)
Space Complexity: O(h * w)
*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  const ll MOD = 1000000007;
  ll h, w;
  scanf("%lld %lld", &h, &w);
  std::vector<std::vector<ll>> g(h, std::vector<ll>(w, 0)); // Initialize grid with all zeros
  ll ans(1); // Answer initialized to 1 (multiplicative identity)
  for (ll row = 0; row < h; row++) {
    ll x;
    scanf("%lld", &x);
    for (ll col = 0; col < x; col++) {
      g[row][col] = 1; // Mark first x cells in row as full
    }
    if (x < w) {
      g[row][x] = -1; // Mark boundary cell after prefix as forbidden to be full
    }
  }
  for (ll col = 0; ans && (col < w); col++) {
    ll x;
    scanf("%lld", &x);
    for (ll row = 0; row < x; row++) {
      if (g[row][col] == -1) { // If forbidden cell is encountered, impossible to satisfy conditions
        ans = 0;
        break;
      }
      g[row][col] = 1; // Mark first x cells in column as full
    }
    if (x < h) {
      if (g[x][col] == 1) { // If boundary cell is already full, impossible to satisfy conditions
        ans = 0;
        break;
      } else {
        g[x][col] = -1; // Mark boundary cell as forbidden to be full
      }
    }
  }
  if (ans) {
    ll cnt(0); // Count empty cells that are not yet fixed
    for (ll row = 0; row < h; row++) {
      for (ll col = 0; col < w; col++) {
        cnt += (g[row][col] == 0); // Count unfixed cells
      }
    }
    while (cnt--) { // For each free cell, we have 2 choices: full or empty
      ans *= 2;
      ans %= MOD;
    }
  }
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/