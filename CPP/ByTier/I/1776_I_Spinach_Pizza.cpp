// Problem: CF 1776 I - Spinach Pizza
// https://codeforces.com/contest/1776/problem/I

/*
 * Purpose: Solve the Spinach Pizza game where two players (Alberto and Beatrice) alternately remove triangles from a convex polygon,
 *          aiming to eat at most half of the total area. The strategy is based on the number of vertices and optimal greedy selection.
 *
 * Algorithms/Techniques:
 * - Game theory: Based on parity of number of vertices, the first or second player can guarantee eating at most half.
 * - Greedy approach: At each turn, pick the triangle with minimum area to minimize eaten portion.
 * - Convex polygon triangulation: Area calculation using cross product formula for triangle.
 *
 * Time Complexity: O(n^3) - For each of the (n-2)/2 turns, we check all unvisited vertices and their neighbors.
 * Space Complexity: O(n) - To store coordinates and visited flags.
 */

#include <stdlib.h>
#include <iostream>

using namespace std;
long long x[100], y[100], vis[100];  // Arrays to store x,y coordinates and visited status of vertices

// Function to calculate the area of a triangle using cross product
long long calcarea(int i, int j, int k) {
  return llabs((y[i] - y[j]) * (x[i] - x[k]) - (y[i] - y[k]) * (x[i] - x[j]));
}

int main() {
  int n, i, j, k, T, mxp, q;
  long long curmx, cura;
  cin >> n;
  for (i = 0; i < n; i++)
    cin >> x[i] >> y[i];
  
  // If the number of vertices is even, Alberto (the first player) can guarantee winning
  if (n % 2 == 0)
    cout << "Alberto" << endl;
  else {
    // If odd, Beatrice (the second player) is guaranteed to win
    cout << "Beatrice\n";
    cin >> q;
    vis[q - 1] = 1;  // Mark the chosen vertex as visited
  }
  
  // Main game loop, iterating for (n-2)/2 turns (since each turn removes one vertex)
  for (T = (n - 2) / 2; T > 0; T--) {
    curmx = 1e18;  // Initialize with a large value for minimum area
    for (i = 0; i < n; i++) {
      if (vis[i])
        continue;  // Skip if the vertex is already used
      
      // Find the previous unvisited vertex
      for (j = i + n - 1; vis[j % n] == 1; j--)
        ;
      
      // Find the next unvisited vertex
      for (k = i + 1; vis[k % n] == 1; k++)
        ;
      
      // Calculate area of triangle formed by i, j, k
      cura = calcarea(i, j % n, k % n);
      
      // Keep track of the triangle with minimum area
      if (cura < curmx) {
        curmx = cura;
        mxp = i;
      }
    }
    
    cout << mxp + 1 << endl;  // Output the chosen vertex (1-indexed)
    vis[mxp] = 1;  // Mark it as visited
    
    cin >> q;
    vis[q - 1] = 1;  // Mark opponent's choice as visited
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/