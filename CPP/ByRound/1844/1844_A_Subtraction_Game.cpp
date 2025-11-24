// Problem: CF 1844 A - Subtraction Game
// https://codeforces.com/contest/1844/problem/A

/*
 * Problem: Subtraction Game
 * Algorithm/Technique: Game Theory, Sprague-Grundy Theorem Analysis
 * 
 * The problem asks us to find a value of n such that the second player has a winning strategy.
 * This is a classic game theory problem where we analyze the winning and losing positions.
 * 
 * Key Insight:
 * A position is losing for the current player if all moves from it lead to winning positions for the opponent.
 * For this particular game, if n is a multiple of (a + b), then the second player can always mirror
 * the first player's moves and maintain the invariant that the remaining number of stones is a multiple of (a + b).
 * Eventually, the first player will be left with 0 stones and lose.
 * 
 * However, in the given examples, it looks like we are looking for a value such that the second player wins
 * right away or in very few steps. Looking carefully at the examples:
 * - For a=1, b=4: n=2 → after first player removes 1, second removes 1 and wins.
 * - For a=1, b=5: n=6 → second player can force a win by responding to any move.
 * - For a=9, b=26: n=3 → first player can't move, so second wins.
 * 
 * From the pattern and standard analysis of such games, if we pick n = a + b, 
 * the second player can always respond in such a way as to keep the number of stones 
 * congruent to 0 modulo (a + b) after their turn.
 * 
 * Time Complexity: O(t), where t is the number of test cases
 * Space Complexity: O(1)
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    printf("%ld\n", a + b); // Output the sum of a and b, which ensures second player wins
  }
}


// https://github.com/VaHiX/CodeForces/