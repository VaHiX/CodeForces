// Problem: CF 623 A - Graph and String
// https://codeforces.com/contest/623/problem/A

/*
 * Code Purpose: Determine if a graph can be represented by a string of 'a', 'b', 'c' 
 * such that two vertices are adjacent if and only if their corresponding characters 
 * are equal or adjacent in the alphabet. Uses a greedy algorithm to assign characters 
 * to vertices.
 *
 * Algorithm: 
 * 1. Build adjacency matrix from input edges.
 * 2. Identify vertices connected to all others (clique) and assign 'b' to them.
 * 3. For remaining vertices, assign 'a' and propagate constraints:
 *    - Vertices connected must be same or adjacent.
 *    - Vertices not connected must be non-adjacent.
 * 4. Check consistency of assignments.
 *
 * Time Complexity: O(n^2) due to nested loops over vertices.
 * Space Complexity: O(n^2) for the adjacency matrix.
 */

#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<std::vector<int>> g(n, std::vector<int>(n, 0)); // adjacency matrix
  std::vector<long> deg(n, 0); // degree of each vertex
  for (long p = 0; p < m; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    --x;
    --y;
    g[x][y] = g[y][x] = 1; // mark edge in adjacency matrix
    ++deg[x];
    ++deg[y];
  }
  std::vector<char> s(n, '-'); // string to store assigned characters
  bool possible(true); // flag to track if solution exists
  
  // Assign 'b' to vertices with degree n-1 (connected to all others)
  for (long p = 0; p < n; p++) {
    if (deg[p] == n - 1) {
      s[p] = 'b';
    }
  }
  
  // Process each vertex to assign characters
  for (long p = 0; p < n; p++) {
    if (!possible) {
      break;
    }
    if (s[p] == 'b') {
      continue; // skip already assigned 'b'
    } else if (s[p] == '-') {
      s[p] = 'a'; // assign 'a' to unassigned vertex
    }
    
    // Examine neighbors of vertex p
    for (long q = 0; q < n; q++) {
      if (p == q) {
        continue; // skip self-loop
      }
      
      if (g[p][q]) { // p and q are connected
        // if q already assigned:
        if (s[q] == s[p] || s[q] == 'b') {
          continue; // valid assignment
        } else if (s[q] == '-') {
          s[q] = s[p]; // propagate same character
        } else {
          possible = false; // conflicting assignment
          break;
        }
      } else { // p and q are not connected
        char expected = (s[p] == 'a') ? 'c' : 'a'; // expected character for non-adjacent
        if (s[q] == '-') {
          s[q] = expected; // assign expected character
        } else if (s[q] == expected) {
          continue; // valid assignment
        } else {
          possible = false; // conflicting assignment
          break;
        }
      }
    }
  }
  
  if (possible) {
    puts("Yes");
    for (long p = 0; p < n; p++) {
      printf("%c", s[p]);
    };
    puts("");
  } else {
    puts("No");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/