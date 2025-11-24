// Problem: CF 1527 A - And Then There Were K
// https://codeforces.com/contest/1527/problem/A

/*
Algorithm: A. And Then There Were K
Techniques: Bit manipulation, binary search approach

Purpose:
This code finds the maximum value of integer k such that the bitwise AND 
of all integers from n down to k equals zero.

Time Complexity: O(log n) per test case
Space Complexity: O(1)

The key insight is that we want to find the largest k such that 
n & (n-1) & ... & k = 0.
This happens when the AND operation "clears" all bits in n,
which occurs when we go down to a number whose binary representation
has the same highest set bit as n but with lower bits cleared,
effectively making the entire sequence of AND operations result in 0.

For example, if n = 5 (binary: 101), 
we can go down to 3 (binary: 011) where 5 & 4 & 3 = 0.
The maximum k is such that we reach a number with all bits cleared,
which happens when k = 2^h - 1 where h is the position of highest set bit in n.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x(1);  // Start with smallest power of 2
    while (2 * x <= n) {  // Find the largest power of 2 <= n
      x *= 2;
    }
    --x;  // Convert to the number with all lower bits set
    printf("%ld\n", x);
  }
}


// https://github.com/VaHiX/codeForces/