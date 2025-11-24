// Problem: CF 1076 C - Meme Problem
// https://codeforces.com/contest/1076/problem/C

/*
 * Problem: C. Meme Problem
 * 
 * Given a non-negative integer d, find two non-negative real numbers a and b such that:
 *   a + b = d
 *   a * b = d
 * 
 * This is a system of equations that can be solved by treating it as a quadratic equation.
 * From a + b = d and a * b = d, we derive that a and b are roots of:
 *   x^2 - d*x + d = 0
 * 
 * Using the quadratic formula: x = (d ± sqrt(d^2 - 4*d)) / 2
 * 
 * Time Complexity: O(t), where t is the number of test cases
 * Space Complexity: O(1)
 */

#include <cmath>
#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    double d;
    scanf("%lf", &d);
    if (d == 0.0) {
      // If d is 0, then both a and b must be 0 to satisfy both equations
      puts("Y 0.0 0.0");
    } else if (d < 4) {
      // For d < 4, the discriminant (d^2 - 4*d) is negative or zero,
      // which implies real solutions don't exist or are invalid
      puts("N");
    } else {
      // Compute the two roots using quadratic formula
      // a = (d + sqrt(d^2 - 4*d)) / 2
      // b = (d - sqrt(d^2 - 4*d)) / 2
      printf("Y %.9lf %.9lf\n", (d + sqrt(d * d - 4 * d)) / 2,
             (d - sqrt(d * d - 4 * d)) / 2);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/