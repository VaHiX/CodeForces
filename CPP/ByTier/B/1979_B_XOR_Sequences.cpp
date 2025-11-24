// Problem: CF 1979 B - XOR Sequences
// https://codeforces.com/contest/1979/problem/B

/*
B. XOR Sequences
Algorithm: For each pair of distinct non-negative integers x and y, we compute the longest common subsegment 
           between two infinite sequences defined as:
             a[n] = n ^ x
             b[n] = n ^ y
           
           The key insight is that the difference between consecutive elements in each sequence follows a pattern.
           When we compute z = x ^ y, the number of trailing zeros in the binary representation of z gives us 
           the maximum length of a common subsegment.

           Time Complexity: O(1) per test case
           Space Complexity: O(1)

           Techniques:
             - Bitwise XOR operations
             - Trailing zero count in binary representation
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    long z = x ^ y;       // Compute XOR of x and y to find pattern
    long res(1);          // Initialize result to 1 (minimum possible length)
    while (z % 2 == 0) {  // While z is even (has trailing zeros)
      res *= 2;           // Multiply result by 2 for each trailing zero
      z /= 2;             // Remove one trailing zero from z
    }
    printf("%ld\n", res); // Output the maximum length of common subsegment
  }
}


// https://github.com/VaHiX/codeForces/