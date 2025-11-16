// Problem: CF 944 A - World Cup
// https://codeforces.com/contest/944/problem/A

/*
 * Code Purpose: Determine in which round two specific teams will meet in a knockout tournament.
 *               The tournament follows a standard play-off system where teams are paired in each round,
 *               with the winner advancing to the next round.
 *
 * Algorithm/Techniques:
 *   - Simulate the tournament rounds by halving team IDs (integer division + ceiling)
 *   - Compare the current positions of the two teams in the tournament bracket
 *   - Continue until the teams are in adjacent positions in the tournament bracket
 *   - If teams are in the final round (only 2 teams), output "Final!"
 *
 * Time Complexity: O(log n), where n is the number of teams.
 *                    Each iteration halves the number of teams, so at most log(n) iterations.
 *
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <iostream>

using namespace std;

int main() {
  int a, b, c; // a: number of teams, b: first team id, c: second team id
  cin >> a >> b >> c;
  int cnt = 0; // counter for the round number

  // Loop until teams b and c are in adjacent positions in the tournament
  while (b / 2 + b % 2 != c / 2 + c % 2) {
    b = b / 2 + b % 2;  // Compute next round position for team b
    c = c / 2 + c % 2;  // Compute next round position for team c
    a /= 2;             // Update total number of teams for next round
    cnt++;              // Increment the round counter
  }

  // If we reach a point where number of teams is 2, then the teams will meet in the final
  if (a == 2) {
    cout << "Final!";
    return 0;
  }
  // Otherwise, output the round number (cnt + 1 because initially we are at round 0)
  cout << cnt + 1;
  return 0;
}


// https://github.com/VaHiX/CodeForces/