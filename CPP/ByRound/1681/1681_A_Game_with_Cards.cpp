// Problem: CF 1681 A - Game with Cards
// https://codeforces.com/contest/1681/problem/A

#include <cstdio>
// Flowerbox:
// Problem: Game with Cards
// Purpose: Determine the winner of a turn-based game between Alice and Bob,
//          where each player plays cards optimally. Players alternate turns,
//          and each play must be greater than the previous play.
//          The game ends when a player cannot make a move.
// Algorithm:
//   1. For each test case, find the maximum card value each player has.
//   2. If Alice's max is greater than Bob's max, Alice wins if she starts.
//   3. If Bob's max is greater than Alice's max, Bob wins if he starts.
//   4. If both maxes are equal:
//      - If Alice starts, she must play her max card, but then Bob can play
//        his own max. Since Alice won't have a higher card, she loses.
//      - If Bob starts, same logic applies, so Alice wins because Bob can't
//        beat the maximum.
//
// Time Complexity: O(n + m) per test case, where n is number of Alice's cards
//                  and m is number of Bob's cards (for finding max elements).
// Space Complexity: O(1), constant extra space used.

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mxa(0); // maximum card value for Alice
    while (n--) {
      long x;
      scanf("%ld", &x);
      mxa = (mxa > x) ? mxa : x; // update max card for Alice
    }
    long m;
    scanf("%ld", &m);
    long mxb(0); // maximum card value for Bob
    while (m--) {
      long x;
      scanf("%ld", &x);
      mxb = (mxb > x) ? mxb : x; // update max card for Bob
    }
    if (mxa > mxb) {
      puts("Alice\nAlice"); // Alice wins in both cases
    } else if (mxa < mxb) {
      puts("Bob\nBob"); // Bob wins in both cases
    } else {
      puts("Alice\nBob"); // Alice wins if she starts, Bob wins if he starts
    }
  }
}

// https://github.com/VaHiX/codeForces/