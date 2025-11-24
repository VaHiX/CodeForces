// Problem: CF 1433 A - Boring Apartments
// https://codeforces.com/contest/1433/problem/A

/*
 * Problem: A. Boring Apartments
 * Purpose: Calculate the total number of digits pressed when calling boring apartments
 *          in a specific order until the target apartment is reached.
 *
 * Algorithm:
 * - For each test case, given a boring apartment number x (all digits same),
 *   determine how many digits were pressed in sequence:
 *   - All apartments with digit 1 (1, 11, 111, 1111) -> 1 + 2 + 3 + 4 = 10 digits
 *   - Then all apartments with digit 2 (2, 22, 222, 2222) -> 1 + 2 + 3 + 4 = 10 digits
 *   - And so on.
 * - For a number x consisting of digit d:
 *   - Count how many digits it has: len = floor(log10(x)) + 1
 *   - Add contributions from previous digits (1 to d-1) -> each contributes (1+2+3+4)*10 = 100
 *   - Add contribution of current digit's sequence up to x:
 *     - Each digit position 1,2,3,4 contributes (1,2,3,4) digits respectively
 *   - The formula used:
 *     ans = 10 * (d - 1) + (x / 1 > 0) + 2 * (x / 10 > 0) + 3 * (x / 100 > 0) + 4 * (x / 1000 > 0)
 *     where:
 *       - 10 * (d - 1): total digits from all previous digits
 *       - (x / 1 > 0): add one for last digit of current group
 *       - 2 * (x / 10 > 0): add two if it has tens place
 *       - 3 * (x / 100 > 0): add three if it has hundreds place
 *       - 4 * (x / 1000 > 0): add four if it has thousands place
 *
 * Time Complexity: O(1) per test case.
 * Space Complexity: O(1).
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    // Compute the total number of keypresses needed to reach apartment x
    long ans = 10 * ((x % 10) - 1) + (x / 1 > 0) + 2 * (x / 10 > 0) +
               3 * (x / 100 > 0) + 4 * (x / 1000 > 0);
    printf("%ld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/