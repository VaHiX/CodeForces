// Problem: CF 888 A - Local Extrema
// https://codeforces.com/contest/888/problem/A

/*
 * Code Purpose: This program counts the number of local extrema (local minima and maxima)
 *               in a given array. A local extremum is an element that is either strictly
 *               greater than both of its neighbors (local maximum) or strictly less than
 *               both of its neighbors (local minimum). Elements at the boundaries are
 *               excluded from consideration.
 *
 * Algorithms/Techniques: Linear scan through the array with simple comparisons.
 *
 * Time Complexity: O(n), where n is the number of elements in the array.
 * Space Complexity: O(n), due to the storage of the array elements.
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  long count(0);
  for (long p = 1; p < n - 1; p++) {
    // Check if current element is a local minimum
    if (a[p - 1] > a[p] && a[p] < a[p + 1]) {
      ++count;
    }
    // Check if current element is a local maximum
    if (a[p - 1] < a[p] && a[p] > a[p + 1]) {
      ++count;
    }
  }
  printf("%ld\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/