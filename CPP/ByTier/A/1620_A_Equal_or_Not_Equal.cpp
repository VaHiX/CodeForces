// Problem: CF 1620 A - Equal or Not Equal
// https://codeforces.com/contest/1620/problem/A

/*
 * Code Purpose: Determines if there exists a valid array of positive integers 
 *               consistent with the given equality/not-equality constraints 
 *               arranged in a circle.
 *
 * Algorithm: The problem is essentially checking if a circular graph can be 
 *            2-colored such that edges marked 'E' connect same-colored nodes 
 *            and edges marked 'N' connect different-colored nodes. This is 
 *            equivalent to checking if the string has no contradiction 
 *            (e.g., adjacent 'E's followed by 'N' in a way that creates an odd cycle).
 *
 * Time Complexity: O(n) for each test case, where n is the length of the string.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Optimize I/O speed
  long t;
  std::cin >> t;  // Read number of test cases
  while (t--) {
    std::string s;
    std::cin >> s;  // Read constraint string
    long cnt(0);   // Counter for 'N' characters
    for (long p = 0; p < s.size(); p++) {
      cnt += s[p] == 'N';  // Count number of 'N' characters
    }
    std::cout << (cnt != 1 ? "YES" : "NO") << std::endl;  // Output result based on count
  }
}


// https://github.com/VaHiX/codeForces/