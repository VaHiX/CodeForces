// Problem: CF 1685 A - Circular Local MiniMax
// https://codeforces.com/contest/1685/problem/A

/*
 * Problem: Circular Local MiniMax
 * Algorithm: Rearranging array elements in a circle such that each element is either strictly greater than both neighbors or strictly smaller than both neighbors.
 *
 * Time Complexity: O(n log n) per test case due to sorting; overall O(t * n * log n)
 * Space Complexity: O(n) for storing vectors
 *
 * Approach:
 * 1. If n is odd, impossible to satisfy the condition (each element must have two neighbors forming a "local extremum").
 * 2. Sort the array.
 * 3. Rearrange elements in a specific pattern to ensure no three consecutive elements form an increasing or decreasing sequence.
 *    This is done by placing elements alternately at positions that avoid local minima/maxima violations.
 * 4. Validate final arrangement by checking each element against its neighbors in circular manner.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    if (n % 2) { // If odd number of elements, impossible to satisfy the condition
      puts("NO");
      continue;
    }
    sort(a.begin(), a.end()); // Sort to prepare for arrangement
    std::vector<long> b(n);
    // Place sorted elements in a specific order to avoid invalid local extrema
    for (long p = 0; p < n; p++) {
      long idx = (2 * p + (2 * p >= n)) % n; // Compute index based on pattern to alternate placement
      b[idx] = a[p];
    }
    bool possible(true);
    // Ensure the arrangement satisfies the required condition for all elements
    for (long p = 0; possible && p < n; p++) {
      long prev = (p - 1 + n) % n; // Previous element in circular fashion
      long next = (p + 1 + n) % n; // Next element in circular fashion
      // Check if current element is neither local min nor max (violates the condition)
      if (b[prev] <= b[p] && b[p] <= b[next]) {
        possible = false;
      }
      if (b[prev] >= b[p] && b[p] >= b[next]) {
        possible = false;
      }
    }
    if (!possible) {
      puts("NO");
    } else {
      puts("YES");
      for (long p = 0; p < n; p++) {
        printf("%ld ", b[p]);
      }
      puts("");
    }
  }
}


// https://github.com/VaHiX/codeForces/