// Problem: CF 891 B - Gluttony
// https://codeforces.com/contest/891/problem/B

/*
 * Code Purpose: 
 * This code constructs a permutation of the given array such that for every non-empty subset of indices,
 * the sum of elements in the original array and the new permutation differ. 
 * The approach uses a cyclic shift of sorted elements to ensure this property holds.
 * 
 * Algorithm/Techniques:
 * - Sort the array elements along with their original indices.
 * - Perform a cyclic right shift on the sorted values.
 * - Assign the shifted values back to the original positions to form the result array.
 * 
 * Time Complexity: O(n log n) due to sorting.
 * Space Complexity: O(n) for storing the array and auxiliary structures.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::pair<long, long>> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p].first);
    a[p].second = p;
  }
  sort(a.begin(), a.end()); // Sort elements while keeping track of original indices
  std::vector<long> f(n);
  for (long p = 0; p < n; p++) {
    f[a[p].second] = a[(p + 1) % n].first; // Cyclically assign next element to original index
  }
  for (long p = 0; p < n; p++) {
    printf("%ld ", f[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/