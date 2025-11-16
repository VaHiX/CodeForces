// Problem: CF 950 A - Left-handers, Right-handers and Ambidexters
// https://codeforces.com/contest/950/problem/A

/*
 * Problem: Forming a team with equal left and right hand players
 * Algorithm: Greedily assign ambidexters to balance the sides
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only using a few variables
 *
 * The approach is to determine the maximum number of players that can be
 * assigned such that exactly half use left hand and half use right hand.
 * Ambidexters can be assigned to either side, so we use them to balance
 * the difference between left and right handers.
 */

#include <cstdio>
int main() {
  long l, r, a;
  scanf("%ld %ld %ld", &l, &r, &a);
  long res(0);
  if (l + a <= r) {
    // All left-handers and ambidexters can be assigned to left side
    // and still have enough right-handers
    res = 2 * (l + a);
  } else if (l <= r) {
    // Left-handers are fewer (or equal) than right-handers
    // Use ambidexters to balance the excess right-handers
    // Remaining ambidexters after balancing are split between sides
    res = 2 * r + 2 * ((a - (r - l)) / 2);
  } else if (r + a <= l) {
    // All right-handers and ambidexters can be assigned to right side
    // and still have enough left-handers
    res = 2 * (r + a);
  } else if (r <= l) {
    // Right-handers are fewer (or equal) than left-handers
    // Use ambidexters to balance the excess left-handers
    // Remaining ambidexters after balancing are split between sides
    res = 2 * l + 2 * ((a - (l - r)) / 2);
  }
  printf("%ld\n", res);
  return 0;
}


// https://github.com/VaHiX/CodeForces/