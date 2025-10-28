// Problem: CF 1567 A - Domino Disaster
// https://codeforces.com/contest/1567/problem/A

/*
 * Problem: Domino Disaster
 * Purpose: Given one row of a 2xN grid covered by dominoes, reconstruct the other row.
 * Algorithm:
 *   - For each character in the input string:
 *     - If 'U' (top half), then the corresponding bottom half must be 'D'
 *     - If 'D' (bottom half), then the corresponding top half must be 'U'
 *     - If 'L' or 'R', they remain unchanged since they represent vertical dominoes.
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(n) for storing the result string.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::string t(s); // Copy input string to result
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'U') {
        t[p] = 'D'; // U maps to D
      } else if (s[p] == 'D') {
        t[p] = 'U'; // D maps to U
      }
      // L and R remain unchanged as they represent vertical dominoes
    }
    std::cout << t << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/