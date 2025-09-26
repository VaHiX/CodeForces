// Problem: CF 2106 F - Goblin
// https://codeforces.com/contest/2106/problem/F

/*
F. Goblin

Purpose:
This code solves the problem of finding the maximum size of a connected component of '0's in an n x n grid formed from a binary string s.
Each row i of the grid corresponds to flipping the i-th bit of s, and the task is to find the largest set of cells (all 0s) that are connected through adjacent sides.

Algorithm:
- For each character in the string, we determine how many 0s exist to the right and left.
- We track two values U (upward count) and D (downward count).
- When encountering a '0':
    - Add the number of remaining characters to D.
    - Reset U based on current D + 1.
- When encountering a '1':
    - Update U = D + 1,
    - Reset D to 0.
- Keep track of the maximum of U and D at any point.

Time Complexity: O(n) per test case, where n is the length of string s.
Space Complexity: O(1) excluding input/output space used.

*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

long long t, n, U, D, ans;
string s;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t; t--) {
    cin >> n >> s;
    s = " " + s, ans = D = U = 0; // Prepend space to make indexing from 1, initialize counters
    for (int i = 1; i <= n; i++) {
      if (s[i] == '0') {
        D += n - i, U += i - 1; // Extend D with remaining characters to the right, extend U with characters to the left
      } else {
        U = D + 1, D = 0; // Reset based on accumulated D
      }
      ans = max({ans, U, D}); // Keep track of maximum size seen so far
    }
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/