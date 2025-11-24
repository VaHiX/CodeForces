// Problem: CF 1419 A - Digit Game
// https://codeforces.com/contest/1419/problem/A

/*
 * Problem: Digit Game
 * Algorithm: Game Theory, Optimal Play Strategy
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 *
 * In this game, two agents (Raze and Breach) take turns marking digits of a number.
 * Raze (agent 1) can only mark odd-positioned digits (1-indexed), and Breach (agent 2) 
 * can only mark even-positioned digits. The game ends when only one digit remains,
 * and if that digit is odd, Raze wins; otherwise Breach wins.
 *
 * The key insight is to simulate the optimal play:
 * - If n is odd, Raze starts first; if n is even, Breach starts first.
 * - Each player tries to ensure their winning condition (odd digit for Raze).
 * - We check the parity of available digits at each valid position and determine
 *   if the current player can force a win by choosing the right digit.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    
    // Determine whose turn it is based on parity of n
    bool turn(!(n % 2)); // true if Raze's turn, false if Breach's turn
    
    // Initialize win flag to false
    bool win(false);
    
    // Iterate through positions, depending on whose turn it is:
    // If turn is true (Raze's turn), start from index 0 (odd positions)
    // If turn is false (Breach's turn), start from index 1 (even positions)
    for (long p = turn; !win && p < s.length(); p += 2) {
      // Check if digit at position p can lead to a win
      // For Raze: if current digit is odd, he wins; for Breach: if current digit is even, he wins
      win |= ((s[p]) % 2 == !turn);
    }
    
    // Output result: 1 if Raze wins, 2 if Breach wins
    std::cout << (2 - (turn ^ win)) << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/