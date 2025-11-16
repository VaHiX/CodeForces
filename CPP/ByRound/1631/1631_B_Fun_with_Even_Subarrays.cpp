// Problem: CF 1631 B - Fun with Even Subarrays
// https://codeforces.com/contest/1631/problem/B

/*
 * Problem: B. Fun with Even Subarrays
 * Algorithm: Greedy approach to find minimum operations to make all elements equal.
 * Time Complexity: O(n) amortized over all test cases
 * Space Complexity: O(n)
 *
 * The key idea is to traverse the array from right to left, and for each element,
 * if it's equal to the first element, we move forward. Otherwise, we increment 
 * the operation count and jump to the next power-of-2 position.
 * This greedy method ensures minimal operations by grouping elements strategically.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = n - 1; p >= 0; p--) {
      scanf("%ld", &v[p]); // Fill the vector from right to left
    }
    long idx(1), cnt(0); // Start from index 1, count operations
    while (idx < n) {
      if (v[idx] == v[0]) {
        idx++; // If current element equals first, move forward
      } else {
        ++cnt; // Otherwise, we need an operation
        idx *= 2; // Jump to the next power-of-2 position
      }
    }
    printf("%ld\n", cnt); // Print result for this test case
  }
}


// https://github.com/VaHiX/codeForces/