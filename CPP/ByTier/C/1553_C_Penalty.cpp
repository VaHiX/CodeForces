// Problem: CF 1553 C - Penalty
// https://codeforces.com/contest/1553/problem/C

/*
C. Penalty
Algorithms/Techniques: Simulation with greedy approach
Time Complexity: O(t * n) where n = 10 (fixed), so effectively O(t)
Space Complexity: O(1) - only using a few variables for counting

This problem simulates a penalty shootout between two teams. Each team takes turns 
kicking, and the game stops as soon as one team has a lead that the other cannot 
overcome with remaining kicks. The string input represents predictions of each kick:
'1' means goal, '0' means no goal, '?' means unknown outcome.
We simulate the process step by step, keeping track of goals scored and remaining 
kicks for both teams. At each step, we check if either team has a lead that can't be 
overcome by the opponent in their remaining kicks. If so, we stop the simulation early.
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  const int N = 10;
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    int ga(0), gb(0), ua(0), ub(0), ra(5), rb(5); // ga/gb: goals scored, ua/ub: unknowns, ra/rb: remaining kicks
    int mlen(10);
    for (long p = 0; p < s.size(); p++) {
      if (p % 2 == 0) {      // Team A's turn (even indices)
        --ra;
        if (s[p] == '1') {
          ++ga;              // Goal for team A
        } else if (s[p] == '?') {
          ++ua;              // Unknown for team A
        }
      } else {               // Team B's turn (odd indices)
        --rb;
        if (s[p] == '1') {
          ++gb;              // Goal for team B
        } else if (s[p] == '?') {
          ++ub;              // Unknown for team B
        }
      }
      // Check if team A can't be overtaken by team B with remaining kicks
      if (ga + ua > gb + rb) {
        mlen = p + 1;
        break;
      } else if (gb + ub > ga + ra) {   // Check if team B can't be overtaken by team A
        mlen = p + 1;
        break;
      }
    }
    printf("%d\n", mlen);
  }
}


// https://github.com/VaHiX/codeForces/