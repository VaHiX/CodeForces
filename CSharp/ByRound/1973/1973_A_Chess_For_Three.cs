// Problem: CF 1973 A - Chess For Three
// https://codeforces.com/contest/1973/problem/A

using System;
public class ChessForThree {
  /*
   * Problem: Determine the maximum number of draws in a chess game among three players,
   * given their final scores. Each game awards 2 points to winner, 0 to loser, and 1 to each in case of draw.
   * 
   * Algorithm:
   * 1. Check if total points is even (as in every match, total points awarded is 2).
   * 2. Simulate maximizing draws by reducing scores from highest to lowest.
   * 3. When p2 > 0, reduce scores in a way that maximizes draws:
   *    - If p1 == 0, reduce p2 and p3 (assumes draw between p2 and p3).
   *    - If p2 == p3, reduce p2 and p1 (assumes draw between p2 and p1).
   *    - Otherwise, reduce p3 and p1 (assumes draw between p3 and p1).
   * 4. Count each such move as one potential draw.
   * 
   * Time Complexity: O(p2) in worst case, but since p2 is bounded (0-30), it's effectively O(1).
   * Space Complexity: O(1), only using a few variables.
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      byte p1 = byte.Parse(parts[0]);
      byte p2 = byte.Parse(parts[1]);
      byte p3 = byte.Parse(parts[2]);
      short ans = 0;
      // If total points is odd, it's impossible to have valid game outcomes
      if ((p1 + p2 + p3) % 2 > 0)
        ans = -1;
      else
        // Simulate the game process by reducing p2 to zero, maximizing draws at each step
        while (p2 > 0) {
          if (p1 == 0) {
            p2--;
            p3--;
          } else if (p2 == p3) {
            p2--;
            p1--;
          } else {
            p3--;
            p1--;
          }
          ans++;
        }
      Console.WriteLine(ans);
    }
  }
}

// https://github.com/VaHiX/CodeForces/