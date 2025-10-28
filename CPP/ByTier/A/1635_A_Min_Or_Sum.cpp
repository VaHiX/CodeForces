// Problem: CF 1635 A - Min Or Sum
// https://codeforces.com/contest/1635/problem/A

/*
 * Problem: Min Or Sum
 * Description: Given an array of non-negative integers, we can perform operations
 *              where we choose two elements, replace them with new values such that
 *              their bitwise OR remains the same. The goal is to minimize the sum
 *              of the array after any number of operations.
 *
 * Algorithm: The key insight is that we want to reduce as many bits as possible,
 *            especially higher-order bits. Since we can set a number to 0 without
 *            violating the OR constraint (if another element has that bit set),
 *            we attempt to zero out elements that have bits that can be covered
 *            by other elements. However, if any bit is present in at least one
 *            number in the array, it must remain somewhere in the result.
 *
 *            The optimal strategy:
 *              - For each bit position, check if it's set in at least one element.
 *              - If it is, this bit contributes to the final OR value.
 *              - The answer is simply the bitwise OR of all elements because
 *                the minimum possible result occurs when we can reduce every number
 *                to 0 except those whose bits are necessary to maintain the OR.
 *
 * Time Complexity: O(n) per test case — we iterate through n numbers once.
 * Space Complexity: O(1) — only using constant extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long res(0); // Initialize result as 0
    while (n--) {
      long x;
      scanf("%ld", &x);
      res |= x; // Perform bitwise OR of all elements
    }
    printf("%ld\n", res); // Output the final OR value
  }
}


// https://github.com/VaHiX/codeForces/