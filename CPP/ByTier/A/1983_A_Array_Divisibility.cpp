// Problem: CF 1983 A - Array Divisibility
// https://codeforces.com/contest/1983/problem/A

/*
 * Code Purpose:
 *   This code generates a "beautiful" array of size n, where for every k from 1 to n,
 *   the sum of elements at positions that are multiples of k is divisible by k.
 *   The simple approach is to set each element a[j] = j, which satisfies the condition
 *   because the sum of elements at multiples of k will be a sum of multiples of k,
 *   and hence divisible by k.
 *
 * Algorithm:
 *   For each test case:
 *     - Print integers from 1 to n as the array elements.
 *
 * Time Complexity: O(n) per test case, as we just print numbers from 1 to n.
 * Space Complexity: O(1) extra space, excluding input/output storage.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 1; p <= n; p++) {
      printf("%ld ", p);  // Print each index as the element value
    }
    puts("");  // Print newline after each array
  }
}


// https://github.com/VaHiX/CodeForces/