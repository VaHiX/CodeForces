// Problem: CF 916 A - Jamie and Alarm Snooze
// https://codeforces.com/contest/916/problem/A

/*
 * Problem: Jamie and Alarm Snooze
 * 
 * Purpose: Find the minimum number of snooze button presses needed to set an alarm
 *          at a "lucky" time (contains digit '7') such that waking up at hh:mm is
 *          achievable by pressing snooze every x minutes.
 * 
 * Algorithm:
 * - Start from the target time (hh:mm)
 * - Move backward by x minutes each iteration until a "lucky" time is found
 * - A time is lucky if it contains the digit '7'
 * - Use modular arithmetic to handle time wrapping (24-hour clock)
 * 
 * Time Complexity: O(24 * 60) = O(1) since we iterate at most one full day
 * Space Complexity: O(1) as only a constant amount of extra space is used
 */

#include <cstdio>
int main() {
  long x, h, m;
  scanf("%ld %ld %ld", &x, &h, &m);
  long num(0);
  for (num = 0; num < 24 * 60; num++) {
    // Check if current time is lucky (contains digit '7')
    if (h % 10 == 7 || m % 10 == 7) {
      break;
    } else {
      // Move backward by x minutes
      m -= x;
      // Handle minute underflow
      if (m < 0) {
        m += 60;
        --h;
      }
      // Handle hour underflow (wrap to previous day)
      if (h < 0) {
        h += 24;
      }
    }
  }
  printf("%ld\n", num);
  return 0;
}


// https://github.com/VaHiX/CodeForces/