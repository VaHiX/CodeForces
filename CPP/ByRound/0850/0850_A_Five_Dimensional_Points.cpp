// Problem: CF 850 A - Five Dimensional Points
// https://codeforces.com/contest/850/problem/A

/*
 * Problem: Find good points in 5-dimensional space based on acute angles.
 *
 * Algorithm:
 * - For each point, check all combinations of pairs of other points.
 * - Compute the dot product of vectors from the current point to each pair.
 * - If any dot product is positive (acute angle), the point is bad.
 * - A point is good if no acute angles are formed.
 *
 * Time Complexity: O(n^3), where n is the number of points.
 * Space Complexity: O(n * D), where D = 5 is the dimensionality.
 */

#include <cstdio>
#include <vector>
int main() {
  const int D = 5;  // Number of dimensions
  long n;
  scanf("%ld", &n);
  std::vector<std::vector<long>> a(n, std::vector<long>(D, 0));  // Store points
  if (n > 11) {
    puts("0");  // Early exit for large n since it's guaranteed to have no good points
  } else {
    std::vector<long> ans;  // Store indices of good points
    for (long p = 0; p < n; p++) {
      for (long q = 0; q < D; q++) {
        scanf("%ld", &a[p][q]);  // Read coordinates of point p
      }
    }
    for (long p = 0; p < n; p++) {
      bool good(true);  // Assume point p is good initially
      for (long q = 0; q < n; q++) {
        if (q == p) {
          continue;  // Skip self comparison
        }
        for (int r = 0; r < n; r++) {
          if (r == p || r == q) {
            continue;  // Skip if r equals p or q
          }
          int sum(0);  // Dot product of vectors
          for (int t = 0; t < 5; t++) {
            sum += (a[q][t] - a[p][t]) * (a[r][t] - a[p][t]);  // Compute dot product
          }
          if (sum > 0) {
            good = false;  // Found an acute angle, so point p is bad
          }
        }
      }
      if (good) {
        ans.push_back(p + 1);  // Point p is good (1-indexed)
      }
    }
    printf("%ld\n", ans.size());
    for (long p = 0; p < ans.size(); p++) {
      printf("%ld\n", ans[p]);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/