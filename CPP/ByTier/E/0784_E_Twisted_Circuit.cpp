// Problem: CF 784 E - Twisted Circuit
// https://codeforces.com/contest/784/problem/E

#include <cstdio>
int main() {
  int a, b, c, d;
  scanf("%d %d %d %d", &a, &b, &c, &d);
  printf("%d", ((a ^ b) & (c | d) ^ ((b & c) | (a ^ d)))); // Evaluate twisted circuit logic
  return 0;
}
/*
E. Twisted Circuit

This code evaluates a complex boolean expression involving four binary inputs (a, b, c, d).
The expression is: ((a XOR b) AND (c OR d)) XOR ((b AND c) OR (a XOR d))

Algorithms/Techniques:
- Bitwise operations (XOR, AND, OR)
- Boolean algebra evaluation
- Single pass computation

Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - only using a fixed number of integer variables
*/

// https://github.com/VaHiX/codeForces/