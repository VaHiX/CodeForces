// Problem: CF 2009 A - Minimize!
// https://codeforces.com/contest/2009/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    printf("%ld\n", b - a);
  }
}
/*
Flowerbox:
Problem: Minimize expression (c-a)+(b-c) for given a and b where a ≤ c ≤ b
Algorithm: Mathematical simplification
- Expression (c-a)+(b-c) = c - a + b - c = b - a
- Since c cancels out, the result is always b - a regardless of c's value
- Time Complexity: O(1) - constant time operations
- Space Complexity: O(1) - only using fixed amount of variables

Techniques:
- Mathematical optimization to simplify expression
- Direct computation after algebraic manipulation
*/

// https://github.com/VaHiX/codeForces/