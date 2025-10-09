// Problem: CF 2117 A - False Alarm
// https://codeforces.com/contest/2117/problem/A

/*
 * Problem: A. False Alarm
 * Purpose: Determine if Yousef can pass through all doors in a hallway,
 *          given that he can use a special button once to open all closed doors for x seconds.
 *
 * Algorithm:
 * - For each test case, iterate through the doors.
 * - Track the first closed door and check if using the button at that point allows passing
 *   all subsequent doors within the button's duration.
 * - If at any point a closed door is encountered such that the button can't cover it,
 *   return "NO".
 *
 * Time Complexity: O(n) per test case, where n is the number of doors.
 * Space Complexity: O(1), constant extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    long idx(-1);         // index of the first closed door
    bool possible(true);  // whether a solution exists
    
    for (long p = 0; p < n; p++) {
      int s;
      scanf("%d", &s);
      
      // If current door is closed and this is the first closed door
      if (idx < 0 && s) {
        idx = p;
      }
      
      // If a closed door is encountered after the first one,
      // check if the button can cover it from the start of the first closed door.
      if (s && idx + x <= p) {
        possible = false;
      }
    }
    
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/