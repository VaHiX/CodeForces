// Problem: CF 1260 B - Obtain Two Zeroes
// https://codeforces.com/contest/1260/problem/B

/*
B. Obtain Two Zeroes
Algorithm: Mathematical analysis of allowed operations.
Time Complexity: O(1) per test case
Space Complexity: O(1)

The allowed operations are:
- (a, b) -> (a - x, b - 2x)
- (a, b) -> (a - 2x, b - x)

We want to determine if we can make both a and b zero.

Key observations:
1. Each operation reduces a by x and b by 2x or vice versa.
2. After k operations, the sum of a and b should be divisible by 3.
   Because each operation removes 3x total units (x from one, 2x from the other).
3. Also, at any point during operations, the values must remain non-negative.
4. If a > 2*b or b > 2*a, it's impossible to reduce both to zero since we cannot
   have negative values.

The condition is:
- (a + b) % 3 == 0 -> sum must be divisible by 3
- a <= 2*b and b <= 2*a -> constraints on ratio of a and b

We use the negation of this condition to check for "NO":
if any of these conditions are true: 
1. (a + b) % 3 != 0
2. a > 2 * b
3. b > 2 * a
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    bool ans = ((a + b) % 3) || (a > 2 * b) || (b > 2 * a); // Check for impossible cases
    puts(ans ? "NO" : "YES"); // Output result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/