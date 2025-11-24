// Problem: CF 2070 B - Robot Program
// https://codeforces.com/contest/2070/problem/B

/*
B. Robot Program
Algorithm: Simulation with cycle detection and mathematical optimization
Time Complexity: O(n + sqrt(k)) per test case
Space Complexity: O(n) for string storage

The problem simulates a robot moving on a coordinate line based on commands.
The key insight is that if the robot reaches 0, it restarts the command sequence.
We simulate the initial part of execution to find when (if ever) it hits 0,
then use cycle detection and mathematical summation to count zeros efficiently
in the remaining k seconds.

Approach:
1. Simulate initial steps until either:
   - We hit 0 (reset counter)
   - All steps are done without reaching 0
2. If we never reached 0, answer is 0.
3. Otherwise, compute number of full cycles that can fit in remaining time,
   and handle the leftover steps efficiently.

Key techniques used:
- Prefix sum to track position
- Cycle detection optimization
- Mathematical summation instead of brute force simulation for large k
*/

#include <stddef.h>
#include <stdint.h>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  int64_t t;
  std::cin >> t;
  while (t--) {
    int64_t n, x, k;
    std::cin >> n >> x >> k;
    std::string s;
    std::cin >> s;
    
    // Simulate the first part of movement to see if we hit 0
    for (int64_t p = 0; x && p < s.size(); p++) {
      x += (s[p] == 'R') - (s[p] == 'L');  // Update position based on command
      --k;
    }
    
    if (x) {  // If we never hit zero during this initial run
      std::cout << "0" << std::endl;
      continue;
    }
    
    int64_t res(1);  // We've already entered 0 once, so start with 1
    
    // Now simulate to see how many full cycles of commands occur,
    // and if we can reach zero again in each cycle
    for (size_t p = 0; p < n; p++) {
      x += (s[p] == 'R') - (s[p] == 'L');  // Update total displacement from origin after this step
      if (!x) {  // If we return to origin
        res += k / (p + 1);  // Number of full cycles that can fit in remaining time
        break;
      }
    }
    
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/