// Problem: CF 840 A - Leha and Function
// https://codeforces.com/contest/840/problem/A

/*
 * Problem: Leha and Function
 * 
 * Purpose: Rearrange elements of array A such that the sum of A'[i] * B[i] is maximized,
 *          where A' is a permutation of A and B is given.
 * 
 * Algorithm:
 *   - Sort array A in descending order to get the largest values first.
 *   - Sort array B in ascending order to align smaller B values with larger A values.
 *   - Assign the sorted A values to the positions in F based on the original indices of B.
 * 
 * Time Complexity: O(n log n) due to sorting operations.
 * Space Complexity: O(n) for storing vectors and pairs.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<std::pair<long, long>> b(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &b[p].first);
    b[p].second = p;  // Store original index
  }
  sort(a.rbegin(), a.rend());  // Sort A in descending order
  sort(b.begin(), b.end());    // Sort B in ascending order
  std::vector<long> f(n);
  for (long p = 0; p < n; p++) {
    f[b[p].second] = a[p];  // Assign A[p] to position of B's sorted index
  }
  for (long p = 0; p < n; p++) {
    printf("%ld ", f[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/