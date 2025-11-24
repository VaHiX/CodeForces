// Problem: CF 1873 C - Target Practice
// https://codeforces.com/contest/1873/problem/C

/*
C. Target Practice
time limit per test1 second
memory limit per test256 megabytes

A 10×10 target is made out of five "rings" as shown. Each ring has a different point value: 
the outermost ring — 1 point, the next ring — 2 points, ..., the center ring — 5 points.
Vlad fired several arrows at the target. Help him determine how many points he got.

Algorithms/Techniques:
- For each arrow ('X') on the grid, compute its Manhattan distance to the nearest edge of the 10x10 grid.
- Based on that distance, calculate which ring it belongs to (ring 1 to 5).
- Sum up the point values accordingly.

Time Complexity: O(t * B^2) where B=10 (constant), so effectively O(t)
Space Complexity: O(B^2) for storing the 10x10 grid per test case.

Input:
The input consists of multiple test cases. The first line of the input contains a single integer
t (1≤t≤1000) — the number of test cases.
Each test case consists of 10 lines, each containing 10 characters. Each character in the grid is either
X (representing an arrow) or . (representing no arrow).

Output:
For each test case, output a single integer — the total number of points of the arrows.

Example:
input
4
X.........
..........
.......X..
.....X....
......X...
..........
.........X
..X.......
..........
.........X
..........
..........
..........
..........
..........
..........
..........
..........
..........
..........
..........
..........
..........
..........
....X.....
..........
..........
..........
..........
..........
XXXXXXXXXX
XXXXXXXXXX
XXXXXXXXXX
XXXXXXXXXX
XXXXXXXXXX
XXXXXXXXXX
XXXXXXXXXX
XXXXXXXXXX
XXXXXXXXXX
XXXXXXXXXX
output
17
0
5
220
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  const int B = 10;
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::vector<std::string> m(B); // Store the 10x10 grid
    for (long p = 0; p < B; p++) {
      std::cin >> m[p]; // Read each row of the grid
    }
    long total(0);
    for (long row = 0; row < B; row++) {
      for (long col = 0; col < B; col++) {
        if (m[row][col] == '.') {
          continue; // Skip empty cells
        }
        // Find the minimum distance to any edge (row or column)
        long xrow = (row < B - 1 - row) ? row : (B - 1 - row);
        long xcol = (col < B - 1 - col) ? col : (B - 1 - col);
        // The score is 1 plus the minimum of the two distances
        long score = 1 + (xrow < xcol ? xrow : xcol);
        total += score;
      }
    }
    printf("%ld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/