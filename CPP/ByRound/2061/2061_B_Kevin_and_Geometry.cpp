// Problem: CF 2061 B - Kevin and Geometry
// https://codeforces.com/contest/2061/problem/B

/*
B. Kevin and Geometry

Purpose:
This program attempts to find four sticks that can form an isosceles trapezoid (including rectangles/squares) 
with positive area from a given list of stick lengths. An isosceles trapezoid has two parallel bases (parallel sides) 
and two equal-length legs (non-parallel sides).

Algorithm:
1. Sort the sticks in descending order.
2. Find the largest pair of equal-length sticks to form one base and leg of the trapezoid.
3. From remaining sticks, select an appropriate fourth stick such that the quadrilateral forms a valid 
   isosceles trapezoid with positive area using triangle inequality.

Time Complexity:
O(n log n) per test case due to sorting; overall complexity depends on number of test cases and total n.

Space Complexity:
O(n) for storing the vector of stick lengths.

Techniques Used:
- Sorting
- Greedy selection based on stick length comparisons
- Validation of trapezoid properties via triangle inequality check

*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    sort(v.rbegin(), v.rend()); // Sort in descending order to easily find largest elements
    long s(-1), sidx(-1), a(-1), b(-1);
    for (long p = 1; p < n; p++) {
      if (v[p - 1] == v[p]) { // Find first pair of equal consecutive elements
        sidx = p;
        s = v[p];
        v[p - 1] = v[p] = -1; // Mark these as used
        break;
      }
    }
    if (v[0] > 0) { // Take the largest available stick as one of the legs/bases
      a = v[0];
      v[0] = -1;
    } else {
      a = v[2]; // Or take third largest if first is already taken
      v[2] = -1;
    }
    for (long p = 1; p < n; p++) {
      if (v[p] < 0) { // Skip marked elements
        continue;
      }
      if (a < 2 * s + v[p]) { // Check triangle inequality condition to form valid trapezoid
        b = v[p];
        break;
      } else {
        a = v[p]; // If not yet enough for valid trapezoid, try next largest as base/leg
      }
    }
    if (b > 0) {
      printf("%ld %ld %ld %ld\n", s, s, a, b); // Output the four sticks forming trapezoid
    } else {
      puts("-1"); // No valid trapezoid found
    }
  }
}


// https://github.com/VaHiX/codeForces/