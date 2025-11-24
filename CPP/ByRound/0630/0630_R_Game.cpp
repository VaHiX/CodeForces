// Problem: CF 630 R - Game
// https://codeforces.com/contest/630/problem/R

/*
 * Code Purpose: Determine the winning player in a game theory problem where two players
 * alternate painting cells on an n×n grid such that no two painted cells share a side.
 * The player who cannot make a move loses.
 *
 * Algorithm/Technique: 
 * This is a classic game theory problem that can be solved by analyzing the
 * structure of optimal play. The key insight is that the first player wins if and only
 * if n is odd. This is because:
 * - When n is odd, the first player can always choose the center cell (if n is odd),
 *   and then mirror the second player's moves to maintain symmetry.
 * - When n is even, the second player can always mirror the first player's moves,
 *   leading to the first player eventually running out of valid moves.
 *
 * Time Complexity: O(1) - The solution only performs a single modulo operation
 * Space Complexity: O(1) - Only a constant amount of extra space is used
 */

#include <cstdio>
int main() {
  long long n;
  scanf("%lld\n", &n);
  puts(n % 2 ? "1" : "2");  // If n is odd, first player wins (1), otherwise second player wins (2)
  return 0;
}


// https://github.com/VaHiX/CodeForces/