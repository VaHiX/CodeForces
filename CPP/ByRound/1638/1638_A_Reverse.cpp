// Problem: CF 1638 A - Reverse
// https://codeforces.com/contest/1638/problem/A

/*
 * Problem: Lexicographically smallest permutation after one reverse operation
 * Algorithm: Greedy approach to find the optimal subsegment to reverse
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the permutation
 *
 * The approach:
 * 1. Find the first position where p[i] != i (leftmost mismatch)
 * 2. From that point, find the rightmost position where we encounter the leftmost mismatch value
 * 3. Reverse the segment between these positions
 * 4. This guarantees lexicographically smallest result
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n + 1); // 1-indexed array
    long start(-1), stop(-1);
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &a[p]);
      if (start < 0 && p != a[p]) { // Find first position where value doesn't match index
        start = p;
      } else if (a[p] == start) { // Once found, look for the matching value from right
        stop = p;
      }
    }
    // Reverse the segment from start to stop
    for (long p = 0; start > 0 && 2 * p <= stop - start; p++) {
      long tmp = a[start + p];
      a[start + p] = a[stop - p];
      a[stop - p] = tmp;
    }
    // Output the result
    for (long p = 1; p <= n; p++) {
      printf("%ld ", a[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/