// Problem: CF 1982 A - Soccer
// https://codeforces.com/contest/1982/problem/A

/*
Problem: Soccer
Algorithm/Techniques: Math, Coordinate analysis
Time Complexity: O(1) per test case
Space Complexity: O(1)

Given two scores (x1, y1) and (x2, y2), determine if it's possible that the teams never had equal scores during the interval.
The key insight is to analyze the relative positions of the two points in a coordinate system where x-axis represents goals of first team and y-axis represents goals of second team.
If the product (x1 - y1) * (x2 - y2) > 0, it means both points are on the same side of the line y = x, which means no tie occurred.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long long x1, y1, x2, y2;
    scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
    // Check if both points are on the same side of line y = x
    puts((x1 - y1) * (x2 - y2) > 0 ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/