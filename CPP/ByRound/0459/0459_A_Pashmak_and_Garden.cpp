// Problem: CF 459 A - Pashmak and Garden
// https://codeforces.com/contest/459/problem/A

#include <cmath>
#include <cstdio>
int main() {
  int x1, y1, x2, y2;
  scanf("%d %d %d %d\n", &x1, &y1, &x2, &y2);
  if (x1 == x2) {
    // Vertical line case: same x-coordinate
    // Compute the side length of the square
    int length = (y1 > y2) ? (y1 - y2) : (y2 - y1);
    // The other two corners are at (x1 + length, y1) and (x2 + length, y2)
    printf("%d %d %d %d\n", x1 + length, y1, x2 + length, y2);
  } else if (y1 == y2) {
    // Horizontal line case: same y-coordinate
    // Compute the side length of the square
    int length = (x1 > x2) ? (x1 - x2) : (x2 - x1);
    // The other two corners are at (x1, y1 + length) and (x2, y2 + length)
    printf("%d %d %d %d\n", x1, y1 + length, x2, y2 + length);
  } else {
    // Diagonal line case: neither x1==x2 nor y1==y2
    // Compute diagonal squared
    long diagonal = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    // Compute expected side length from diagonal
    long length = sqrt(diagonal / 2);
    // Compute slope (tangent) of the diagonal line
    double tan = (y2 - y1) / (x2 - x1);
    // Check if it's a valid square (diagonal has slope ±1, and diagonal^2 = 2*side^2)
    if ((tan != 1 && tan != -1) || 2 * length * length != diagonal) {
      puts("-1"); // Invalid square
    } else {
      // If valid, compute the other two vertices
      printf("%d %d %d %d\n", x1, y2, x2, y1);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/