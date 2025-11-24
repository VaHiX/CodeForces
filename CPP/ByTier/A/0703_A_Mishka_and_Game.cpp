// Problem: CF 703 A - Mishka and Game
// https://codeforces.com/contest/703/problem/A

/*
Purpose: This program determines the winner of a dice game between Mishka and Chris based on the number of rounds each player wins.
           - For each round, both players roll a six-sided dice.
           - The player with the higher roll wins that round.
           - The overall winner is determined by who wins more rounds.
           - If both players win the same number of rounds, the result is a draw.

Algorithms/Techniques: Simulation
Time Complexity: O(n), where n is the number of rounds. We process each round exactly once.
Space Complexity: O(1), as we only use a constant amount of extra space regardless of input size.

*/
#include <cstdio>
int main() {
  long n;
  scanf("%ld\n", &n);
  long long sumX(0), sumY(0); // sumX counts Mishka's wins, sumY counts Chris's wins
  while (n--) {
    long x, y;
    scanf("%ld %ld\n", &x, &y);
    if (x > y) {
      ++sumX; // Mishka wins the round
    } else if (x < y) {
      ++sumY; // Chris wins the round
    }
    // If x == y, no one wins the round (draw)
  }
  if (sumX > sumY) {
    puts("Mishka"); // Mishka is the overall winner
  } else if (sumX < sumY) {
    puts("Chris"); // Chris is the overall winner
  } else if (sumX == sumY) {
    puts("Friendship is magic!^^"); // Draw result
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/