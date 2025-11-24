// Problem: CF 641 A - Little Artem and Grasshopper
// https://codeforces.com/contest/641/problem/A

/*
 * Problem: Little Artem and Grasshopper
 * Purpose: Determine if a grasshopper jumping on a strip of n cells will continue forever or eventually jump off the strip.
 * Algorithm:
 *   - Simulate the grasshopper's jumps starting from the first cell.
 *   - Track visited cells to detect cycles.
 *   - If the grasshopper jumps outside the strip, output "FINITE".
 *   - If a cycle is detected, output "INFINITE".
 * 
 * Time Complexity: O(n) - Each cell is visited at most once.
 * Space Complexity: O(n) - For storing visited flags and next jump distances.
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

int main() {
  int n;
  std::cin >> n;
  std::string dir;
  std::cin >> dir;
  std::vector<long> next(n);
  for (long p = 0; p < n; p++) {
    int x;
    std::cin >> x;
    // Calculate the jump distance with direction
    next[p] = x * ((dir[p] == '<') ? (-1) : 1);
  }
  std::vector<bool> visited(n, 0);  // Track which cells have been visited
  long pos(0);  // Starting position
  bool finite(false);
  while (true) {
    // Check if grasshopper is out of bounds
    if (pos < 0 || pos >= n) {
      finite = true;
      break;
    }
    // Check for cycle (if current cell was already visited)
    if (visited[pos]) {
      finite = false;
      break;
    }
    visited[pos] = true;  // Mark current cell as visited
    pos += next[pos];  // Move to the next cell according to the jump rule
  }
  puts(finite ? "FINITE" : "INFINITE");
  return 0;
}


// https://github.com/VaHiX/CodeForces/