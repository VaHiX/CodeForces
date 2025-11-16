// Problem: CF 1315 A - Dead Pixel
// https://codeforces.com/contest/1315/problem/A

/*
 * Problem: A. Dead Pixel
 * Purpose: Find the maximum area of a rectangle that can be cut from a screen
 *          without including the dead pixel.
 * 
 * Algorithm:
 *   - The screen has dimensions a x b, with a dead pixel at (x, y).
 *   - To avoid the dead pixel, we consider four possible rectangles:
 *     1. Left rectangle: from column 0 to x-1
 *     2. Right rectangle: from column x+1 to a-1
 *     3. Top rectangle: from row 0 to y-1
 *     4. Bottom rectangle: from row y+1 to b-1
 *   - For each such rectangle, compute its area.
 *   - Return the maximum among all four possible rectangles.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, x, y;
    scanf("%ld %ld %ld %ld", &a, &b, &x, &y);
    
    // Calculate the maximum distance from the dead pixel to either edge in x-direction
    long u = (x > (a - 1 - x)) ? x : (a - 1 - x);
    
    // Calculate the maximum distance from the dead pixel to either edge in y-direction
    long v = (y > (b - 1 - y)) ? y : (b - 1 - y);
    
    // Compute the maximal area of a rectangle that doesn't contain the dead pixel
    long res = (u * b > v * a) ? (u * b) : (v * a);
    printf("%ld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/