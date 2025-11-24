// Problem: CF 1591 B - Array Eversion
// https://codeforces.com/contest/1591/problem/B

/*
B. Array Eversion
Algorithm: The problem simulates a process where we repeatedly partition an array into two parts based on the last element, and then concatenate them back in order. We count how many iterations are needed until the array no longer changes.

Time Complexity: O(n) per test case, since each element is processed at most once in the loop.
Space Complexity: O(n) for storing the vector of size n.

Techniques:
- Stable partitioning based on a pivot (last element)
- Tracking the number of operations until convergence
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
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]); // Read array elements
    }
    long cnt(0), last(v.back()); // Initialize counter and last element as the final element
    for (long p = n - 1; p >= 0; p--) { // Traverse from the end to the beginning
      if (v[p] <= last) {
        continue; // If current element is not greater than last, skip it
      }
      ++cnt; // Increment operation count if element is greater than last
      last = v[p]; // Update last to current element as new pivot
    }
    printf("%ld\n", cnt); // Output the number of operations
  }
}


// https://github.com/VaHiX/codeForces/