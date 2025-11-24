// Problem: CF 1734 B - Bright, Nice, Brilliant
// https://codeforces.com/contest/1734/problem/B

/*
B. Bright, Nice, Brilliant

Purpose:
This program generates an arrangement of torches in a pyramid structure such that:
1. The pyramid is "nice" — all rooms on each floor have the same brightness.
2. The brilliance (sum of brightness of the leftmost room of each floor) is maximized.

Algorithm/Techniques:
- For a pyramid with n floors, we can observe that placing torches in a specific pattern ensures all rooms on a given floor have equal brightness.
- A key insight is to place torches in the first and last positions of each row (except the top), forming a kind of "zigzag" or staircase pattern.
- By setting the first and last elements of every row (except the first) to 1, we create an arrangement where:
   - Each room on a floor receives contributions from torches placed in earlier rows, particularly those directly above or diagonally above.
   - The same brightness is achieved across all rooms in a given row due to symmetry.

Time Complexity: O(n^2)
Space Complexity: O(1) additional space apart from input/output storage

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long row = 0; row < n; row++) {
      for (long col = 0; col <= row; col++) {
        // For each cell, print 1 if it's the first or last element of row, otherwise 0
        printf("%d ", col == 0 || col == row);
      }
      puts(""); // Move to next line after printing a row
    }
  }
}


// https://github.com/VaHiX/codeForces/