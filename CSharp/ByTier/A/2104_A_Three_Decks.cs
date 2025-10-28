// Problem: CF 2104 A - Three Decks
// https://codeforces.com/contest/2104/problem/A

/*
 * Problem: Three Decks
 * Purpose: Determine if it's possible to make all three decks have equal number of cards 
 *          by moving some cards from the third deck to the first and second decks.
 * Algorithm: Mathematical check based on total sum and distribution constraints.
 * Time Complexity: O(1) - Constant time per test case.
 * Space Complexity: O(1) - Only using a constant amount of extra space.
 * 
 * Approach:
 * 1. Calculate how many cards are needed to make all decks equal.
 * 2. If the total number of cards can be evenly distributed among 3 decks, then it's possible.
 * 3. Check whether it's feasible given that we can only move from deck 3 to decks 1 and 2.
 */

using System;
using System.Numerics;
class JustLearning {
  static void Main(string[] args) {
    int t = Convert.ToInt32(Console.ReadLine());
    while (t > 0) {
      string[] numset = Console.ReadLine().Split();
      int[] intnumset = Array.ConvertAll(numset, int.Parse);
      // Calculate how many cards are left after moving from deck 3
      int cardleft1stcheck = intnumset[2] - (intnumset[1] - intnumset[0]);
      // If remaining cards in deck 3 is less than deck 2's current count, impossible to balance
      if (cardleft1stcheck < intnumset[1]) {
        Console.WriteLine("NO");
      } else if ((cardleft1stcheck - intnumset[1]) % 3 == 0) {
        // If difference between new deck 1 and deck 2 is divisible by 3, valid distribution
        Console.WriteLine("YES");
      } else {
        Console.WriteLine("NO");
      }
      t--;
    }
  }
}


// https://github.com/VaHiX/codeForces/