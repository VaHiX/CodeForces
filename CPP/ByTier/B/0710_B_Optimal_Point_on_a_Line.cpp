// Problem: CF 710 B - Optimal Point on a Line
// https://codeforces.com/contest/710/problem/B

#include <algorithm>
#include <cstdio>
#include <vector>
// ==================================================================
// Problem: B. Optimal Point on a Line
// Purpose: Find the point on a line that minimizes the sum of distances to given points
// Algorithm: Sorting + Median selection
// Time Complexity: O(n log n) due to sorting
// Space Complexity: O(n) for storing the points
// ==================================================================
int main() {
  long n;
  scanf("%ld\n", &n);
  std::vector<long> a(n, 0);  // Create vector to store points
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);  // Read each point coordinate
  }
  sort(a.begin(), a.end());  // Sort points in ascending order
  printf("%ld\n", a[(n - 1) / 2]);  // Print median (optimal point)
  return 0;
}

// https://github.com/VaHiX/codeForces/