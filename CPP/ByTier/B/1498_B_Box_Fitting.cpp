// Problem: CF 1498 B - Box Fitting
// https://codeforces.com/contest/1498/problem/B

/*
B. Box Fitting
Algorithm: Greedy approach with bit manipulation
Time Complexity: O(n * log(W)) per test case, where n is the number of rectangles and W is the box width
Space Complexity: O(W) for the vector v storing available space per row

This solution uses a greedy strategy to pack rectangles into rows. It processes
rectangles in descending order of their widths (powers of 2). For each width,
it tries to place as many rectangles of that width as possible in existing rows,
and if needed, creates a new row. The key idea is to use bit operations and
greedily assign rectangles to minimize height.
*/

#include <cstdio>
#include <map>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, w;
    scanf("%ld %ld", &n, &w);
    std::map<long, long> rem; // Map to count frequency of each rectangle width
    long res(0); // Resulting minimum height
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++rem[x]; // Count occurrences of each width
    }
    std::vector<long> v(1e5 + 7, w); // Vector to represent remaining capacity in each row (initially full)
    for (long p = 30; p >= 0; p--) { // Process all possible powers of 2 from highest to lowest
      long cur(1 << p), rod(rem[cur]), idx(0); // cur: current power of 2, rod: number of rectangles of this width
      bool carryon = true;
      for (long idx = 0; carryon && idx < v.size(); idx++) { // Try to place rectangles in existing rows
        long cap = v[idx] / cur; // How many rectangles fit in current row
        if (cap >= rod) {
          cap = rod;
          carryon = false; // No more rectangles of this width to place
        }
        rod -= cap; // Number of rectangles left to place
        v[idx] -= cap * cur; // Update remaining capacity in the row
        res = (res > idx) ? res : idx; // Track maximum row index used
      }
    }
    printf("%ld\n", res + 1); // Add 1 because rows are 0-indexed
  }
}


// https://github.com/VaHiX/codeForces/