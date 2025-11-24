// Problem: CF 513 A - Game
// https://codeforces.com/contest/513/problem/A

/*
 * Problem: Game
 * 
 * Algorithm/Technique: Game Theory - Nim-like game analysis
 * 
 * Time Complexity: O(1) - Constant time operation
 * Space Complexity: O(1) - Constant space usage
 * 
 * The problem can be solved by analyzing the game state:
 * - First player starts the game.
 * - Each player can take between 1 and k1 (for first player) or k2 (for second player) balls per turn.
 * - The key insight is that if n1 > n2, the first player can always win by taking one ball, 
 *   leaving the second player in a losing position.
 * - Conversely, if n1 <= n2, the second player wins.
 * 
 * This is a simplified version where the optimal strategy is based on comparing the initial 
 * number of balls in each box.
 */

#include <cstdio>
int main() {
  int n1, n2, k1, k2;
  scanf("%d %d %d %d\n", &n1, &n2, &k1, &k2);
  puts(n1 > n2 ? "First" : "Second");  // Output winner based on comparison of n1 and n2
  return 0;
}


// https://github.com/VaHiX/CodeForces/