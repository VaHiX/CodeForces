// Problem: CF 1043 C - Smallest Word
// https://codeforces.com/contest/1043/problem/C

#include <iostream>
#include <string>

using namespace std;

/**
 * C. Smallest Word
 *
 * Purpose: Given a string consisting only of 'a' and 'b', determine which prefixes
 *          to reverse in order to obtain the lexicographically smallest possible string.
 *
 * Algorithm:
 *   - Process each prefix from length 1 to n.
 *   - For each prefix, decide whether reversing it leads to a smaller lexicographical result.
 *   - This approach uses greedy strategy: if current character is 'b' and previous character
 *     in the result is 'a', then we should reverse the prefix up to this point.
 *
 * Time Complexity: O(n^2), where n is the length of input string s
 * Space Complexity: O(n), due to string s and output vector
 */

string s;
void solve() {
  s += 'b'; // Add sentinel 'b' at end to simplify loop logic (s.size() - 1)
  for (int i = 0; i < s.size() - 1; i++) {
    cout << (s[i] != s[i + 1]) << " "; // Output 1 if characters differ, else 0
  }
}
int main() {
  cin >> s;
  solve();
}

// https://github.com/VaHiX/codeForces/