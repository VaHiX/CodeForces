// Problem: CF 1827 A - Counting Orders
// https://codeforces.com/contest/1827/problem/A

/*
 * Problem: Reorder array 'a' such that a[i] > b[i] for all i.
 * Algorithm: Greedy + combinatorics
 * Time Complexity: O(n log n) per test case due to sorting + O(n) for processing = O(n log n)
 * Space Complexity: O(n) for the vectors a and b
 *
 * Approach:
 * - Sort both arrays.
 * - For each element in sorted b, find how many elements in sorted a are greater than it.
 * - The number of valid assignments is the product of such counts modulo 10^9 + 7.
 * - If at any point the count becomes negative, return 0 (no valid permutations).
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long long MOD = 1e9 + 7;
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n), b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    };
    sort(a.begin(), a.end()); // Sort array 'a'
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    };
    sort(b.begin(), b.end()); // Sort array 'b'
    long idx(n - 1);          // Pointer to track largest element in a that is <= current b[p]
    long long res(1);         // Result initialized to 1
    for (long p = n - 1; p >= 0; p--) {
      while (idx >= 0 && a[idx] > b[p]) { // Move back until we find an element in 'a' <= b[p]
        --idx;
      }
      long diff = p - idx;  // Number of valid choices for current position
      if (diff < 0) {       // If there's no valid assignment, set result to 0
        res = 0;
        break;
      }
      res *= diff;          // Multiply result by number of choices
      res %= MOD;           // Apply modulo to prevent overflow
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/