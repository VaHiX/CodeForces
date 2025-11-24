// Problem: CF 1301 A - Three Strings
// https://codeforces.com/contest/1301/problem/A

/*
 * Problem: A. Three Strings
 * Purpose: Determine if it's possible to make strings 'a' and 'b' equal by swapping
 *          each character of 'c' with either 'a' or 'b' at the same position.
 * Algorithm: For each position i, check if c[i] matches either a[i] or b[i].
 *            If for any position i, c[i] doesn't match either a[i] or b[i], return "NO".
 *            Otherwise, return "YES".
 *
 * Time Complexity: O(n), where n is the length of the strings.
 * Space Complexity: O(1), not counting input storage.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Optimize I/O speed
  long t;
  std::cin >> t; // Read number of test cases
  while (t--) { // Process each test case
    std::string a, b, c;
    std::cin >> a >> b >> c; // Read the three strings
    bool res(true); // Assume result is true initially
    for (long p = 0; p < a.size(); p++) { // Iterate through each character position
      if (!(a[p] == c[p] || b[p] == c[p])) { // If c[i] doesn't match a[i] or b[i]
        res = false; // Set result to false
        break; // Exit loop early
      }
    }
    std::cout << (res ? "YES" : "NO") << std::endl; // Output result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/