// Problem: CF 1776 A - Walking Boy
// https://codeforces.com/contest/1776/problem/A

/*
 * Problem: A. Walking Boy
 * Purpose: Determine if it's possible for a judge to walk their dog "Boy" at least twice in a day,
 *          given that each walk requires 120 consecutive minutes and no messages can be sent during walks.
 *          Messages are sent at specific times and cannot overlap with walks.
 *
 * Algorithm:
 * - For each test case, we process all message times.
 * - We calculate gaps between consecutive messages (and also from last message to end of day).
 * - If a gap is >= 120 minutes, we can place one walk there.
 * - If we find at least two such gaps, output "YES", otherwise "NO".
 *
 * Time Complexity: O(n) per test case, where n is the number of messages.
 * Space Complexity: O(1), only using a few variables for computation.
 */

#include <iostream>

using namespace std;
int main() {
  int n, m;
  cin >> n;
  while (n--) {
    int p = 0, t = 0;  // 'p' counts number of valid walks, 't' tracks previous message time
    cin >> m;
    for (int i = 0; i < m; i++) {
      int x;
      cin >> x;
      // Calculate gap between current and previous message
      p += (x - t) / 120;  // If gap >= 120, we can fit at least one walk
      t = x;               // Update previous message time
    }
    // Add the final gap from last message to end of day (1440 minutes)
    p += (1440 - t) / 120;
    if (p >= 2)   // If we can place at least two walks
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
}


// https://github.com/VaHiX/codeForces/