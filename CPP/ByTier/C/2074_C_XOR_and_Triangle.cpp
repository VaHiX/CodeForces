// Problem: CF 2074 C - XOR and Triangle
// https://codeforces.com/contest/2074/problem/C

/*
C. XOR and Triangle
Algorithm: For each x, we try to find a valid y < x such that x, y, and x XOR y can form a non-degenerate triangle.
The key insight is to compute y = (x & -x) | (~x & -~x) which finds a candidate y efficiently.

Time Complexity: O(1) per test case
Space Complexity: O(1)

The algorithm uses bit manipulation to find a specific value of y that satisfies the condition.
It checks triangle inequality constraints implicitly by selecting a y such that the resulting triangle is valid.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    // Compute candidate y using bit operations
    long y = (x & -x) | (~x & -~x);
    // If computed y is less than x, output it; otherwise output -1
    printf("%ld\n", (y < x ? y : -1));
  }
}


// https://github.com/VaHiX/codeForces/