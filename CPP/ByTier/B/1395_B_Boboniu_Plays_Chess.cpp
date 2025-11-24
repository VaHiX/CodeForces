// Problem: CF 1395 B - Boboniu Plays Chess
// https://codeforces.com/contest/1395/problem/B

/*
Algorithm/Techniques: 
The solution uses a cyclic rotation technique to generate a Hamiltonian path that visits every cell exactly once.
It starts from the given position (x, y) and generates a sequence of moves by applying a cyclic shift to the row and column indices.
This ensures that all cells are visited exactly once in a valid chess rook-like traversal.

Time Complexity: O(n * m) - We iterate through all n*m cells exactly once.
Space Complexity: O(1) - Only a constant amount of extra space is used, not counting the output.
*/

#include <cstdio>
int main() {
  long n, m, x, y;
  scanf("%ld %ld %ld %ld", &n, &m, &x, &y);
  for (long row = 1; row <= n; row++) {
    if (row % 2) {
      // For odd rows, move left to right
      for (long col = 1; col <= m; col++) {
        // Apply cyclic shift to row and column indices to determine the next cell
        printf("%ld %ld\n", 1 + (row + x - 2) % n, 1 + (col + y - 2) % m);
      }
    } else {
      // For even rows, move right to left
      for (long col = m; col >= 1; col--) {
        // Apply cyclic shift to row and column indices to determine the next cell
        printf("%ld %ld\n", 1 + (row + x - 2) % n, 1 + (col + y - 2) % m);
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/