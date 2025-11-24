// Problem: CF 867 A - Between the Offices
// https://codeforces.com/contest/867/problem/A

/*
 * Problem: Determine if more flights were made from Seattle to San Francisco
 *          than from San Francisco to Seattle over the last n days.
 *
 * Algorithm/Techniques: 
 *   - Single pass through the string to count net direction of travel
 *   - Increment count when moving from S to F (Seattle to San Francisco)
 *   - Decrement count when moving from F to S (San Francisco to Seattle)
 *   - Output "YES" if count > 0, otherwise "NO"
 *
 * Time Complexity: O(n), where n is the number of days
 * Space Complexity: O(1), only using a few variables regardless of input size
 */

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long count(0);
  for (long p = 1; p < s.size(); p++) {
    // If we moved from Seattle (S) to San Francisco (F), increment count
    if (s[p - 1] == 'S' && s[p] == 'F') {
      ++count;
    } else if (s[p - 1] == 'F' && s[p] == 'S') {
      // If we moved from San Francisco (F) to Seattle (S), decrement count
      --count;
    }
  }
  // Output YES if more flights from Seattle to San Francisco
  puts((count > 0) ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/