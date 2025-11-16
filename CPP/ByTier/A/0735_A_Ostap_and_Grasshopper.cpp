// Problem: CF 735 A - Ostap and Grasshopper
// https://codeforces.com/contest/735/problem/A

#include <iostream>
#include <string>

/*
 * Problem: Determine if a grasshopper can reach from 'G' to 'T' by jumping exactly k steps
 *          at a time, avoiding obstacles '#'. The grasshopper can jump left or right.
 *
 * Algorithms/Techniques:
 *   - Linear traversal with k-step jumps in both directions from starting point
 *   - Check for obstacle '#' blocking the path
 *   - Early termination on reaching target 'T'
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int main() {
  int n, k;
  std::cin >> n >> k;
  std::string s;
  std::cin >> s;
  int g(-1), t(-1);
  for (int p = 0; p < s.size(); p++) {
    if (s[p] == 'G') {
      g = p;  // Find the starting position G
    }
    if (s[p] == 'T') {
      t = p;  // Find the target position T
    }
  }
  bool possible(0);
  // Check jumps to the right (forward direction)
  for (int p = g; p < s.size(); p += k) {
    if (s[p] == '#') {
      break;  // Obstacle blocks the path
    }
    if (s[p] == 'T') {
      possible = 1;  // Found target
      break;
    }
  }
  // Check jumps to the left (backward direction)
  for (int p = g; p >= 0; p -= k) {
    if (s[p] == '#') {
      break;  // Obstacle blocks the path
    }
    if (s[p] == 'T') {
      possible = 1;  // Found target
      break;
    }
  }
  std::cout << (possible ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/