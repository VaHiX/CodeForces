// Problem: CF 2033 A - Sakurako and Kosuke
// https://codeforces.com/contest/2033/problem/A

/*
 * Problem: Sakurako and Kosuke
 * Purpose: Simulate a game where Sakurako and Kosuke alternately move a dot on a coordinate line.
 *          Sakurako moves the dot negatively, Kosuke moves it positively. Game ends when |x| > n.
 *          Determine who makes the last move.
 * 
 * Algorithms/Techniques:
 *   - Simulation with alternating turns
 *   - Directional movement based on turn (odd/even)
 *   - Absolute value comparison to determine end condition
 * 
 * Time Complexity: O(n) per test case, since in worst case we may need to simulate up to n moves.
 * Space Complexity: O(1), only using a constant amount of extra variables.
 */

using System;
namespace ASD {
class Program {
  static void Main() {
    int b = int.Parse(Console.ReadLine()); // Read number of games
    for (int i = 0; i < b; i++) {
      int n = int.Parse(Console.ReadLine()); // Read the limit n for current game
      int x = 0; // Current position of the dot, starts at 0
      int v = 1; // Move number (used to calculate step size: 2*v - 1)
      string player = "Kosuke"; // Tracks whose turn it is; Kosuke starts
      while (true) {
        int r = 2 * v - 1; // Calculate step size for current move
        if (v % 2 == 1) { // If v is odd, Sakurako's turn (negative direction)
          x -= r;
          player = "Sakurako";
        } else { // If v is even, Kosuke's turn (positive direction)
          x += r;
          player = "Kosuke";
        }
        if (Math.Abs(x) > n) { // Check if absolute value exceeds n
          Console.WriteLine(player); // Output the player who made the last move
          break;
        }
        v++; // Increment move number for next iteration
      }
    }
  }
}
}


// https://github.com/VaHiX/codeForces/