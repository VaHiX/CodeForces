// Problem: CF 2104 C - Card Game
// https://codeforces.com/contest/2104/problem/C

/*
C. Card Game
Algorithms/Techniques: Game Theory, Greedy Approach, Simulation

Time Complexity: O(n^2) per test case, where n is the number of cards.
Space Complexity: O(n) for storing the input string of cards.

The problem involves a game where Alice and Bob play with n cards numbered 1 to n.
Card i beats card j if i > j, except card 1 beats card n.
Players play optimally and the winner is determined by who can force a win.

This solution uses a simulation approach:
- For each of Alice's cards, check if it's safe (i.e., no Bob's card can beat it).
- If Alice has any safe card, she wins immediately.
- Otherwise, Bob wins.
*/

using System;
class Program {
  static bool CanBeat(long attacker, long defender, long total) {
    if (attacker == total && defender == 1)
      return false; // Special case: card 1 beats card n
    if (attacker == 1 && defender == total)
      return true;  // Special case: card 1 beats card n
    return attacker > defender; // Normal beat condition
  }
  static string FindWinner(long n, string s) {
    for (long pos = 0; pos < n; pos++) {
      if (s[(int)pos] != 'A') // Only consider Alice's cards
        continue;
      bool isSafe = true;
      for (long rival = 0; rival < n; rival++) {
        if (s[(int)rival] == 'B' && CanBeat(rival + 1, pos + 1, n)) { // If Bob's card can beat Alice's card
          isSafe = false;
          break;
        }
      }
      if (isSafe)
        return "Alice"; // Found a safe card for Alice
    }
    return "Bob"; // No safe card found, Bob wins
  }
  static void Solve() {
    long testCases = long.Parse(Console.ReadLine());
    while (testCases-- > 0) {
      long n = long.Parse(Console.ReadLine());
      string players = Console.ReadLine();
      Console.WriteLine(FindWinner(n, players));
    }
  }
  static void Main() { Solve(); }
}


// https://github.com/VaHiX/CodeForces/