// Problem: CF 2155 A - El fucho
// https://codeforces.com/contest/2155/problem/A

/*
 * Problem: Determine the total number of matches played in a modified double-elimination tournament.
 *
 * Algorithm/Techniques:
 * - Simulation of tournament structure with winners and losers groups.
 * - Each match eliminates exactly one team (except for the final match which determines the winner).
 * - In a double-elimination format, every team except the winner is eliminated after losing once or twice.
 * - The total number of matches can be derived mathematically:
 *   - For n teams, we need to eliminate (n - 1) teams.
 *   - Each match eliminates at least one team.
 *   - Therefore, exactly (n - 1) matches are required to determine the winner.
 *   - However, in this specific implementation, formula is simplified to 2*(n-1).
 *
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), only using a few variables.
 */

#include <iostream>
using namespace std;

int main() {
  int t;              // Read number of test cases
  cin >> t;
  int a;              // Variable to store current input (number of teams)
  while (t--) {       // Loop through each test case
    cin >> a;         // Input the number of teams for this case
    cout << 2 * (a - 1); // Output total matches using derived formula
    cout << endl;     // New line after each output
  }
}


// https://github.com/VaHiX/CodeForces/