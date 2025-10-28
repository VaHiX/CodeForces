// Problem: CF 1950 G - Shuffling Songs
// https://codeforces.com/contest/1950/problem/G

/*
 * Problem: G. Shuffling Songs
 * 
 * Purpose: Find the minimum number of songs to remove from a playlist so that
 *          the remaining songs can be arranged in an "exciting" order, where
 *          adjacent songs either share the same writer or the same genre.
 * 
 * Algorithm:
 *  - Use bitmask dynamic programming to explore all possible subsets of songs.
 *  - For each subset, determine if there exists a valid ordering (Hamiltonian path)
 *    where adjacent songs satisfy the genre or writer condition.
 *  - The DP state `f[mask][i]` represents whether we can form a valid sequence ending
 *    with song `i` using the subset of songs represented by `mask`.
 *  - The maximum number of songs that can form a valid sequence gives us the minimum
 *    removals needed.
 * 
 * Time Complexity: O(2^n * n^2) where n <= 16
 * Space Complexity: O(2^n * n) for the DP table
 * 
 * Techniques:
 *  - Bitmask DP
 *  - Graph traversal (valid adjacency conditions)
 *  - Map for genre and writer compression
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

const int N = 17;
int n;
int g[N], w[N]; // g[i] and w[i] store compressed genre and writer IDs
bool f[1 << N][N]; // f[mask][i] = true if we can form a valid path ending at song i with subset mask

void solve() {
  std::cin >> n;
  std::map<std::string, int> mpg, mpw; // maps genre and writer strings to integers
  int idxg = 0, idxw = 0; // counters for unique genres and writers
  for (int i = 0; i < n; i++) {
    std::string gs, ws;
    std::cin >> gs >> ws;
    if (!mpg.count(gs))
      mpg[gs] = ++idxg;
    if (!mpw.count(ws))
      mpw[ws] = ++idxw;
    g[i] = mpg[gs], w[i] = mpw[ws]; // compress strings to integers
  }
  
  // Initialize DP: each single song can start a path
  for (int i = 0; i < 1 << n; i++) {
    if (!i) {
      for (int j = 0; j < n; j++) {
        f[i | 1 << j][j] = true;
      }
      continue;
    }
    // For each song in current mask, try extending it by another song not in mask
    for (int j = 0; j < n; j++)
      if (i >> j & 1) { // if song j is in the current subset
        if (!f[i][j])
          continue;
        for (int k = 0; k < n; k++)
          if (!(i >> k & 1)) { // if song k is not in the current subset
            if (g[j] == g[k] || w[j] == w[k]) { // check adjacency condition
              f[i | 1 << k][k] = true; // extend the subset by including song k
            }
          }
      }
  }
  
  // Find the maximum number of songs in a valid path
  int mx = 0;
  for (int i = 0; i < 1 << n; i++) {
    int cnt = 0;
    for (int j = 0; j < n; j++)
      cnt += i >> j & 1;
    for (int j = 0; j < n; j++)
      if (i >> j & 1) {
        if (f[i][j]) {
          mx = std::max(mx, cnt);
        }
      }
  }
  
  std::cout << n - mx << "\n";
  // Reset the DP table for next test case
  for (int i = 0; i < 1 << n; i++) {
    for (int j = 0; j < n; j++) {
      f[i][j] = false;
    }
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int t = 1;
  std::cin >> t;
  for (int i = 1; i <= t; i++)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/