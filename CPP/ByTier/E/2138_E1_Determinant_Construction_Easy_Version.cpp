// Problem: CF 2138 E1 - Determinant Construction (Easy Version)
// https://codeforces.com/contest/2138/problem/E1

/*
E1. Determinant Construction (Easy Version)
Algorithms/Techniques: Matrix construction using GCD and recursive determinant building techniques.
Time Complexity: O(t * log^2(x)) where t is number of test cases, x is the target determinant value.
Space Complexity: O(1) excluding output space (fixed size matrices up to 80x80).

This code constructs a square matrix with determinant equal to given integer x,
with constraints that each row/column has at most 3 non-zero entries and
all elements are in {-1, 0, 1}.
 */
#include <math.h>
#include <stdio.h>
#include <utility>
using namespace std;
double pi = (sqrt(5.0) - 1.0) / 2.0; // Golden ratio constant used for approximation
int w, n, x, y, cnt, f[111][111];     // Global variables for computation

// Compute greatest common divisor using Euclidean algorithm
int gcd(int a, int b) {
  if (a == 0 || b == 0)
    return a + b;
  return gcd(b, a % b);
}

// Recursive function to build a matrix for a given pair (a, b)
bool find(int a, int b) {
  cnt = 1;
  while (a > 1 || b > 1) {
    if (cnt >= 80)
      return 0; // Maximum matrix size exceeded
    if (a >= b) {
      swap(a, b);              // Ensure a <= b
      b = b - a;               // Reduce second value by first
      f[cnt][cnt] = 1;         // Place 1 on diagonal
      f[cnt][cnt + 1] = 1;     // Place 1 next to diagonal
      f[cnt + 1][cnt] = -1;    // Place -1 below diagonal
      cnt++;                   // Increment counter
    } else {
      swap(a, b);              // Ensure a <= b
      b = a - b;               // Reduce first value by second
      f[cnt][cnt] = 1;         // Place 1 on diagonal
      f[cnt][cnt + 1] = 1;     // Place 1 next to diagonal
      f[cnt + 1][cnt] = 1;     // Place 1 below diagonal
      cnt++;                   // Increment counter
    }
  }
  f[cnt][cnt] = 1;           // Final step in recursion - set last element to 1
  return 1;
}

// Find valid a,b such that gcd(a,b)=1 and find() succeeds
bool gao(int a, int b) {
  for (int i = 0; i <= 20; i++) {
    if (gcd(a, b + i) == 1) {      // Try increasing b by i to make GCD=1
      if (find(a, b + i)) {
        return 1;
      }
    }
    if (b - i >= 1) {              // Ensure we don't go below 1
      if (gcd(a, b - i) == 1) {    // Try decreasing b by i to make GCD=1
        if (find(a, b - i)) {
          return 1;
        }
      }
    }
  }
  return 0;
}

// Main solve logic with optimization to handle large x values
void solve(int a) {
  x = a;
  y = ((int)(pi * a));         // Estimate based on golden ratio approximation
  if (!gao(x, y)) {            // If not yet solved, try different values
    for (int i = 2; i <= y; i++) {
      if (gao(x, y / i)) {     // Use division to find a suitable pair
        break;
      }
    }
  }
  printf("%d\n", cnt);         // Output matrix dimension
  for (int i = 1; i <= cnt; i++) {
    for (int j = 1; j <= cnt; j++)
      printf("%d ", f[i][j]);  // Print matrix row by row
    printf("\n");
  }
}

int main() {
  scanf("%d", &w);             // Read number of test cases
  while (w) {
    w--;
    scanf("%d", &n);           // Read target determinant value
    if (n > 1) {               // If n > 1, construct matrix
      solve(n);
    } else {                   // For n = 1, special case handled directly
      printf("1\n");
      printf("%d\n", n);
    }
  }
}


// https://github.com/VaHiX/codeForces/