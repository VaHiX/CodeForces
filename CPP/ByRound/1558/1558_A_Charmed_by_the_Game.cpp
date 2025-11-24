// Problem: CF 1558 A - Charmed by the Game
// https://codeforces.com/contest/1558/problem/A

/*
 * Problem: A. Charmed by the Game
 * Purpose: Find all possible numbers of breaks that can occur in a tennis match
 *          given the number of games won by Alice and Borys.
 *
 * Algorithms:
 *   - Mathematical analysis of serve patterns and break conditions
 *   - Observing that breaks occur when receiving player wins a game
 *   - The total number of breaks is bounded by the sum of games,
 *     and depends on the starting server and alternating pattern
 *
 * Time Complexity: O(1) per test case (constant time operations)
 * Space Complexity: O(1) (only using a few variables, not storing results)
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int n, m, t;  // n: Alice's wins, m: Borys's wins, t: number of test cases

int main() {
  cin >> t;  // Read number of test cases
  while (t--) {
    cin >> n >> m;  // Read Alice's and Borys's wins
    
    int d = abs(n - m) / 2;  // Calculate the difference in wins divided by 2
    // This determines the minimum number of breaks possible
    printf("%d\n", 1 + (n + m - d - d) / ((n + m) % 2 == 0 ? 2 : 1));
    // Compute how many valid break counts there are
    
    for (int i = d; i <= n + m - d; i += (n + m) % 2 == 0 ? 2 : 1) {
      // Iterate from minimum possible breaks to maximum, stepping by 2 if total games is even,
      // or 1 if total games is odd
      printf("%d ", i);
    }
    printf("\n");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/