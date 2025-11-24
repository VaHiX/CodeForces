// Problem: CF 1523 B - Lord of the Values
// https://codeforces.com/contest/1523/problem/B

/*
 * Purpose: This code solves the problem of transforming an array of even length
 *          from values a_1, a_2, ..., a_n to -a_1, -a_2, ..., -a_n using two types of operations:
 *          1. a_i = a_i + a_j
 *          2. a_j = a_j - a_i
 *          The solution uses a strategy that operates on pairs of elements,
 *          effectively negating each pair through a series of operations.
 *          
 * Algorithm: For each pair of elements at indices p and p+1 (where p is even):
 *            - Add the second to the first (a[p+1] += a[p]) - 2 times
 *            - Subtract the first from the second (a[p+1] -= a[p]) - 2 times
 *            This sequence effectively negates both elements.
 *            
 * Time Complexity: O(n^2) in worst case due to nested loops, but since n <= 1000,
 *                  and the number of operations is 3*n, which is well under 5000,
 *                  it's acceptable.
 * Space Complexity: O(1) - constant extra space used, no additional data structures.
 */
#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    // Read input values (but do not store them, as they are not needed for the algorithm)
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
    }
    // Output total number of operations
    printf("%ld\n", 3 * n);
    // Process pairs of elements
    for (long p = 0; p < n; p += 2) {
      long u(p + 1), v(p + 2);  // u = first element of pair, v = second
      // Operation 1: Add second to first
      printf("1 %ld %ld\n", u, v);
      printf("1 %ld %ld\n", u, v);
      // Operation 2: Subtract first from second
      printf("2 %ld %ld\n", u, v);
      // Operation 1: Add second to first again
      printf("1 %ld %ld\n", u, v);
      printf("1 %ld %ld\n", u, v);
      // Operation 2: Subtract first from second again
      printf("2 %ld %ld\n", u, v);
    }
  }
}


// https://github.com/VaHiX/CodeForces/