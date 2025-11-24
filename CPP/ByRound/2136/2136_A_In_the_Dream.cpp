// Problem: CF 2136 A - In the Dream
// https://codeforces.com/contest/2136/problem/A

/*
 * Problem: A. In the Dream
 * Purpose: Determine if a given football score scenario is possible under the constraint that
 *          no team scores three consecutive goals in the same half.
 *
 * Algorithm/Techniques:
 *   - Check for impossible scenarios based on max vs min ratios in each half
 *   - For each half, verify that the difference between max and min scores does not exceed
 *     twice the minimum plus two, which is a sufficient condition to avoid 3 consecutive goals.
 *
 * Time Complexity: O(1) per test case — constant time operations
 * Space Complexity: O(1) — only using fixed-size variables
 */

#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int t, a, b, c, d;
  cin >> t;
  while (t--) {
    cin >> a >> b >> c >> d;
    // Check if either half has an impossible score configuration
    // Specifically, check if max(score) > min(score) * 2 + 2 for each half
    if (max(a, b) > min(a, b) * 2 + 2 ||  // First half impossible?
        max(c - a, d - b) > min(c - a, d - b) * 2 + 2)  // Second half impossible?
      cout << "NO\n";
    else
      cout << "YES\n";
  }
}


// https://github.com/VaHiX/codeForces/