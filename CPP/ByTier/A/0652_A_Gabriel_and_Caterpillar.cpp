// Problem: CF 652 A - Gabriel and Caterpillar
// https://codeforces.com/contest/652/problem/A

/*
 * Problem: Gabriel and Caterpillar
 * Purpose: Determine the number of days Gabriel must wait to see the caterpillar reach the apple.
 * 
 * Algorithm:
 * - The caterpillar starts at height h1 and moves toward apple at height h2.
 * - It climbs 'a' cm during the day (12 hours) and slips down 'b' cm at night (12 hours).
 * - The process begins at 2 PM, so the first day has only 8 hours of climbing (from 2 PM to 10 PM).
 * - After the first day, each full day-night cycle results in a net gain of (a - b) cm.
 * 
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only a few integer variables are used
 */

#include <cstdio>
int main() {
  int h1, h2, a, b;
  scanf("%d %d\n%d %d", &h1, &h2, &a, &b);
  
  // Adjust h2 to be relative to the initial height and account for first day's climb (8 hours)
  h2 -= h1 + 8 * a;
  
  // Net progress per full day-night cycle (12 hours day + 12 hours night)
  a = (a - b) * 12;
  
  // If the apple is already reached after first day's climb
  if (h2 <= 0) {
    puts("0");
  } 
  // If the caterpillar cannot make net progress (climbs same or less than it slips)
  else if (a <= 0) {
    puts("-1");
  } 
  // Otherwise, calculate number of full cycles needed
  else {
    printf("%d\n", (h2 + a - 1) / a);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/