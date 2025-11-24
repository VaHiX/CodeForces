// Problem: CF 1971 F - Circle Perimeter
// https://codeforces.com/contest/1971/problem/F

/*
F. Circle Perimeter
Given an integer r, find the number of lattice points that have a Euclidean distance from (0,0) greater than or equal to r but strictly less than r+1.
A lattice point is a point with integer coordinates. The Euclidean distance from (0,0) to the point (x,y) is sqrt(x^2 + y^2).

Algorithm:
- For each x-coordinate p from 1 to n, compute the number of valid y-coordinates such that r <= sqrt(p^2 + y^2) < r+1.
- This translates to finding integer y where sqrt((r+1)^2 - p^2) > y >= sqrt(r^2 - p^2).
- To count valid points in a range, use the difference between floor of upper bound and floor of lower bound.
- The outer loop runs from 1 to n (n steps). For each step, we compute two square roots and perform arithmetic.

Time Complexity: O(n) per test case
Space Complexity: O(1)

*/
#include <cmath>
#include <cstdio>
typedef long long ll;
int main() {
  long t; // number of test cases
  scanf("%ld", &t);
  while (t--) {
    ll n; // radius r
    scanf("%lld", &n);
    ll cnt(1); // start with 1 to count the point (0, n) or (0, -n)
    for (ll p = 1; p <= n; p++) {
      // Compute difference of floor of square roots to count lattice points
      // between circles of radius sqrt(n*n - p*p - 1) and sqrt((n+1)*(n+1) - p*p - 1)
      cnt += (ll)std::sqrt((n + 1) * (n + 1) - p * p - 1) -
             (ll)std::sqrt(n * n - p * p - 1);
    }
    printf("%lld\n", 4 * cnt); // multiply by 4 to account for symmetry in all quadrants
  }
}


// https://github.com/VaHiX/codeForces/