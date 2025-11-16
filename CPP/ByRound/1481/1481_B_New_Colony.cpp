// Problem: CF 1481 B - New Colony
// https://codeforces.com/contest/1481/problem/B

/*
B. New Colony

Algorithm: Simulation with optimization
Time Complexity: O(n * k) worst case, but optimized with early termination when k > 100*n
Space Complexity: O(n) for storing mountain heights

This problem simulates throwing boulders down a sequence of mountains. Each boulder rolls 
from left to right until it finds a mountain that is not taller than the current one,
where it stops and increases the height of that mountain by 1. If a boulder reaches the
last mountain, it falls into the collection system.

The key optimization is that if k is large (k > 100 * n), it's impossible for all boulders 
to stop at valid positions, so we directly return -1. Otherwise, we simulate each boulder 
throwing step by step.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> h(n + 1, 0); // Vector to store mountain heights, index 0 unused
    for (long p = 0; p < n; p++) {
      scanf("%ld", &h[p]); // Read heights into the vector (0-indexed)
    }
    if (k > 100 * n) { // Early termination for large k values
      puts("-1");
      continue;
    }
    long res(-1); // Result to store position of k-th boulder
    while (k--) {
      long idx(0); // Start index for current boulder's path
      // Roll the boulder until it finds a mountain shorter than current or reaches end
      while (idx < n && h[idx] >= h[idx + 1]) {
        ++idx;
      }
      if (idx >= n) { // If boulder reached the last mountain, it falls
        res = -1;
        break;
      }
      ++h[idx]; // Increase height of the mountain where boulder stops
      res = idx + 1; // Position is 1-indexed
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/