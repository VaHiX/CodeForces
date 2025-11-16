// Problem: CF 1739 C - Card Game
// https://codeforces.com/contest/1739/problem/C

/*
 * Problem: Card Game
 * 
 * Algorithm:
 * This problem involves determining the number of ways to distribute cards between two players
 * (Alex and Boris) such that the game ends in a win for Alex, a win for Boris, or a draw.
 * 
 * The key insight is based on combinatorial game theory and optimal play:
 * - At each turn, a player must play a card, and the opponent responds with a stronger card if possible.
 * - A player wins if the opponent cannot respond with a stronger card.
 * 
 * The solution uses dynamic programming with a closed-form approach:
 * - For a given n (even), we compute values for different distributions.
 * - We maintain:
 *   - x: number of ways Alex wins
 *   - y: number of ways Boris wins
 *   - mid: intermediate value used for computation
 * 
 * Time Complexity: O(n) for each test case
 * Space Complexity: O(1)
 * 
 * The code implements a mathematical recurrence relation derived from the game dynamics,
 * where each step builds on the previous computation efficiently.
 */
#include <stdio.h>
#include <iostream>

using namespace std;
int main() {
  int t, n, i;
  scanf("%d", &t);
  while (t--) {
    long long x = 1, y = 0, mid = 2; // Initialize variables for calculation
    scanf("%d", &n);
    for (i = 4; i <= n; i = i + 2) {
      // Update mid using the formula: mid = mid * 2 * (i - 1) / i * 2
      mid = mid * 2 * (i - 1) / i * 2;
      // Calculate x as half of mid plus y
      x = mid / 2 + y;
      // Calculate y as the remaining value after subtracting x and 1 from mid
      y = mid - x - 1;
    }
    // Output the results modulo 998244353
    cout << x % 998244353 << " " << y % 998244353 << " " << 1 << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/