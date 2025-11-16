// Problem: CF 1650 C - Weight of the System of Nested Segments
// https://codeforces.com/contest/1650/problem/C

/*
Algorithm: 
- The problem asks to find a system of nested segments with minimum total weight.
- Key insight: To minimize the sum of weights of endpoints of n nested segments,
  we need to select 2*n points such that the sum of their weights is minimized.
- Since segments are nested, the leftmost point of the outermost segment must be
  the leftmost among all selected points, and the rightmost point of the outermost
  segment must be the rightmost among all selected points.
- Therefore, to achieve minimum weight: we sort all points by coordinate,
  then take the first 2*n points with the smallest weights.
- The points are assigned to form nested segments such that:
  - The outermost segment uses the first and last of these 2*n points.
  - The inner segments use the next pair of points, and so on.
- Sorting is used to easily pick the 2*n smallest-weight points.
- To output the segments, we sort them by left endpoint and then pair up
  the first with the last, second with second last, etc.

Time Complexity: O(m log m) per test case due to sorting.
Space Complexity: O(m) for storing the points.

*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    // Store points as {weight, {coordinate, index}} to sort by coordinate
    std::vector<std::pair<long, std::pair<long, long>>> v(m);
    for (long p = 0; p < m; p++) {
      scanf("%ld %ld", &v[p].second.first, &v[p].first); // Read coordinate and weight
      v[p].second.second = p + 1; // Store the 1-based index
    }
    // Sort points by coordinate (first element of pair)
    sort(v.begin(), v.end());
    // Store the indices of the first 2*n points with minimal weights
    std::vector<std::pair<long, long>> z(2 * n);
    long long wsum(0); // Total weight of the selected points
    for (long p = 0; p < 2 * n; p++) {
      wsum += v[p].first; // Add the weight of the point
      z[p] = v[p].second; // Store the coordinate and index of point
    }
    printf("%lld\n", wsum);
    // Sort the selected points by coordinate
    sort(z.begin(), z.end());
    // Output the nested segments by pairing first with last, etc.
    for (long p = 0; p < n; p++) {
      printf("%ld %ld\n", z[p].second, z[2 * n - 1 - p].second);
    }
    puts(""); // Print empty line after each test case
  }
}


// https://github.com/VaHiX/CodeForces/