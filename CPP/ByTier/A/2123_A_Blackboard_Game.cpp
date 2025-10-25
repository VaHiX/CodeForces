// Problem: CF 2123 A - Blackboard Game
// https://codeforces.com/contest/2123/problem/A

/*
 * Problem: A. Blackboard Game
 * Algorithm/Technique: Mathematical game theory, modular arithmetic
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * Explanation:
 * The key insight is to analyze the game based on the modulo 4 values of numbers.
 * Numbers 0, 1, 2, 3 are on the board initially.
 * Each move involves choosing a number 'a' and then choosing 'b' such that (a + b) ≡ 3 (mod 4).
 * So for each number a, there is exactly one valid number b that satisfies the condition.
 * The game can be reduced to a pattern based on n % 4:
 * - If n % 4 != 0, Alice wins because she can force a win with optimal play.
 * - If n % 4 == 0, Bob wins because he can mirror Alice's moves and force her into a losing position.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    puts(n % 4 ? "Alice" : "Bob");  // Determine winner based on modulo 4 result
  }
}


// https://github.com/VaHiX/codeForces/