// Problem: CF 2073 L - Boarding Queue
// https://codeforces.com/contest/2073/problem/L

#include <iostream>

#define N 1005
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int r, c, n, p, i, j, g[N][N], x, y, vis[N * N], t;
  cin >> r >> c >> n >> p; // Read grid dimensions, total travelers, and position of traveler p
  // Initialize the grid with zeros (out-of-bounds cells)
  for (i = 0; i <= r + 1; i++)
    for (j = 0; j <= c + 1; j++)
      g[i][j] = 0;
  // Initialize visited array to track which travelers might be adjacent to p
  for (i = 0; i <= n; i++)
    vis[i] = 0;
  // Read the grid values representing traveler positions
  for (i = 1; i <= r; i++)
    for (j = 1; j <= c; j++)
      cin >> g[i][j];
  // Find initial position of traveler p
  for (i = 1; i <= r; i++)
    for (j = 1; j <= c; j++)
      if (p == g[i][j]) {
        x = i;
        y = j;
      }
  t = 0; // Time step counter for tracking boarding progress
  while (true) {
    // Check adjacent cells (up, left, down, right) to see if any travelers are present,
    // and mark those reachable by t steps from p's path using the vis array.
    if (g[x - 1][y] && g[x - 1][y] + t <= n)
      vis[g[x - 1][y] + t] = 1;
    if (g[x][y - 1] && g[x][y - 1] + t <= n)
      vis[g[x][y - 1] + t] = 1;
    if (g[x + 1][y] && g[x + 1][y] + t <= n)
      vis[g[x + 1][y] + t] = 1;
    if (g[x][y + 1] && g[x][y + 1] + t <= n)
      vis[g[x][y + 1] + t] = 1;
    
    // If traveler p reaches a cell marked "1", we stop (because it is the last one to board)
    if (g[x][y] == 1)
      break;
      
    // Move p's path to the next adjacent cell with a value that is exactly one less than current
    if (g[x - 1][y] == g[x][y] - 1)
      x--; // Move up
    else if (g[x][y - 1] == g[x][y] - 1)
      y--; // Move left
    else if (g[x + 1][y] == g[x][y] - 1)
      x++; // Move down
    else
      y++; // Move right
    
    t++; // Increment time step
  }
  x = 0; // Count how many travelers could have been adjacent to p
  y = n - 1; // Total possible coaches (excluding p itself)
  for (i = 1; i <= n; i++)
    x += vis[i]; // Sum up all travelers marked in vis array
  cout << x << '/' << y;
  return 0;
}

/*
 * Problem: Boarding Queue
 * 
 * Purpose:
 * This program computes the probability that a traveler p will be adjacent to their team coach at any point before boarding.
 * It models a dynamic movement on a grid where travelers move in sequence and tracks possible neighbors for each step.
 *
 * Algorithms/Techniques:
 * - Grid traversal with simulation of traveler movement
 * - Adjacency checking in 4 directions (up, down, left, right)
 * - Path tracking via backward propagation from current traveler location to earlier steps
 * 
 * Time Complexity: O(r * c + n) where r is rows, c is columns, and n is number of travelers.
 * Space Complexity: O(r * c) for the grid storage and O(n) for the visited array.
 */

// https://github.com/VaHiX/codeForces/