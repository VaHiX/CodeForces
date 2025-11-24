// Problem: CF 500 A - New Year Transportation
// https://codeforces.com/contest/500/problem/A

/*
 * Purpose: Determine if it's possible to reach cell 't' from cell '1' in a Line World
 *          using a set of unidirectional portals defined by array 'a'.
 * 
 * Algorithm: 
 *   - Build a map of portals where portal i connects cell i to cell (i + a[i]).
 *   - Use BFS/DFS-like traversal starting from cell 1, keeping track of visited cells.
 *   - If we reach cell 't', return "YES", otherwise "NO".
 * 
 * Time Complexity: O(n), where n is the number of cells. In worst case, we visit each cell once.
 * Space Complexity: O(n), for the map storing portals and the set for visited cells.
 */

#include <cstdio>
#include <map>
#include <set>
#include <utility>

int main() {
  long n, t;
  scanf("%ld %ld\n", &n, &t);
  std::map<long, long> move;  // Map to store portal connections: cell -> destination
  for (long p = 1; p < n; p++) {
    long a;
    scanf("%ld", &a);
    move.insert(std::pair<long, long>(p, p + a));  // Insert portal from p to p + a[p]
  }
  std::set<long> visited;  // Keep track of visited cells to avoid cycles
  long current = 1;  // Start from cell 1
  bool possible(0);  // Flag to indicate if destination is reachable
  while (true) {
    if (current == t) {  // If current cell is target
      possible = 1;
      break;
    } else if (current == n || visited.count(current)) {  // If out of bounds or already visited
      break;
    } else {
      visited.insert(current);  // Mark current cell as visited
      current = move[current];  // Move to next cell via portal
    }
  }
  puts(possible ? "YES" : "NO");  // Output result
  return 0;
}


// https://github.com/VaHiX/CodeForces/