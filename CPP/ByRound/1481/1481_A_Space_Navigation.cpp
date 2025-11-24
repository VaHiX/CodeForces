// Problem: CF 1481 A - Space Navigation 
// https://codeforces.com/contest/1481/problem/A

/*
 * Problem: Space Navigation
 * Algorithm/Technique: Simulation with greedy approach
 * Time Complexity: O(n) where n is the length of string s (sum of all lengths across test cases is at most 10^5)
 * Space Complexity: O(1) - only using a few variables for counting and flags
 *
 * Description:
 * You start at (0, 0) and want to reach (px, py). The string s contains movement commands.
 * You can delete some commands but not change their order. Determine if it's possible to reach the target.
 *
 * Approach:
 * Count total number of each direction command (U, D, L, R).
 * For each coordinate, check if we have enough moves in the required direction.
 * If px > 0, we need at least px moves to the right (R).
 * If px < 0, we need at least -px moves to the left (L).
 * Same logic applies for py and up/down movements.
 */

#include <iostream>
#include <string>
int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long px(0), py(0); // Target coordinates
    std::cin >> px >> py;
    std::string s; // Movement string
    std::cin >> s;
    long l(0), r(0), u(0), d(0); // Counters for each direction
    for (long p = 0; p < s.size(); p++) { // Traverse the string to count directions
      if (s[p] == 'R') {
        ++r;
      } else if (s[p] == 'L') {
        ++l;
      } else if (s[p] == 'U') {
        ++u;
      } else if (s[p] == 'D') {
        ++d;
      }
    }
    bool possible(true); // Flag to track if reaching the target is possible
    
    // Check if we have enough right moves for positive x target
    if (px > 0 && r < px) {
      possible = false;
    }
    
    // Check if we have enough left moves for negative x target
    if (px < 0 && l < -px) {
      possible = false;
    }
    
    // Check if we have enough up moves for positive y target
    if (py > 0 && u < py) {
      possible = false;
    }
    
    // Check if we have enough down moves for negative y target
    if (py < 0 && d < -py) {
      possible = false;
    }
    
    std::cout << (possible ? "YES" : "NO") << std::endl; // Output result
  }
}


// https://github.com/VaHiX/codeForces/