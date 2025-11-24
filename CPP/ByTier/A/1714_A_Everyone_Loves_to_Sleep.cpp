// Problem: CF 1714 A - Everyone Loves to Sleep
// https://codeforces.com/contest/1714/problem/A

/*
 * Problem: A. Everyone Loves to Sleep
 * Purpose: Determine how long Vlad can sleep until the next alarm clock rings,
 *          given his bedtime and a list of alarm times.
 *
 * Algorithm:
 *   - Convert all times (bedtime and alarms) into total minutes since midnight.
 *   - For each alarm, calculate the time difference in minutes from bedtime.
 *   - Handle wraparound (e.g., if alarm is at 00:00 and bedtime is at 23:59).
 *   - Select the minimum positive delay.
 *
 * Time Complexity: O(n) per test case, where n is the number of alarms.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, H, M;
    scanf("%ld %ld %ld", &n, &H, &M);
    long bed = 60 * H + M;  // Convert bedtime to minutes
    long res(24 * 60);      // Initialize result to maximum possible minutes (24 hours)
    for (long p = 0; p < n; p++) {
      long h, m;
      scanf("%ld %ld", &h, &m);
      long check = 60 * h + m - bed;  // Calculate time difference in minutes
      if (check < 0) {
        check += 24 * 60;  // Handle wraparound (e.g., from 23:59 to 00:00)
      }
      res = (res < check) ? res : check;  // Keep the minimum delay
    }
    printf("%ld %ld\n", res / 60, res % 60);  // Output hours and minutes
  }
}


// https://github.com/VaHiX/codeForces/