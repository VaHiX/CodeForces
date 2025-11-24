// Problem: CF 1612 F - Armor and Weapons
// https://codeforces.com/contest/1612/problem/F

/*
Algorithm: BFS with memoization to find minimum time to obtain nth armor and mth weapon.
Approach: 
- Use two maps `s[0]` and `s[1]` to represent current and next state of (armor, weapon) combinations.
- Start with (1,1) in `s[0]`.
- For each state, compute possible next states by either:
  1. Adding a new weapon to an existing armor set, or
  2. Adding a new armor set to an existing weapon.
- If a synergistic pair (i,j) exists, power is increased by 1.
- Traverse levels (hours) until both nth armor and mth weapon are reached.

Time Complexity: O(nm) where n and m are the number of armor sets and weapons.
Space Complexity: O(nm) for storing the synergy map and state tracking.

*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>

int n, m, q, k, x, y, c, p, t, i;
std::map<int, int> f[200005], s[2]; // f: synergy map; s: current states
int main() {
  for (std::cin >> n >> m >> q, s[0][1] = 1; q--; // Initialize with (1,1) state
       std::cin >> x >> y, n > m ? f[y][x] = 1 : f[x][y] = 1) // Store synergies
    ;
  if (n > m) // Ensure n <= m to optimize processing
    std::swap(n, m);
  for (;; c = (++k) & 1) { // Alternate between two state maps
    if (s[c][n] == m) // If we've reached both nth armor and mth weapon
      return printf("%d\n", k), 0;
    for (i = 1; i <= n; i++) // Process all armor sets
      if (s[c][i]) {
        p = i + s[c][i] + f[i][s[c][i]], // Calculate power (with synergy bonus if exists)
        t = p < n ? p : n; // Determine new armor level (max n)
        s[1 - c][t] = std::max(s[1 - c][t], s[c][i]), // Update next state with max weapon
              s[1 - c][i] = std::max(s[1 - c][i], p < m ? p : m); // Update armor weapon level
      }
  }
}


// https://github.com/VaHiX/CodeForces/