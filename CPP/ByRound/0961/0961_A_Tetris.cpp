// Problem: CF 961 A - Tetris
// https://codeforces.com/contest/961/problem/A

/*
Code purpose: This program calculates the number of times a full row can be removed from a Tetris-like platform. 
Each column starts empty, and blocks are added one by one. When all columns have at least one block, 
the bottom row is removed, and all blocks fall down. The number of such removals is the output.

Algorithms/Techniques: 
- Simulation of block placement
- Tracking of column heights
- Finding minimum height to determine how many complete rows can be removed

Time Complexity: O(n + m) where n is the number of columns and m is the number of blocks.
Space Complexity: O(n) for storing the column heights.
*/

#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> a(n, 0); // Array to store the height of each column
  for (long p = 0; p < m; p++) {
    long x;
    scanf("%ld", &x);
    ++a[x - 1]; // Increment the height of the column (1-indexed input converted to 0-indexed)
  }
  long mn(m); // Initialize minimum height to maximum possible value
  for (long p = 0; p < n; p++) {
    mn = (mn < a[p]) ? mn : a[p]; // Update minimum height across all columns
  }
  printf("%ld\n", mn); // Output the number of complete rows that can be removed
  return 0;
}


// https://github.com/VaHiX/CodeForces/