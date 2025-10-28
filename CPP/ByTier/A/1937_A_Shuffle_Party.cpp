// Problem: CF 1937 A - Shuffle Party
// https://codeforces.com/contest/1937/problem/A

/*
 * Problem: A. Shuffle Party
 * Purpose: Find the final position of element 1 after applying a series of swap operations
 *          on an array initialized as [1, 2, ..., n]. Each swap(k) swaps elements at positions
 *          d (largest proper divisor of k) and k.
 *
 * Algorithm:
 *   - For each k from 2 to n, find the largest proper divisor d of k
 *   - Swap a[d] and a[k]
 *   - Track where element 1 ends up
 *
 * Key Observation:
 *   - After all operations, 1 will end up at position 2^floor(log2(n))
 *   - This is because 1 gets moved by swaps involving powers of 2
 *
 * Time Complexity: O(1) per test case (we just compute 2^floor(log2(n)))
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x(1);  // Start with x = 1
    while (2 * x <= n) {  // Keep doubling x as long as 2*x doesn't exceed n
      x *= 2;  // Multiply x by 2 to get the largest power of 2 <= n
    }
    printf("%ld\n", x);  // Output the result (largest power of 2 <= n)
  }
}


// https://github.com/VaHiX/codeForces/