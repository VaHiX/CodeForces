// Problem: CF 1100 C - NN and the Optical Illusion
// https://codeforces.com/contest/1100/problem/C

/*
Algorithm: Geometric analysis of circle packing
Techniques: Trigonometric relationships in regular polygons

Time Complexity: O(1) - constant time operations including trigonometric functions
Space Complexity: O(1) - only using a constant amount of space

This problem involves finding the radius R of outer circles such that:
- All outer circles touch the inner circle externally
- Adjacent outer circles touch each other
- The outer circles are arranged in a regular polygon around the inner circle

Key insight:
The centers of the outer circles form a regular n-gon. 
The distance between the center of the inner circle and any outer circle center is (R + r).
The distance between centers of two adjacent outer circles is 2R.
Using the law of cosines in the triangle formed by:
- Center of inner circle
- Center of one outer circle
- Center of next outer circle

We derive:  (2R)^2 = (R + r)^2 + (R + r)^2 - 2*(R + r)*(R + r)*cos(2π/n)
Solving for R gives the formula used in the code.
*/

#include <cmath>
#include <cstdio>
#define PI 3.14159265
int main() {
  long n;           // number of outer circles
  double r;         // radius of inner circle
  scanf("%ld %lf", &n, &r);
  // The formula derived from geometric relationships:
  // R = r * sin(π/n) / (1 - sin(π/n))
  printf("%.8lf\n", r * sin(PI / n) / (1 - sin(PI / n)));
  return 0;
}


// https://github.com/VaHiX/CodeForces/