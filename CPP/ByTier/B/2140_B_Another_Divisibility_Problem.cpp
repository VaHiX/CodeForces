// Problem: CF 2140 B - Another Divisibility Problem
// https://codeforces.com/contest/2140/problem/B

/*
B. Another Divisibility Problem
Algorithms/Techniques: Bitwise left shift operation to multiply by 8, pattern-based solution
Time Complexity: O(T) where T is the number of test cases
Space Complexity: O(1)

The problem asks to find a positive integer y < 10^9 such that concatenation of x and y (x#y)
is divisible by x + y. A key observation is that choosing y = 10^(digits_in_x) - 1 works for most cases.
However, the simple approach here uses bit shift: a << 3 is equivalent to a * 8,
which can be part of a general pattern where y = 10^k - 1 or similar derived values.

Input:
- Number of test cases T
- For each test case, read integer x (1 <= x < 10^8)

Output:
- For each test case, print an integer y such that (x#y) % (x+y) == 0
*/

#include <stdio.h>
int main() {
  int T, a;
  scanf("%d", &T); // Read number of test cases
  while (T--) {
    scanf("%d", &a); // Read the value x
    printf("%d\n", a << 3); // Output a * 8 (simplified heuristic for y)
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/