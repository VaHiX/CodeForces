// Problem: CF 1017 C - The Phone Number
// https://codeforces.com/contest/1017/problem/C

#include <cstdio>
// Flowerbox:
// Problem: C. The Phone Number
// Purpose: Generate a permutation of numbers from 1 to n that minimizes the sum of 
//          the lengths of the Longest Increasing Subsequence (LIS) and the Longest 
//          Decreasing Subsequence (LDS).
// Algorithm: 
//   - First compute the square root of n, denoted as t. This value helps in grouping numbers
//     into segments that will form the required permutation.
//   - Then, greedily assign values to output by processing from n down to 1,
//     placing elements in chunks based on the computed t value to balance LIS and LDS lengths.
// Time Complexity: O(n) - Each element is processed a constant number of times.
// Space Complexity: O(1) - Only a few variables are used, independent of input size.
int main() {
  long n;
  scanf("%ld", &n);
  long t(0);
  while (t * t < n) { // Find the smallest integer t such that t^2 >= n
    ++t;
  }
  while (n) {
    long x = ((n - 1) / t) * t; // Compute the start of the current chunk
    for (long p = x + 1; p <= n; p++) { // Print numbers in reverse order within chunk
      printf("%ld ", p);
    }
    n = x; // Move to the next chunk
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/