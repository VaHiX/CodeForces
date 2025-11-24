// Problem: CF 2109 C3 - Hacking Numbers (Hard Version)
// https://codeforces.com/contest/2109/problem/C3

/*
C3. Hacking Numbers (Hard Version)
Interactive problem to transform an unknown integer x (1 <= x <= 10^9) into a given integer n using at most f(n) commands.

Algorithms/Techniques:
- Use mul 999999999 to get x close to 10^9, then use digit to get sum of digits.
- Based on the sum of digits and value of n, compute difference and adjust with add command.
- For any valid input x, f(n) ensures transformation using at most a fixed number of operations.

Time Complexity: O(1) per test case - Each test case uses constant number of commands.
Space Complexity: O(1) - Uses only a few variables regardless of input size.
*/

#include <iostream>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t, n, r;
  cin >> t;
  while (t--) {
    cin >> n;
    cout << "mul 999999999" << endl;   // Multiply x by large number to get close to 10^18
    cin >> r;
    cout << "digit" << endl;          // Get sum of digits of current x
    cin >> r;
    if (n != 81) {                    // If target is not 81, adjust with add command
      cout << "add " << n - 81 << endl; // Add the difference to reach target
      cin >> r;
    }
    cout << "!" << endl;              // Confirm we've reached the target
    cin >> r;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/