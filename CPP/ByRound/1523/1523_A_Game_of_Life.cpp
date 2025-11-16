// Problem: CF 1523 A - Game of Life
// https://codeforces.com/contest/1523/problem/A

/*
* Problem: William's Cellular Automaton - Game of Life Variation
* 
* Algorithm: Simulation with Optimization
* 
* Time Complexity: O(n * m) in worst case, but optimized to O(n * k) where k is the number of iterations before pattern repeats.
*                  Since m can be up to 10^9, we detect cycles and avoid full simulation.
* Space Complexity: O(n) for storing the string and temporary string during each iteration.
*
* Description:
*   - Each cell evolves based on its neighbors: if dead and exactly one neighbor is alive, it becomes alive.
*   - Alive cells remain alive.
*   - Neighbors are defined as left and right adjacent cells (indices i-1 and i+1).
*   - If a neighbor doesn't exist, it's considered dead.
*
* Techniques:
*   - Simulation with cycle detection for large m values
*   - Optimization: Stop early when pattern repeats to prevent unnecessary iterations.
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::string s;
    std::cin >> s;
    bool chg(true);
    // Optimization: If m is too large, detect repeating patterns to avoid full simulation
    while (chg && m--) {
      std::string t(s); // Create a copy of current state
      chg = false;     // Assume no changes in this iteration
      for (long p = 0; p < t.size(); p++) {
        if (t[p] == '1') {
          continue; // Alive cells stay alive
        }
        // Check neighbors: previous and next cell
        bool prev = (p > 0 ? (s[p - 1] == '1') : 0);   // Left neighbor is alive?
        bool nxt = (p < n - 1 ? (s[p + 1] == '1') : 0); // Right neighbor is alive?
        if (prev ^ nxt) {                              // XOR: exactly one neighbor is alive
          t[p] = '1';                                  // Cell becomes alive
          chg = true;                                  // Indicates a change occurred
        }
      }
      s = t; // Update state for next iteration
    }
    std::cout << s << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/