// Problem: CF 1891 A - Sorting with Twos
// https://codeforces.com/contest/1891/problem/A

/*
 * Problem: Sorting with Twos
 * Algorithm: Check if array can be sorted using operations where we subtract 1 from first 2^m elements.
 * Approach:
 *   - The key idea is to verify if the given array can be made non-decreasing by applying allowed operations.
 *   - For each bit position B (2^B), we check whether the subarray from index B+1 to 2*B-1 is in non-decreasing order.
 *   - If any such subarray violates the order, then it's impossible to sort with given operations.
 *
 * Time Complexity: O(n log n) where n is the size of array per test case (since we iterate over log(n) bits and check up to n elements).
 * Space Complexity: O(n) due to vector storage for the array.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n + 1, 0); // Vector to store input array, indexed from 1
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &v[p]); // Read the elements starting from index 1
    }
    bool res(true);
    for (long B = 1; res && B <= 2 * n; B *= 2) { // Iterate through powers of 2 up to 2*n
      for (long p = B + 1; res && p < 2 * B && p + 1 < v.size(); p++) {
        // Check if adjacent elements in current range are in non-decreasing order
        if (v[p] > v[p + 1]) {
          res = false;
        }
      }
    }
    puts(res ? "YES" : "NO"); // Output result based on whether sorting is possible
  }
}


// https://github.com/VaHiX/codeForces/