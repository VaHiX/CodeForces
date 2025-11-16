// Problem: CF 1579 B - Shifting Sort
// https://codeforces.com/contest/1579/problem/B

/*
Algorithm: Sorting by Selection with Cyclic Shifts
Approach:
This solution mimics a selection sort algorithm where for each position p from 0 to n-1,
we find the minimum element in the subarray [p, n-1]. If the minimum is not at position p,
we perform operations:
1. Record the shift operation from p to idx (the position of minimum element).
2. Shift elements in the array such that the minimum element moves to position p by
   simulating the left shift operation manually.

Time Complexity: O(n^2) due to nested loops for finding minimum and shifting elements.
Space Complexity: O(n) for storing the vector of operations and the input array.

Techniques:
- Selection sort logic adapted for cyclic shifts
- Simulation of left shift by manual element shifting
- Tracking of operations in a vector for output
*/

#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    std::vector<std::pair<long, long>> w; // Stores the operations
    for (long p = 0; p < n; p++) {
      long idx(p); // index of minimum element in the remaining array
      for (long q = p + 1; q < n; q++) {
        if (v[q] < v[idx]) {
          idx = q;
        }
      }
      if (idx == p) {
        continue; // Already in correct position
      }
      // Record operation: shift from p to idx (left shift by (idx - p) positions)
      w.push_back(std::make_pair(p + 1, idx + 1));
      // Simulate shifting elements to the left (move minimum to position p)
      for (long q = idx; q > p; q--) {
        v[q] = v[q - 1];
      }
    }
    printf("%ld\n", w.size());
    for (long p = 0; p < w.size(); p++) {
      // Print l, r, d where l = w[p].first, r = w[p].second, d = (r - l)
      printf("%ld %ld %ld\n", w[p].first, w[p].second,
             w[p].second - w[p].first);
    }
  }
}


// https://github.com/VaHiX/CodeForces/