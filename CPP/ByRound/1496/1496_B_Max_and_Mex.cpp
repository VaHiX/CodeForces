// Problem: CF 1496 B - Max and Mex
// https://codeforces.com/contest/1496/problem/B

/*
B. Max and Mex
Algorithms/Techniques: Set usage for maintaining distinct elements, simulation with mex calculation, ceiling of average computation.

Time Complexity: O(n * log n + k * n) where n is the size of the initial multiset. The log factor comes from set operations. In worst case, we may traverse up to n elements in the mex search.
Space Complexity: O(n) for storing elements in the set.

The problem simulates adding a new element to a multiset based on mex and max values,
and finally returns the count of distinct elements after k such operations.
*/

#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long max(0), mex(0);
    std::set<long> s;
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s.insert(x); // Insert element into set
      max = (max > x) ? max : x; // Track maximum element
    }
    if (max == n - 1) {
      printf("%ld\n", n + k); // Special case: mex is n, so all additions are unique and increase size by k
      continue;
    }
    for (long p = 0; p < 1e9 + 7; p++) {
      if (!s.count(p)) { // Find mex by iterating from 0 until first missing number
        mex = p;
        break;
      }
    }
    long u = (max + mex + 1) / 2; // Compute the ceiling of average of max and mex
    long add = (k > 0) * (1 - s.count(u)); // If we still need to add, check if u is not already in set
    printf("%ld\n", s.size() + add); // Output final count of distinct elements
  }
}


// https://github.com/VaHiX/codeForces/