// Problem: CF 2027 A - Rectangle Arrangement
// https://codeforces.com/contest/2027/problem/A

/*
 * Problem: Minimum Perimeter of Connected Black Regions After Stamping
 * Algorithm/Techniques: Rectangle Arrangement
 *
 * Approach:
 * - For each test case, we are given n stamps, each with width wi and height hi.
 * - We want to place these stamps on an infinite grid such that the total perimeter
 *   of all connected black regions is minimized.
 * - Key insight: To minimize total perimeter, we should try to align all stamps
 *   along one axis (either horizontal or vertical) and stack them to reduce exposed edges.
 * - The optimal strategy is to find the maximum width and height among all stamps,
 *   then arrange them in a way that they form a single large rectangle.
 * - Total perimeter = 2 * (max_width + max_height) * 2 (since we can overlap optimally).
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mxw(0), mxh(0);  // Track maximum width and height seen so far
    for (long p = 0; p < n; p++) {
      long w, h;
      scanf("%ld %ld", &w, &h);
      mxw = (mxw > w ? mxw : w);  // Update maximum width
      mxh = (mxh > h ? mxh : h);  // Update maximum height
    }
    printf("%ld\n", 2 * (mxw + mxh));  // Output the minimum possible perimeter
  }
}


// https://github.com/VaHiX/codeForces/