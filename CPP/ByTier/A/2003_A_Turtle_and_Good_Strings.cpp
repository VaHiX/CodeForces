// Problem: CF 2003 A - Turtle and Good Strings
// https://codeforces.com/contest/2003/problem/A

/*
 * Problem: Turtle and Good Strings
 * 
 * Algorithm/Technique: Greedy Observation
 * 
 * Time Complexity: O(n) where n is the length of the string (due to single pass comparison)
 * Space Complexity: O(1) - only using a constant amount of extra space
 * 
 * Key Insight:
 * A string is good if it can be split into at least two parts such that the first character 
 * of any part is not equal to the last character of any later part.
 * 
 * The crucial observation is:
 * - If the first and last characters of the string are different, we can always split it 
 *   into two parts: the first character as one part, and the rest as another part. This satisfies 
 *   the condition since the first character of the first part is not equal to the last character 
 *   of the second part.
 * - If the first and last characters are the same, no matter how we split the string into 
 *   at least two parts, we will always have at least one pair where the first character of a 
 *   part equals the last character of a later part. Therefore, such a string cannot be good.
 * 
 * So, the solution simply checks whether the first and last characters of the string are different.
 */

#include <stddef.h>
#include <iostream>
#include <string>

using namespace std;
using ll = long long;
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 37
#endif
inline void solve() {
  int n;
  string s;
  cin >> n >> s;
  // If first and last characters are different, it's possible to split into valid parts
  if (s.front() != s.back()) {
    cout << "yes\n";
  } else {
    // If they are the same, there's no valid way to split the string
    cout << "no\n";
  }
}
signed main() {
#ifdef LOCAL
  freopen("test.in", "r", stdin);
  freopen("err.txt", "w", stderr);
#endif
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);
  signed t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/