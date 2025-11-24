// Problem: CF 1392 A - Omkar and Password
// https://codeforces.com/contest/1392/problem/A

/*
 * Problem: A. Omkar and Password
 * Purpose: Determine the shortest possible length of a password array after applying
 *          operations where adjacent unequal elements are replaced by their sum.
 *
 * Algorithm:
 *   - For each test case, iterate through the array to check if all elements are equal.
 *   - If all elements are equal, the minimum length is n (no operations can be performed).
 *   - Otherwise, we can reduce the array to a single element via a series of operations,
 *     since adjacent unequal elements can always be merged until only one distinct value remains.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev(0);
    bool same(true); // Flag to track if all elements are the same
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      if (prev > 0 && a != prev) { // If current element differs from previous
        same = false;              // Mark that elements are not all the same
      }
      prev = a; // Update previous element
    }
    printf("%ld\n", same ? n : 1); // If all same, return n; else return 1
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/