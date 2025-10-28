// Problem: CF 1550 A - Find The Array
// https://codeforces.com/contest/1550/problem/A

/*
 * Problem: Find the minimum possible size of a beautiful array with sum equal to s.
 *
 * A beautiful array satisfies:
 * - For each element ai, either ai = 1, or at least one of (ai - 1) or (ai - 2) exists in the array.
 *
 * Algorithm:
 * - Start with the largest possible element sqrt(s), then increment until n*n >= s.
 * - This approach is based on observing that we can construct a beautiful array
 *   by taking squares to minimize total count while maintaining sum s.
 *
 * Time Complexity: O(1) per test case, since we perform a constant number of operations.
 * Space Complexity: O(1), only using a few variables.
 */

#include <cmath>
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long s;
    scanf("%ld", &s);
    long n = sqrt(s);
    while (n * n < s) {  // Ensure n*n >= s by incrementing n
      ++n;
    }
    printf("%ld\n", n);
  }
}


// https://github.com/VaHiX/codeForces/