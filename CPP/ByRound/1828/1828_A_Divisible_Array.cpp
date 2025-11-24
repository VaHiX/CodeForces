// Problem: CF 1828 A - Divisible Array
// https://codeforces.com/contest/1828/problem/A

/*
 * Code Purpose: 
 * This code solves the "Divisible Array" problem where for a given integer n,
 * we need to construct an array of length n such that:
 * 1. Each element a[i] is between 1 and 1000.
 * 2. Each element a[i] is divisible by its index i.
 * 3. The sum of all elements is divisible by n.
 * 
 * Algorithm:
 * The approach is to set each element a[i] = 2 * i. This ensures:
 * - a[i] is divisible by i since 2*i is always divisible by i.
 * - Each element is within [1, 1000] as long as n <= 200.
 * - The sum of the array will be 2*(1+2+...+n) = 2 * n * (n+1)/2 = n*(n+1).
 *   Since n*(n+1) is always divisible by n when n > 0, the sum is divisible by n.
 * 
 * Time Complexity: O(n) per test case, as we loop from 1 to n once.
 * Space Complexity: O(1) additional space, not counting the output array.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 1; p <= n; p++) {
      printf("%ld ", 2 * p); // Each element is set to 2*i to satisfy divisibility and sum conditions
    }
    puts(""); // Print newline after each array
  }
}


// https://github.com/VaHiX/CodeForces/