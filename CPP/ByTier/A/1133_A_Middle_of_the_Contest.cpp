// Problem: CF 1133 A - Middle of the Contest
// https://codeforces.com/contest/1133/problem/A

/*
 * Problem: A. Middle of the Contest
 * Purpose: Calculate the midpoint time of a contest given start and end times.
 * Algorithm: 
 *   1. Parse input strings to extract hours and minutes.
 *   2. Convert start and end times to total minutes from midnight.
 *   3. Compute duration in minutes, then divide by 2 to get half duration.
 *   4. Add half duration to start time in minutes.
 *   5. Convert back to hours and minutes format with proper zero-padding.
 * 
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only using a fixed amount of variables
 */

#include <iostream>
#include <string>

int main() {
  std::string s, t;
  std::cin >> s >> t;
  int h1, m1, h2, m2;
  // Extract hours and minutes from input string s (start time)
  h1 = 10 * (s[0] - '0') + (s[1] - '0');
  m1 = 10 * (s[3] - '0') + (s[4] - '0');
  // Extract hours and minutes from input string t (end time)
  h2 = 10 * (t[0] - '0') + (t[1] - '0');
  m2 = 10 * (t[3] - '0') + (t[4] - '0');
  // Calculate total duration in minutes
  int dur = 60 * (h2 - h1) + (m2 - m1);
  // Divide duration by 2 to get half duration
  dur /= 2;
  // Add half duration to start minutes
  m1 += dur;
  // Adjust hours if minutes exceed 60
  h1 += (m1 / 60);
  // Keep minutes within 0-59 range
  m1 %= 60;
  // Output result in hh:mm format with zero padding
  std::cout << h1 / 10 << h1 % 10 << ":" << m1 / 10 << m1 % 10 << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/