// Problem: CF 1883 A - Morning
// https://codeforces.com/contest/1883/problem/A

/*
 * Purpose: Calculate the minimum time required to enter a 4-digit PIN on a numeric keypad.
 *          The keypad is arranged in a line where each digit is adjacent to its neighbors,
 *          except for 0 which is adjacent to 9.
 *          The cursor starts at digit 1.
 *
 * Algorithm:
 *   - For each digit in the PIN:
 *     - Calculate the minimal distance from the previous cursor position to the current digit.
 *     - Add the distance plus 1 second (for pressing the button) to total time.
 *     - Update the cursor position to the current digit.
 *
 * Time Complexity: O(n) where n is the length of the PIN (4 in this case, so effectively O(1)).
 * Space Complexity: O(1) - only a few variables used, independent of input size.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string x;
    std::cin >> x;
    int prev(1), cnt(0); // prev: previous digit position, cnt: total time
    for (long p = 0; p < x.size(); p++) {
      int cur = x[p] - '0'; // cur: current digit in PIN
      if (cur == 0) {
        cur = 10; // Treat 0 as 10 for distance calculation (0 is adjacent to 9)
      }
      int dist = cur - prev; // Calculate the difference in positions
      if (dist < 0) {
        dist = -dist; // Take absolute value of distance
      }
      // Add the minimal movement steps + 1 second to press
      cnt += dist + 1;
      prev = cur; // Update previous position
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/