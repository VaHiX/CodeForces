// Problem: CF 1054 B - Appending Mex
// https://codeforces.com/contest/1054/problem/B

#include <cstdio>
// Flowerbox:
// Problem: B. Appending Mex
// Purpose: Determine the minimum step where a mistake was made in constructing an array
//          by repeatedly appending mex of subsets of previously added elements.
// Algorithms/Techniques: Greedy approach with tracking maximum element seen so far.
// Time Complexity: O(n)
// Space Complexity: O(1)
int main() {
  long n;
  scanf("%ld", &n);
  long m(-1);  // Tracks the maximum element seen so far
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    if (a > m + 1) {  // If current element is more than one greater than max seen,
                      // it's impossible to form this value from previous mex operations
      printf("%ld\n", p + 1);  // Return the step number (1-indexed)
      return 0;
    }
    m = (m > a) ? m : a;  // Update maximum element seen so far
  }
  puts("-1");  // No mistake found, array is valid
  return 0;
}

// https://github.com/VaHiX/codeForces/