// Problem: CF 1767 A - Cut the Triangle
// https://codeforces.com/contest/1767/problem/A

/*
A. Cut the Triangle
time limit per test2 seconds
memory limit per test512 megabytes

Algorithm:
The problem asks whether we can cut a triangle into two non-degenerate triangles using a straight line that is either horizontal or vertical.

Key insight:
- For a valid cut, the line must pass through the triangle such that both resulting parts are also triangles.
- If the line is horizontal (y = constant), it intersects the triangle at most at two points and splits the triangle into two pieces only if one vertex lies above the line and another below.
- Similarly for vertical lines (x = constant).
- It's possible to do so **if** two of the vertices share the same x-coordinate or two of them share the same y-coordinate — allowing a vertical or horizontal cut respectively.

Time Complexity: O(1) per test case
Space Complexity: O(1)

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long xa, ya, xb, yb, xc, yc;
    scanf("%ld %ld", &xa, &ya);       // Read vertex A
    scanf("%ld %ld", &xb, &yb);       // Read vertex B
    scanf("%ld %ld", &xc, &yc);       // Read vertex C
    
    // Check if any two vertices share the same x or y coordinate.
    // If so, then a horizontal or vertical cut is possible to split triangle into two valid triangles.
    puts(((xa == xb || xa == xc || xb == xc) &&
          (ya == yb || ya == yc || yb == yc))
             ? "NO"
             : "YES");
  }
}


// https://github.com/VaHiX/codeForces/