// Problem: CF 1283 A - Minutes Before the New Year
// https://codeforces.com/contest/1283/problem/A

/*
 * Problem: A. Minutes Before the New Year
 * Algorithms/Techniques: Simple arithmetic calculation
 *
 * Time Complexity: O(t), where t is the number of test cases
 * Space Complexity: O(1)
 *
 * Description:
 * Given the current time in 24-hour format (h hours and m minutes),
 * calculate how many minutes remain until the next midnight (00:00).
 * The solution uses the formula: (24 - h) * 60 - m
 * This computes the remaining minutes from the current hour to midnight,
 * minus the current minute offset.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);  // Read number of test cases
  while (t--) {
    long h, m;
    scanf("%ld %ld", &h, &m);  // Read current hour and minute
    long ans = (24 - h) * 60 - m;  // Calculate minutes until midnight
    printf("%ld\n", ans);  // Print result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/