// Problem: CF 1858 A - Buttons
// https://codeforces.com/contest/1858/problem/A

/*
 * Problem: A. Buttons
 * Purpose: Determine the winner of a game where Anna and Katie take turns pressing buttons,
 *          with different button types having restrictions on who can press them.
 * 
 * Algorithm:
 * - Both players play optimally.
 * - Anna goes first.
 * - Each player has buttons they can only press (a and b) and buttons they can share (c).
 * - The total number of moves in the game is a + b + c.
 * - Anna wins if she can force a win based on the parity of total moves and how many shared
 *   buttons are available.
 * - If we calculate total moves (a + b + c), then check ((a + c) % 2) to determine
 *   whether there is an odd number of Anna's possible moves. If her advantage allows her
 *   to win even when Katie makes optimal picks, she wins.
 *
 * Time Complexity: O(t), where t is the number of test cases
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld\n", &a, &b, &c); // Read the number of buttons for each type
    puts((a + (c % 2) > b) ? "First" : "Second"); // Determine winner based on optimal play
  }
}


// https://github.com/VaHiX/codeForces/