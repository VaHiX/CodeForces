// Problem: CF 2027 A - Rectangle Arrangement
// https://codeforces.com/contest/2027/problem/A

/*
 * Problem: Minimum Perimeter of Black Regions After Stamping
 * Algorithm/Technique: Rectangle Arrangement
 *
 * Time Complexity: O(n) per test case, where n is the number of stamps.
 * Space Complexity: O(1), only using a constant amount of extra space.
 *
 * Description:
 * We are given n rectangular stamps, each with width w_i and height h_i.
 * We must place each stamp exactly once on an infinite grid to form black regions.
 * The goal is to minimize the total perimeter of all connected black regions.
 *
 * Key Insight:
 * To minimize the total perimeter, we should try to stack as many rectangles as possible
 * in a way that reduces the exposed edges. The minimal configuration occurs when
 * we align all rectangles such that one dimension is maximized (say width) and the other
 * (height) is also maximized. Then the optimal arrangement forms a single large rectangle.
 *
 * Approach:
 * - For each test case, find the maximum width (m) and maximum height (p) among all stamps.
 * - The minimum perimeter is then 2 * (m + p), because the best layout makes a rectangle
 *   of dimensions m x p which has this perimeter.
 */

using System;
using static System.Console;

class Program {
  static void Main() {
    int t = int.Parse(ReadLine()); // Read number of test cases
    while (t-- > 0) {
      int n = int.Parse(ReadLine()); // Read number of stamps
      int m = 0, p = 0; // m stores max width, p stores max height
      for (int i = 0; i < n; i++) {
        var asd = ReadLine().Split(); // Read stamp dimensions
        int w = int.Parse(asd[0]); // Width of current stamp
        int h = int.Parse(asd[1]); // Height of current stamp
        m = Math.Max(m, w); // Update max width
        p = Math.Max(p, h); // Update max height
      }
      WriteLine(2 * (m + p)); // Output minimum perimeter
    }
  }
}


// https://github.com/VaHiX/codeForces/