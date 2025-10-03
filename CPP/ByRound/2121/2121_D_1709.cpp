// Problem: CF 2121 D - 1709
// https://codeforces.com/contest/2121/problem/D

#include <cstdio>
#include <vector>
#include <utility>

/*
 * Problem: D. 1709
 * Purpose: Sort two arrays `a` and `b` such that:
 *   1. Both arrays are strictly increasing (a[i] < a[i+1], b[i] < b[i+1])
 *   2. For each index i, a[i] < b[i]
 * 
 * Approach:
 * - First, we sort array `a` using adjacent swaps (type 1).
 * - Then, we sort array `b` using adjacent swaps (type 2).
 * - Finally, we ensure that a[i] < b[i] for all i by swapping elements between arrays (type 3).
 *
 * Time Complexity: O(n^3) in worst case due to bubble-sort-like operations.
 * Space Complexity: O(n^2) for storing the sequence of operations.
 */

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long &x : a) {
      scanf("%ld", &x);
    }
    std::vector<long> b(n);
    for (long &x : b) {
      scanf("%ld", &x);
    }
    std::vector<std::pair<long, long>> w;
    
    // Sort array 'a' using adjacent swaps
    for (long p = 0; p < n; p++) {
      for (long q = 0; q < n - 1; q++) {
        if (a[q] <= a[q + 1]) {
          continue;
        }
        std::swap(a[q], a[q + 1]);
        w.push_back({1, q + 1}); // operation type 1: swap a[q] and a[q+1]
      }
    }

    // Sort array 'b' using adjacent swaps
    for (long p = 0; p < n; p++) {
      for (long q = 0; q < n - 1; q++) {
        if (b[q] <= b[q + 1]) {
          continue;
        }
        std::swap(b[q], b[q + 1]);
        w.push_back({2, q + 1}); // operation type 2: swap b[q] and b[q+1]
      }
    }

    // Ensure a[i] < b[i] for all i by swapping elements between arrays
    for (long p = 0; p < n; p++) {
      if (a[p] <= b[p]) {
        continue;
      }
      std::swap(a[p], b[p]);
      w.push_back({3, p + 1}); // operation type 3: swap a[p] and b[p]
    }
    
    printf("%ld\n", w.size());
    for (std::pair<long, long> &z : w) {
      printf("%ld %ld\n", z.first, z.second);
    }
  }
}

// https://github.com/VaHiX/codeForces/