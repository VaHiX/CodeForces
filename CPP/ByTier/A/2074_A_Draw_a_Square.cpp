// Problem: CF 2074 A - Draw a Square
// https://codeforces.com/contest/2074/problem/A

/*
 * Problem: A. Draw a Square
 * Algorithm/Techniques: Geometry, Square validation
 *
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), constant space usage.
 *
 * The problem asks to determine if four given points can form a square.
 * Points are:
 *   - L = (-l, 0)
 *   - R = (r, 0)
 *   - D = (0, -d)
 *   - U = (0, u)
 * For these to form a square, all sides must be equal and all angles 90 degrees.
 * This code checks if l == r == d == u, because only then will the points
 * form a square centered at origin with sides of equal length.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r, d, u;
    scanf("%ld %ld %ld %ld", &l, &r, &d, &u);
    puts((l == r && l == d && d == u) ? "Yes" : "No"); // Check if all values are equal to form a square
  }
}


// https://github.com/VaHiX/codeForces/