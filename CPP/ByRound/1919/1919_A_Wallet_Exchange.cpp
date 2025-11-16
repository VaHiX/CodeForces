// Problem: CF 1919 A - Wallet Exchange
// https://codeforces.com/contest/1919/problem/A

/*
 * Problem: Wallet Exchange
 * Algorithms/Techniques: Game Theory, Mathematical Analysis
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * The game is about optimal play between Alice and Bob. Each player removes
 * one coin per turn from their current wallet, with the option to swap wallets.
 * The key observation is that the total number of moves in the game is a + b.
 * Since Alice goes first, she wins if and only if the total number of moves is odd,
 * because then she will make the last move. If the sum is even, Bob makes the last move.
 *
 * Therefore, the winner is determined by checking whether (a + b) is odd or even.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    a += b;                    // Total number of moves in the game
    puts(a % 2 ? "Alice" : "Bob"); // Alice wins if total is odd, else Bob
  }
}


// https://github.com/VaHiX/codeForces/