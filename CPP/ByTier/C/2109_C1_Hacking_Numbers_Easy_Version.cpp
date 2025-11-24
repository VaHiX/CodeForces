// Problem: CF 2109 C1 - Hacking Numbers (Easy Version)
// https://codeforces.com/contest/2109/problem/C1

/*
C1. Hacking Numbers (Easy Version)
Interactive problem to transform an unknown integer x (initially 9) into a given integer n using at most 7 commands.
Commands allowed: add, mul, div, digit.
The algorithm uses:
- mul 9: quickly increases x to 81 (since x=9)
- digit: computes sum of digits
- add (n - 9): adjusts to reach target n

Time Complexity: O(1) per test case (fixed number of operations)
Space Complexity: O(1) (only using a few variables)

Commands executed:
1. mul 9
2. digit
3. digit
4. add (n - 9)
5. !
*/
#include <iostream>
using namespace std;
int main() {
  int t, n;
  cin >> t;
  while (t-- && cin >> n) // Read test cases and initial n
    cout << "mul 9\ndigit\ndigit\nadd " << n - 9 << "\n!\n",
        cin >> n >> n >> n >> n >> n; // Read and discard responses from jury
}


// https://github.com/VaHiX/codeForces/