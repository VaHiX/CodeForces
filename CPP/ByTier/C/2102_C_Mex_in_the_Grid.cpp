// Problem: CF 2102 C - Mex in the Grid
// https://codeforces.com/contest/2102/problem/C

/*
C. Mex in the Grid

Purpose:
This code solves the problem of arranging numbers from 0 to n^2 - 1 in an n x n grid 
to maximize the sum of MEX (minimum excluded value) over all possible subgrids.
The algorithm fills the grid in a spiral pattern starting from the top-left corner,
which helps to distribute values such that smaller values appear early and more frequently
in small subgrids, thus increasing the total MEX sum.

Algorithms/Techniques:
- Spiral filling of grid: The grid is filled by moving in a clockwise spiral pattern (right -> down -> left -> up),
  changing direction only when hitting boundaries or already filled cells.
- Directional Movement: Uses predefined directional arrays to move in four directions.

Time Complexity: O(n^2)
Space Complexity: O(n^2)

*/

#include <iostream>

#define N 505
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t, n, i, j, a[N][N], x;
  // Directional arrays: right, down, left, up
  int di[4] = {0, 1, 0, -1}, dj[4] = {1, 0, -1, 0}, d;
  
  cin >> t;
  while (t--) {
    cin >> n;
    
    // Initialize grid with -1
    for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
        a[i][j] = -1;
        
    x = n * n - 1;  // Start from the largest number
    i = j = 1;      // Starting position
    d = 0;          // Initial direction: right
    
    // Fill grid in spiral manner
    while (x >= 0) {
      a[i][j] = x;
      x--;
      
      // Check if we need to turn (next cell out of bounds or already filled)
      if (i + di[d] > n || i + di[d] < 1 || 
          j + dj[d] > n || j + dj[d] < 1 ||
          a[i + di[d]][j + dj[d]] != -1)
        d = (d + 1) % 4;  // Change direction clockwise
        
      // Move to next cell
      i = i + di[d];
      j = j + dj[d];
    }
    
    // Output the grid
    for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++)
        cout << a[i][j] << ' ';
      cout << '\n';
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/