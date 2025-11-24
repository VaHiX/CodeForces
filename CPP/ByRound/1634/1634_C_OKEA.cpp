// Problem: CF 1634 C - OKEA
// https://codeforces.com/contest/1634/problem/C

/*
C. OKEA
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
People worry that computers will get too smart and take over the world, but the real problem is that they're too stupid and they've already taken over the world.
— Pedro Domingos

Algorithm/Techniques: 
The problem asks us to arrange numbers from 1 to n*k in a grid of n rows and k columns such that 
for every row, the average of any consecutive subarray is an integer. This means for any contiguous 
subset of items on a shelf, their sum must be divisible by the number of items in that subset.

Key insight:
- For the average to always be an integer, the sum of any contiguous subsequence in each row must 
  be divisible by the length of that subsequence.
- This condition is satisfied if and only if we can arrange numbers such that each row is 
  arithmetic progression with a common difference that ensures divisibility.

Time Complexity: O(n * k)
Space Complexity: O(n * k)

This solution works for most cases, except when n is odd and k > 1. In such cases,
it's impossible to arrange the numbers to satisfy the constraint. This is due to 
the parity property of arithmetic means in a sequence.

The approach:
- If n is odd and k > 1, then the arrangement is not possible (output "NO").
- Otherwise, we simply generate numbers sequentially row-wise with increasing column indices.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    // If n is odd and k > 1, it's impossible to satisfy the constraint
    if ((n % 2) && (k > 1)) {
      puts("NO");
      continue;
    }
    puts("YES");
    // Generate numbers row-wise using formula u + n * p
    for (long u = 1; u <= n; u++) {
      for (long p = 0; p < k; p++) {
        printf("%ld ", u + n * p);
      }
      puts("");
    }
  }
}


// https://github.com/VaHiX/codeForces/