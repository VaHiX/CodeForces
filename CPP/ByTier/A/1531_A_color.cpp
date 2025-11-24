// Problem: CF 1531 A - Зингер | color
// https://codeforces.com/contest/1531/problem/A

#include <iostream>
#include <string>

using namespace std;

/*
 * Code purpose: This program simulates the color changing process of the Zinger dome based on a series of commands.
 *               It tracks the current color and whether color changes are locked or not.
 * 
 * Algorithms/Techniques: 
 *   - Linear simulation of command processing
 *   - State tracking using a flag (fl) for lock state
 *   - String comparison for command interpretation
 * 
 * Time Complexity: O(n), where n is the number of messages. Each message is processed exactly once.
 * Space Complexity: O(1), only a constant amount of extra space is used regardless of input size.
 */
int main() {
  int n, fl = 0;  // fl = 0 means unlocked, fl = 1 means locked
  string s = "blue";  // Initial color is blue
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    string st;
    cin >> st;
    if (st == "lock")
      fl = 1;  // Lock the color change
    else if (st == "unlock")
      fl = 0;  // Unlock the color change
    else if (fl == 0)  // If not locked, change the color
      s = st;
  }
  cout << s;
}


// https://github.com/VaHiX/CodeForces/