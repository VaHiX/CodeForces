// Problem: CF 1986 A - X Axis
// https://codeforces.com/contest/1986/problem/A

/*
 * Problem: X Axis
 * Purpose: Find the minimum total distance from three given points on the X-axis to a chosen point 'a'.
 * Algorithm: The optimal point 'a' is the median of the three given points.
 *            The minimum total distance is the difference between the maximum and minimum coordinates.
 * Time Complexity: O(1) per test case - constant time operations.
 * Space Complexity: O(1) - only using a fixed number of variables.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    long mn = (a < b ? a : b);           // Find minimum of a and b
    mn = (mn < c ? mn : c);              // Update mn with minimum of mn and c
    long mx = (a > b ? a : b);           // Find maximum of a and b
    mx = (mx > c ? mx : c);              // Update mx with maximum of mx and c
    printf("%ld\n", mx - mn);            // Output the difference between max and min
  }
}


// https://github.com/VaHiX/codeForces/