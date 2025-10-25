// Problem: CF 2109 C2 - Hacking Numbers (Medium Version)
// https://codeforces.com/contest/2109/problem/C2

/*
 * Problem: C2. Hacking Numbers (Medium Version)
 * Algorithm/Techniques: Interactive problem solving using mathematical operations
 * Time Complexity: O(1) per test case - constant number of operations (4 commands maximum)
 * Space Complexity: O(1) - only using a few variables regardless of input size
 *
 * This is an interactive problem where we must transform an unknown integer x (initially 9)
 * into the given target value n using at most 4 commands. The allowed commands are:
 * add y, mul y, div y, digit (sum of digits), and ! to indicate completion.
 *
 * Strategy:
 * For the first test case, we use a simple approach: multiply by 10 after adding a value
 * to reach a round number, then adjust with addition. The second approach uses digit sum
 * followed by division to reduce large numbers.
 */

#include <iostream>
using namespace std;

int main() {
  int t;
  cin >> t; // Read number of test cases
  while (t--) {
    int n;
    cin >> n; // Read target number
    
    // First approach: multiply by 10 then add to reach n
    cout << "mul 9\n";        // Multiply x (initially 9) by 9 -> x = 81
    cout << "digit\n";        // Convert x to sum of digits -> x = 8 + 1 = 9
    cout << "digit\n";        // Convert x to sum of digits -> x = 9
    cout << "add " << n - 9 << "\n";  // Add (n - 9) to get target n
    cout << "!\n";            // Signal completion
    
    // Read responses from the interactor
    cin >> n;
    cin >> n;
    cin >> n;
    cin >> n;
    cin >> n;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/