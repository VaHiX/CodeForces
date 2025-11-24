// Problem: CF 1300 A - Non-zero
// https://codeforces.com/contest/1300/problem/A

/*
 * Problem: Make sum and product of array non-zero with minimum steps.
 * Algorithm: Count zeros and check if sum is zero. If both sum and product are zero,
 *            we need to increment elements. The key insight is that if there are zeros,
 *            we will have to make at least one zero non-zero. If the sum of all elements
 *            is zero, we may also need an extra step to break that zero sum.
 *
 * Time Complexity: O(n) per test case, where n is the size of array.
 * Space Complexity: O(1), only using a few variables for counting and computation.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long z(0), s(0); // z: count of zeros, s: sum of elements
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      z += (x == 0); // increment zero counter if current element is zero
      s += x;        // add current element to sum
    }
    long cnt = z + (s + z == 0); // minimum steps needed:
                                 // z steps to fix zeros,
                                 // plus one more if sum + z equals zero (sum was zero)
    printf("%ld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/