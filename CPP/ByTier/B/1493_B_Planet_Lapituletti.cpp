// Problem: CF 1493 B - Planet Lapituletti
// https://codeforces.com/contest/1493/problem/B

/*
 * Problem: Planet Lapituletti - Find the nearest time when the mirrored clock shows a valid time.
 * 
 * Algorithm:
 * - Precompute which digits can be mirrored to valid digits (using array y).
 * - Start from given time s and iterate forward minute by minute.
 * - For each time, check if the mirrored digits form a valid time (hours < h, minutes < m).
 * - If valid, output the time and stop.
 * 
 * Time Complexity: O(h * m) per test case in worst case, since we may need to check all times in a day.
 * Space Complexity: O(1) - only fixed-size arrays and variables used.
 */

#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
  // Mapping array for valid mirrored digits
  // y[digit] = mirrored_digit, x = invalid (100)
  int x = 100, y[10] = {0, 1, 5, x, x, 2, x, x, 8, x};
  int t;
  cin >> t;
  while (t--) {
    int h, m;
    cin >> h >> m;
    int a1, a2;
    char t_char;
    cin >> a1 >> t_char >> a2; // Read HH:MM
    while (1) {
      // Mirror the minutes (a2) and hours (a1)
      int b1 = y[a2 % 10] * 10 + y[a2 / 10]; // Mirror minutes
      int b2 = y[a1 % 10] * 10 + y[a1 / 10]; // Mirror hours
      if (b1 < h and b2 < m) {
        // If mirrored time is valid, output the current time
        printf("%02d:%02d\n", a1, a2);
        break;
      }
      // Increment time
      if (++a2 == m) {
        a2 = 0;
        a1 = (a1 + 1) % h; // Move to next hour, wrap around if needed
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/