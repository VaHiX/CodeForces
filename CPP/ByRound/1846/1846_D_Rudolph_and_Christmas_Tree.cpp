// Problem: CF 1846 D - Rudolph and Christmas Tree
// https://codeforces.com/contest/1846/problem/D

/*
Code Purpose:
This program calculates the total area of triangular Christmas tree branches,
accounting for overlaps between consecutive branches. Each branch is an isosceles
triangle with base `d` and height `h`, positioned at different heights `y_i`.
Overlapping regions are subtracted to avoid double counting.

Algorithm:
- For each branch, add its full area.
- If a branch overlaps with the previous one, compute the overlapping area
  by determining how much of the previous branch is covered by the current one.
- The overlap is calculated using similar triangles, based on vertical distance
  between the two branches and their heights.

Time Complexity: O(n log n) per test case due to sorting, and O(n) for processing.
Space Complexity: O(n) for storing branch heights.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    long double d, h;
    scanf("%ld %Lf %Lf", &n, &d, &h);
    const long double area = 0.5 * d * h; // Area of one triangle
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    sort(b.begin(), b.end()); // Sort branch heights
    long double total(0);
    for (long p = 0; p < n; p++) {
      total += area; // Add full area of current branch
      if (p > 0 && b[p - 1] + h > b[p]) {
        // If current branch overlaps with the previous one
        long diff = b[p] - b[p - 1]; // Vertical gap between branches
        long double ratio = (1 - diff / h); // Ratio of uncovered triangle
        total -= ratio * ratio * area; // Subtract overlapping area
      }
    }
    printf("%.8Lf\n", total);
  }
}


// https://github.com/VaHiX/CodeForces/