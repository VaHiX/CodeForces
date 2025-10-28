// Problem: CF 1982 B - Collatz Conjecture
// https://codeforces.com/contest/1982/problem/B

/*
B. Collatz Conjecture
Algorithm: Simulate the process of incrementing x and reducing by y until k operations are completed,
then adjust using modulo arithmetic for remaining steps.

Time Complexity: O(log_y(x) + k) per test case, where log_y(x) is due to repeated divisions by y.
Space Complexity: O(1), constant extra space used.

The process:
- For each of k steps:
  - Increment x by the minimum of (how much x needs to be increased to reach next multiple of y)
    and remaining k
  - Keep dividing x by y while divisible
- Final result is x + (k % (y - 1)) if no more transformations possible.

Input: number of test cases t, followed by t lines each containing x y k
Output: final value of x after k operations
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y, k;
    scanf("%ld %ld %ld", &x, &y, &k);
    long res(0);
    while (k && x != 1) {
      long long d = (x / y + 1) * y - x; /* Calculate how much to increment x to reach next multiple of y */
      if (!d) {                         /* If already a multiple of y, increment by at least 1 */
        d = 1;
      }
      if (d > k) {                      /* Do not exceed remaining operations */
        d = k;
      }
      x += d;                           /* Increment x */
      while (x % y == 0) {              /* Keep dividing by y while divisible */
        x /= y;
      }
      k -= d;                           /* Decrease number of operations left */
    }
    printf("%ld\n", x + k % (y - 1));   /* Adjust final x with remaining k modulo (y - 1) */
  }
}


// https://github.com/VaHiX/codeForces/