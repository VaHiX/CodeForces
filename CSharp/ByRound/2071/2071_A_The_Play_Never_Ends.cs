// Problem: CF 2071 A - The Play Never Ends
// https://codeforces.com/contest/2071/problem/A

/*
 * Problem: A. The Play Never Ends
 * Algorithm/Techniques: Mathematical pattern recognition
 * 
 * The game involves three players (Sosai, Fofo, Hohai) playing table tennis in a rotating pattern.
 * In each match:
 * - Two players compete; one spectates.
 * - The winner and the spectator play next; loser becomes the new spectator.
 * - No player can play three times in a row.
 * 
 * Observing the pattern of who spectates:
 * - Match 1: Player 3 (index 2) spectates
 * - Match 2: Player 1 (index 0) spectates
 * - Match 3: Player 2 (index 1) spectates
 * - Match 4: Player 3 (index 2) spectates again
 * - And so on...
 * 
 * Pattern repeats every 3 matches: [2, 0, 1, 2, 0, 1, ...]
 * So, for k-th match, the spectator is at position (k - 1) % 3.
 * For the first match's spectator (index 2) to be the same in k-th match:
 * (k - 1) % 3 == 2 => k % 3 == 0
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var k = int.Parse(Console.ReadLine().Trim()); // Read k (the match number to check)
      k--; // Adjust for 0-based indexing
      Console.WriteLine(k % 3 == 0 ? "YES" : "NO"); // Check if k-th match has same spectator as first
    }
  }
}


// https://github.com/VaHiX/codeForces/