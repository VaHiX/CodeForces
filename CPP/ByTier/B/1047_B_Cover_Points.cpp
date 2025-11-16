// Problem: CF 1047 B - Cover Points
// https://codeforces.com/contest/1047/problem/B

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long mxs(0); // Initialize maximum sum of coordinates
  while (n--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    long sum = x + y; // Calculate sum of coordinates for current point
    mxs = (mxs > sum) ? mxs : sum; // Keep track of maximum sum
  }
  printf("%ld\n", mxs); // Output the minimum length of shorter side
  return 0;
}
/*
B. Cover Points

Purpose: Find the minimum length of the shorter side of an isosceles triangle 
with two sides on coordinate axes that covers all given points.

Algorithm: 
- Since we need to place an isosceles triangle with two sides on coordinate axes,
  the triangle's vertices will be at (0,0), (a,0), and (0,a) where 'a' is the side length
- For any point (x,y) to be covered, it must satisfy x + y ≤ a
- Therefore, the minimum 'a' needed is the maximum value of (x + y) among all points

Time Complexity: O(n) - single pass through all points
Space Complexity: O(1) - only using constant extra space
*/

// https://github.com/VaHiX/codeForces/