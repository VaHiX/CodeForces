// Problem: CF 1262 B - Box
// https://codeforces.com/contest/1262/problem/B

/*
B. Box

Purpose:
This code solves the problem of reconstructing a permutation from its prefix maximums array.
The algorithm works by:
1. Checking if the input is valid (each element of q must be >= its index)
2. For each position, if the current maximum is greater than the previous one,
   we place that value at the current position and mark it as unavailable
3. We then fill in remaining positions with unused numbers in order

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing arrays and vectors

Algorithms/Techniques:
- Greedy algorithm
- Prefix maximum tracking
- Set of available numbers management

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n + 1), b(n + 1, 0); // a stores input q array, b stores result permutation
    std::vector<bool> avail(n + 1, 1);      // tracks which numbers are still available
    bool possible(true);
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &a[p]);
      if (a[p] < p) {                        // if q[p] is less than p, impossible to construct
        possible = false;
      }
      if (a[p] > a[p - 1]) {                 // if current max is greater than previous
        b[p] = a[p];                         // place that value at position p
        avail[a[p]] = 0;                     // mark that number as used
      }
    }
    if (possible) {
      std::vector<long> d;                   // collect unused numbers
      for (long p = 1; p <= n; p++) {
        if (avail[p]) {
          d.push_back(p);
        }
      }
      long idx(0);
      for (long p = 1; p <= n; p++) {
        if (b[p] > 0) {
          continue;                          // skip already filled positions
        }
        b[p] = d[idx++];                     // fill remaining positions with unused numbers
      }
      for (long p = 1; p <= n; p++) {
        printf("%ld ", b[p]);
      }
      puts("");
    } else {
      puts("-1");
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/