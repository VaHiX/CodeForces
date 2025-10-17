// Problem: CF 1927 A - Make it White
// https://codeforces.com/contest/1927/problem/A

/*
 * Problem: A. Make it White
 * Purpose: Given a string of 'W' (white) and 'B' (black) cells, find the minimum length of a continuous segment that needs to be painted white so that all cells become white.
 * 
 * Algorithm:
 *   - Identify the first black cell ('B') from the left (start index).
 *   - Identify the last black cell ('B') from the right (stop index).
 *   - The segment between these indices (inclusive) must be painted white.
 *   - Return the length of this segment: stop - start + 1.
 * 
 * Time Complexity: O(n), where n is the length of the string. We scan the string twice in the worst case.
 * Space Complexity: O(1), only using a constant amount of extra space for indices and variables.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long start(0);
    // Skip all leading 'W's to find the first 'B'
    while (s[start] == 'W') {
      ++start;
    }
    long stop(s.size() - 1);
    // Skip all trailing 'W's to find the last 'B'
    while (s[stop] == 'W') {
      --stop;
    }
    long len = stop - start + 1;
    std::cout << len << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/