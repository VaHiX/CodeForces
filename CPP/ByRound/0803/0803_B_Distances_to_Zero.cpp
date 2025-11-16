// Problem: CF 803 B - Distances to Zero
// https://codeforces.com/contest/803/problem/B

/*
Algorithm: Two-Pass Distance Calculation
Approach:
- First pass (left to right): Compute distances to the nearest zero on the left.
- Second pass (right to left): Compute distances to the nearest zero on the right, 
  and take the minimum of the two passes.
- This ensures that for each element, we get the distance to the nearest zero.

Time Complexity: O(n)
Space Complexity: O(n)
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
  std::vector<long> b(n, n + 1); // Initialize with a large value
  long d = n + 1; // Distance tracker, initialized to a large value
  for (long p = 0; p < n; p++) {
    if (a[p] == 0) {
      d = 0; // If current element is zero, reset distance
    } else {
      ++d; // Otherwise, increment distance
    }
    b[p] = (b[p] < d) ? b[p] : d; // Keep the minimum of current and computed distance
  }
  d = n + 1; // Reset distance tracker for reverse pass
  for (long p = n - 1; p >= 0; p--) {
    if (a[p] == 0) {
      d = 0; // If current element is zero, reset distance
    } else {
      ++d; // Otherwise, increment distance
    }
    b[p] = (b[p] < d) ? b[p] : d; // Keep the minimum of current and computed distance
  }
  for (long p = 0; p < n; p++) {
    printf("%ld ", b[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/