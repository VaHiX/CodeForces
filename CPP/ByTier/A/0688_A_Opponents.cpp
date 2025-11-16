// Problem: CF 688 A - Opponents
// https://codeforces.com/contest/688/problem/A

/*
Code Purpose:
This program determines the maximum number of consecutive days Arya will win
against his opponents. Each day, if not all opponents are present, Arya wins.
If all opponents are present, they win. The input consists of n opponents and d days,
with each day's presence of opponents given as a binary string.

Algorithms/Techniques:
- Simulation of daily presence checks
- Sliding window technique to track maximum consecutive wins
- Linear scan through days to compute result

Time Complexity: O(n * d)
Space Complexity: O(d)
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  int n, d;
  std::cin >> n >> d;
  std::vector<bool> wins(d, 0);  // Track whether Arya wins each day
  for (int p = 0; p < d; p++) {
    std::string presence;
    std::cin >> presence;
    // Check if any opponent is absent (0) on this day
    for (int q = 0; q < n; q++)
      if (presence[q] == '0') {
        wins[p] = 1;  // Arya wins if at least one opponent is absent
        break;
      }
  }
  int temp(0);       // Temporary counter for current consecutive wins
  int cons(0);       // Maximum consecutive wins found so far
  for (int p = 0; p < d; p++) {
    if (wins[p]) {
      ++temp;         // Increment if Arya wins
    } else {
      temp = 0;       // Reset counter if he loses
    }
    cons = (temp > cons) ? temp : cons;  // Update maximum
  }
  std::cout << cons << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/