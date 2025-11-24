// Problem: CF 1709 C - Recover an RBS
// https://codeforces.com/contest/1709/problem/C

/*
 * Problem: Recover an RBS
 * 
 * Algorithm/Technique:
 * - Use a greedy approach to determine if there's a unique way to replace '?' with '(' or ')'
 *   such that the result is a valid RBS.
 * - Track the balance of brackets (cnt) and count of '?' (q).
 * - When we encounter a point where cnt + q == 1, we must set the first '?' to '(' to maintain
 *   valid prefix. We then reset q to 0 and cnt to 1.
 * - At the end, the final balance must equal the number of remaining '?' to ensure unique solution.
 * 
 * Time Complexity: O(n) where n is the total length of all input strings across all test cases.
 * Space Complexity: O(1) — only using a few variables for tracking.
 */

#include <iostream>
#include <string>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int cnt = 0, q = 0;
    string s;
    cin >> s;
    for (char ch : s) {
      if (ch == '(')
        cnt++;  // Increment balance for opening bracket
      if (ch == ')')
        cnt--;  // Decrement balance for closing bracket
      if (ch == '?')
        q++;    // Count unknown brackets
      if (cnt + q == 1) {  // If we can only close one more bracket with remaining '?'
        cnt = 1;   // Set balance back to 1 (we're forced to start with '(')
        q = 0;     // Reset question mark count since the '?' was used
      }
    }
    if ((cnt) == q)  // If final balance equals remaining '?', solution is unique
      cout << "YES\n";
    else
      cout << "NO\n";
  }
}


// https://github.com/VaHiX/CodeForces/