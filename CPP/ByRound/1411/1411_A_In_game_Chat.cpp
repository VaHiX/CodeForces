// Problem: CF 1411 A - In-game Chat
// https://codeforces.com/contest/1411/problem/A

/*
 * Problem: In-game Chat Bad Message Filter
 * Algorithm: Count trailing closing parentheses and compare with remaining characters.
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(1) - only using a few variables regardless of input size.
 *
 * Approach:
 * 1. For each test case, count how many ')' characters appear at the end of the string.
 * 2. If the count of trailing ')' is strictly greater than the number of characters
 *    before these trailing ones, then the message is bad ("Yes"), otherwise "No".
 */

#include <iostream>
#include <string>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, cn = 0; // n: length of string, cn: count of trailing ')'
    cin >> n;
    string s;
    cin >> s;
    n--; // Move to last index
    while (s[n] == ')' && n >= 0) // Count trailing ')'
      cn++, n--;
    // If trailing ')' count is greater than remaining characters, it's bad
    cout << (s.size() - cn < cn ? "Yes" : "No") << "\n";
  }
}


// https://github.com/VaHiX/codeForces/