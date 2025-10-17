// Problem: CF 1921 A - Square
// https://codeforces.com/contest/1921/problem/A

/*
Problem: Find the area of a square given its four corners in random order.
Algorithms/Techniques: 
    - Identify square sides by checking parallel lines (equal x or y coordinates)
    - Compute length and width from differences in coordinates
    - Calculate area as product of length and width

Time Complexity: O(1) per test case (constant number of operations)
Space Complexity: O(1) (only using fixed-size arrays)

A. Square
time limit per test1 second
memory limit per test256 megabytes
A square of positive (strictly greater than
0
) area is located on the coordinate plane, with sides parallel to the coordinate axes. You are given the coordinates of its corners, in random order. Your task is to find the area of the square.
Input
Each test consists of several testcases. The first line contains one integer
t
(
1≤t≤100
) — the number of testcases. The following is a description of the testcases.
Each testcase contains four lines, each line contains two integers
x
i
,
y
i
(
−1000≤
x
i
,
y
i
≤1000
), coordinates of the corners of the square.
It is guaranteed that there is a square with sides parallel to the coordinate axes, with positive (strictly greater than
0
) area, with corners in given points.
Output
For each test case, print a single integer, the area of the square.
Example
input
Copy
3
1 2
4 5
1 5
4 2
-1 1
1 -1
1 1
-1 -1
45 11
45 39
17 11
17 39
output
Copy
9
4
784
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x[4], y[4];
    for (long p = 0; p < 4; p++) {
      scanf("%ld %ld", x + p, y + p); // Read coordinates of each corner
    }
    long length(0), width(0);
    for (long p = 1; !length && p < 4; p++) {
      if (x[p] == x[0]) { // Check if side is vertical (same x coordinate)
        length = y[p] - y[0]; // Calculate vertical side length
      }
    }
    for (long p = 1; !width && p < 4; p++) {
      if (y[p] == y[0]) { // Check if side is horizontal (same y coordinate)
        width = x[p] - x[0]; // Calculate horizontal side length
      }
    }
    long area = length * width; // Compute area
    if (area < 0) {
      area *= -1; // Ensure positive area
    }
    printf("%ld\n", area);
  }
}


// https://github.com/VaHiX/codeForces/