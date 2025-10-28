// Problem: CF 1682 B - AND Sorting
// https://codeforces.com/contest/1682/problem/B

/*
Problem: B. AND Sorting
Algorithm/Technique: Bit manipulation, greedy approach
Time Complexity: O(n) amortized over all test cases
Space Complexity: O(1)

Task: Given a permutation of integers from 0 to n-1 that is not sorted,
find the maximum value X such that we can sort the array by swapping
elements where their bitwise AND equals X.

The idea is to compute the bitwise AND of all pairs (i,j) where p[i] & p[j] > 0.
We only consider elements that are not in their correct positions (p[i] != i),
and check which bits can be set in the final answer by performing operations.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x(0); // Result to store maximum possible X
    bool start(0); // Flag to indicate if we've started processing values
    for (long p = 0; p < n; p++) {
      long y;
      scanf("%ld", &y);
      // Skip elements that are already in correct position
      if (y == p) {
        continue;
      }
      // If this is the first element we're considering, initialize x with it
      if (!start) {
        start = 1;
        x = y;
      }
      // Keep doing bitwise AND of all relevant elements
      x &= y;
    }
    printf("%ld\n", x);
  }
}


// https://github.com/VaHiX/codeForces/