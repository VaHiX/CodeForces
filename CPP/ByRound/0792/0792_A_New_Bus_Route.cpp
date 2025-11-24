// Problem: CF 792 A - New Bus Route
// https://codeforces.com/contest/792/problem/A

/*
 * Purpose: To find the minimum distance between any two cities and count how many such pairs exist.
 * Algorithm: Sort the array of city coordinates, then iterate through adjacent pairs to find the minimum difference.
 *            Count how many times this minimum difference occurs.
 *
 * Time Complexity: O(n log n) due to sorting; the subsequent iteration is O(n).
 * Space Complexity: O(1) if we ignore the space used for input storage, otherwise O(n) for the vector.
 */
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());  // Sort the coordinates to bring closest ones next to each other
  long minDist(2e9), count(0);
  for (long p = 1; p < n; p++) {
    long diff = a[p] - a[p - 1];  // Compute the difference between adjacent elements
    if (diff == minDist) {
      ++count;  // Increment count if difference equals current minimum
    } else if (diff < minDist) {
      minDist = diff;  // Update minimum distance
      count = 1;       // Reset count as we found a new smaller distance
    }
  }
  printf("%ld %ld\n", minDist, count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/