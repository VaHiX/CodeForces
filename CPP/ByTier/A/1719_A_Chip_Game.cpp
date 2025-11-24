// Problem: CF 1719 A - Chip Game
// https://codeforces.com/contest/1719/problem/A

#include <cstdio>
// Problem: Chip Game
// Description: Two players (Burenka and Tonya) play a game on an n x m board with a chip starting at the bottom-left corner.
//              Players can move the chip right or up by an odd number of cells. Burenka goes first.
//              Winner is determined based on optimal play.
// Algorithm: The key observation is that the total number of moves in the game depends on the parity of (n + m - 2).
//            If (n + m) is even, then Burenka (first player) loses; otherwise she wins.
// Time Complexity: O(1) per test case
// Space Complexity: O(1)
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    // If sum of dimensions is odd, Burenka wins; otherwise Tonya wins
    puts(((n + m) % 2) ? "Burenka" : "Tonya");
  }
}

// https://github.com/VaHiX/codeForces/