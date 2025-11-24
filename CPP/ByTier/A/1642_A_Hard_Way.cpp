// Problem: CF 1642 A - Hard Way
// https://codeforces.com/contest/1642/problem/A

/*
Code Purpose:
This program determines the total length of the "unsafe" parts of the border of a triangular downtown in Awesomeburg.
A point on the border is considered "unsafe" if there exists no straight-line path from the line y=0 to that point 
without crossing the interior of the triangle.

The algorithm works by:
1. Reading the triangle's vertices.
2. Sorting the vertices by y-coordinate in descending order.
3. Checking if the two highest vertices have the same y-coordinate.
   - If so, the length of the unsafe segment is the difference in their x-coordinates.
   - Otherwise, the unsafe segment length is 0.

Time Complexity: O(1) per test case (sorting 3 elements is constant time)
Space Complexity: O(1) (only using a fixed-size vector and variables)

Algorithms/Techniques:
- Sorting vertices by y-coordinate (descending)
- Line segment comparison and computation
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    std::vector<std::pair<long, long>> v(3);
    for (long p = 0; p < 3; p++) {
      scanf("%ld %ld", &v[p].second, &v[p].first);  // Note: coordinates are read as (y, x) due to scanf order
    }
    sort(v.rbegin(), v.rend());  // Sort by y-coordinate in descending order
    double res = (v[0].first == v[1].first) ? (v[0].second - v[1].second) : 0.0;  // If top two points have same y, unsafe length is x difference
    printf("%.9lf\n", res);
  }
}


// https://github.com/VaHiX/CodeForces/