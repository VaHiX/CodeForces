// Problem: CF 1089 M - Minegraphed
// https://codeforces.com/contest/1089/problem/M

/*
 * Purpose: This program designs a 3D game field for the "Minegraphed" game such that the 
 * reachability of labeled positions in the field matches the reachability of vertices in a 
 * given directed graph. 
 * 
 * Algorithm:
 * - The field is constructed as a 3D parallelepiped with dimensions 3n x 3n x 3.
 * - Each vertex of the graph is represented by a labeled cell (1 to n) in the bottom layer.
 * - The connections between vertices (edges in the graph) are encoded as paths in the 3D field:
 *   - A path from vertex i to vertex j is modeled by a sequence of empty cells that allow
 *     movement from i's position to j's position.
 * - A "railway-like" structure is created:
 *   - The top layer has a horizontal track at i*3 + 1 where i is the vertex index.
 *   - The middle layer contains pathways to support transitions between tracks.
 *   - The bottom layer contains all vertex labels.
 * 
 * Time Complexity: O(n^2), due to nested loops scanning and setting up the path connections
 * Space Complexity: O(n^2), for storing the 3D field structure (3 * 3n * 3n)
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
int n;
char s[3][27][27]; // 3D grid storing the 3 layers of the field
int main() {
  scanf("%d", &n);
  // Initialize all cells to '#' (obstacles)  
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3 * n; j++)
      fill(s[i][j], s[i][j] + 3 * n, '#');
  
  // Iterate for each vertex in the graph
  for (int i = 0; i < n; i++) {
    // Clear horizontal lines in top and bottom layers for this vertex
    for (int j = 0; j < 3 * n; j++) {
      s[0][i * 3][j] = s[2][j][i * 3] = '.';
    }
    
    // Clear cells in the middle layer to form a path from the top to the bottom for this vertex  
    s[1][i * 3][i * 3 + 1] = s[1][i * 3 + 1][i * 3 + 1] = 
        s[2][i * 3 + 1][i * 3 + 1] = '.';
    
    // For each vertex j, determine if there is an edge from i to j
    for (int j = 0, ti; j < n; j++) {
      scanf("%d", &ti);
      if (ti) {
        // If there's an edge, make a path in the middle layer to connect to this vertex j
        for (int k = 0; k < 3; k++)
          s[k][i * 3 + 1][j * 3 + 1] = '.';
      }
    }
    
    // Place a label (digit) in the bottom layer for vertex i
    s[0][i * 3][n * 3 - 1] = i + '1';
  }
  
  // Output the dimensions of the field
  printf("%d %d %d\n", n * 3, n * 3, 3);
  
  // Output each layer of the field
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3 * n; j++) {
      for (int k = 0; k < 3 * n; k++) {
        putchar(s[i][j][k]); // Print the character at this cell
      }
      putchar('\n');
    }
    if (i != 2)
      putchar('\n'); // Separate layers with a blank line (except the last)
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/