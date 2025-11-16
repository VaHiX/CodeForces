// Problem: CF 710 C - Magic Odd Square
// https://codeforces.com/contest/710/problem/C

/*
 * Magic Odd Square
 * 
 * Algorithm: This code generates a magic square of odd order n using the Siamese method.
 * The Siamese method constructs a magic square where all rows, columns, and diagonals sum to the same value.
 * However, this specific implementation is adapted to ensure that all sums are odd by appropriately placing numbers.
 * 
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 * 
 * Techniques:
 * - Siamese method for constructing magic squares
 * - Modular arithmetic to handle out-of-bounds indices
 * 
 * The algorithm starts placing numbers in the middle of the top row and follows a specific pattern:
 * Move up and to the right for each next number. If a cell is already occupied, place the number
 * below the previous one and continue.
 */

#include <cstdio>
#include <iostream>

using namespace std;
int main() {
  int i, j, k;
  int n, c, p, ai, aj;
  cin >> n;
  int a[n][n];
  // Initialize the matrix with zeros
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      a[i][j] = 0;
    }
  }
  // Start position: middle of the top row
  i = 0;
  j = n / 2;
  // Fill the matrix with numbers from 1 to n^2
  for (c = 1; c <= (n * n); c++) {
    if (a[i][j] == 0) {
      a[i][j] = c;
      ai = i;
      aj = j;
      i--;
      j++;
    } else {
      i = ai;
      j = aj;
      i++;
      ai = i;
      aj = j;
      a[i][j] = c;
      i--;
      j++;
    }
    // Handle wraparound for indices
    if (i == -1) {
      i = n - 1;
    }
    if (j == n) {
      j = 0;
    }
    if (j == -1) {
      j = n - 1;
    }
    if (i == n) {
      i = 0;
    }
  }
  // Print the resulting matrix
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      printf("%2d ", a[i][j]);
    }
    printf("\n");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/