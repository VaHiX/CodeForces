// Problem: CF 2029 F - Palindrome Everywhere
// https://codeforces.com/contest/2029/problem/F

/*
F. Palindrome Everywhere
Algorithms/Techniques: String matching, cycle analysis, palindrome property checking

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1) additional space (not counting input storage).

Problem Description:
Given a cycle with n vertices and edges colored R or B, determine if there exists a palindrome route 
between every pair of vertices. A route is a palindrome if for each pair of symmetric positions,
the edges have the same color.

The solution checks:
- If all edges are the same color → YES
- Otherwise analyzes structure to check constraints on edge colors
*/

#include <iostream>
#include <string>

using namespace std;
const int N = 1e6 + 10;
int n, ans;
string s;
signed _main() {
  cin >> n >> s;
  int t = 0;
  // Count how many initial characters are same as first
  while (s[t] == s[0]) {
    ++t;
    if (t == n) {
      cout << "YES\n";
      return 0;
    }
  }
  bool fl1 = 0, fl2 = 0, fl = 0; // fl1: R seen in even-length segments, fl2: B seen in even-length segments, fl: odd-length segment flag
  int i = 0, tot = 0;
  while (i < n) {
    ++tot;
    int lst = (i + t) % n, len = 0;
    // Count length of current segment with same color
    while (s[(i + t) % n] == s[lst])
      ++i, ++len;
    if (len > 1) {
      // If we see more than one edge of same color, check if it's R or B
      if (s[lst] == 'R')
        fl1 = 1;
      else
        fl2 = 1;
      // If we have both red and blue in even-length segments — invalid
      if (fl1 & fl2) {
        cout << "NO\n";
        return 0;
      }
    }
    // If this segment length is even, then a flag should not be set yet
    if (len % 2 == 0) {
      if (fl) {
        cout << "NO\n";
        return 0;
      }
      fl = 1;
    }
  }
  // If we had odd-length segments or exactly two segments, it's valid
  if (fl || tot == 2)
    cout << "YES\n";
  else
    cout << "NO\n";
  return 0;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    _main();
  return 0;
}


// https://github.com/VaHiX/codeForces/