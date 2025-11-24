// Problem: CF 2138 E2 - Determinant Construction (Hard Version)
// https://codeforces.com/contest/2138/problem/E2

/*
E2. Determinant Construction (Hard Version)
Algorithms/Techniques: Bit manipulation, matrix construction based on binary representation of target value.
Time Complexity: O(log(x) * n) where n is the side length of the matrix (at most 50).
Space Complexity: O(1) since we use fixed-size arrays (55x55 at most).

This code constructs a square matrix with determinant equal to the input value x.
The matrix has elements from {-1, 0, 1}, and each row/column has at most 3 non-zero entries.
It uses binary representation of x to determine structure of matrix,
and builds it using specific patterns ensuring determinant matches x.
*/

#include <stdio.h>
const int N = 100;
int K;
int n;
int a[N + 5][N + 5];
int b[N + 5];
int g[N + 5];

void clean() {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      a[i][j] = 0;
  for (int i = 0; i <= 25; ++i)
    b[i] = g[i] = 0;
  n = 0;
}

void work() {
  scanf("%d", &K);
  if (!K) {
    printf("1\n0\n"); // Special case: determinant 0 matrix is just a zero matrix of size 1x1
    return;
  }
  if (K == 1) {
    printf("1\n1\n"); // Special case: 1x1 matrix with value 1
    return;
  }

  for (int i = 0; i <= 25; ++i) {
    b[i] = (K >> i) & 1; // Decompose K into binary bits
  }

  // Process binary representation to build structure of the matrix
  for (int i = 0; i <= 25; ++i) {
    if (b[i] == 1 && b[i + 1] == 1) { // Two consecutive 1s in bit pattern
      for (int j = i + 1; j <= 25; ++j)
        if (b[j] == 1 && b[j + 1] == 0 && b[j + 2] == 0) { // Look for a gap before 0s
          g[j + 1] = 1;     // Set next bit as positive (to handle sequence)
          for (int k = i + 2; k <= j; ++k)
            if (b[k] == 0)
              g[k] = -1;    // Mark gaps as negative for offsetting
          g[i] = -1;
          i = j + 2;
          break;
        }
    } else if (b[i] == 1) {
      g[i] = 1; // Simple case: single 1 bit contributes directly
    }
  }

  // Determine matrix size n based on highest set bit in binary decomposition
  for (int i = 25; ~i; --i) {
    if (g[i] == 1) {
      n = i * 2;
      break;
    }
  }

  // Initialize standard pattern for matrix structure
  for (int i = 1; i <= n / 2; ++i) {
    a[i * 2][i * 2] = 1;
    a[i * 2 - 1][i * 2 - 1] = 1;
    a[i * 2 - 1][i * 2] = 1;
    a[i * 2][i * 2 - 1] = -1;
    if (i * 2 + 1 <= n)
      a[i * 2][i * 2 + 1] = 1;
  }

  // Fill in values based on g[i] array
  for (int i = 0, x = n - 1, y = 2; i <= n / 2 - 1; ++i) {
    if (g[i]) {
      a[x][y] = (1 - ((x - y) & 1) * 2) * g[i]; // Alternate signs based on indices
    }
    if (i & 1)
      x -= 2;
    else
      y += 2; // Traverse diagonals in specific pattern
  }

  printf("%d\n", n);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      printf("%d ", a[i][j]);
    }
    printf("\n");
  }
}

int Tcase;
int main() {
  scanf("%d", &Tcase);
  while (Tcase--) {
    clean();
    work();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/