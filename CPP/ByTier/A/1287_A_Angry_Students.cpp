// Problem: CF 1287 A - Angry Students
// https://codeforces.com/contest/1287/problem/A

/*
 * Problem: Angry Students
 * Algorithm: Two-pointer simulation to track the maximum distance between an 'A' and a 'P'
 *            such that the 'P' becomes angry due to the 'A' throwing a snowball.
 * 
 * Time Complexity: O(n) where n is the length of the string (each character processed once)
 * Space Complexity: O(1) - only using a constant amount of extra space
 * 
 * Techniques:
 *   - Single pass through the string
 *   - Tracking last seen 'A' to compute distances to subsequent 'P's
 *   - Simulation of snowball propagation from left to right (in string order)
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Fast I/O synchronization
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long last(-1), ans(0);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'A') {
        last = p; // Update the index of the most recent angry student
      } else if (s[p] == 'P') {
        if (last < 0) {
          continue; // No previous angry student, so this 'P' cannot become angry
        }
        long dist = p - last; // Distance from last angry student to current patient student
        ans = (ans > dist) ? ans : dist; // Keep track of maximum distance
      }
    }
    std::cout << ans << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/