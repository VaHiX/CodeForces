// Problem: CF 1421 A - XORwice
// https://codeforces.com/contest/1421/problem/A

/*
Problem: A. XORwice
Purpose: Given two integers a and b, find the minimum value of (a ⊕ x) + (b ⊕ x) for any integer x.
Algorithms/Techniques: Bit manipulation, greedy approach
Time Complexity: O(1) per test case
Space Complexity: O(1)

The key insight is to observe that for each bit position, we can choose x such that:
- If both a and b have the same bit at position i, then we can set x[i] = 0 to minimize contribution (0 + 0 = 0)
- If a and b differ in bit i, we must set x[i] = 1 to make one of them zero XOR result for minimizing total sum.

Therefore, the minimum is achieved when x is chosen such that it flips exactly those bits where a and b differ.
In the optimal case: (a ⊕ x) + (b ⊕ x) == (a ⊕ b).

So we simply return a ^ b for each test case.
*/

#include <cstdio>
int main() {
  long t; // number of test cases
  scanf("%ld", &t);
  while (t--) {
    long a, b; // input integers
    scanf("%ld %ld", &a, &b);
    printf("%ld\n", a ^ b); // output XOR result, which is the minimum value
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/