// Problem: CF 1735 A - Working Week
// https://codeforces.com/contest/1735/problem/A

/*
 * Problem: A. Working Week
 * Purpose: Given n days in a week where day n is followed by day 1,
 *          and 3 of them are days off (one is fixed as day n),
 *          choose the other two days off to maximize the minimum
 *          difference between lengths of the three working segments.
 * Algorithm: Mathematical optimization.
 * Time Complexity: O(1) per test case.
 * Space Complexity: O(1).
 */

#include <stdio.h>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    // Formula derived from mathematical analysis of optimal day selection
    // to maximize the minimum difference between working segments.
    printf("%ld\n", (n - 6) / 3);
  }
}


// https://github.com/VaHiX/codeForces/