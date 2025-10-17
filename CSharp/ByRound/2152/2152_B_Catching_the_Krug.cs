// Problem: CF 2152 B - Catching the Krug
// https://codeforces.com/contest/2152/problem/B

/*
 * Problem: B. Catching the Krug
 * Purpose: Determine the Krug's survival time when both players play optimally on an n x n grid.
 *          The Krug starts at (rK, cK), Doran at (rD, cD). 
 *          Krug moves like a rook (up, down, left, right) but not diagonally.
 *          Doran moves like a queen (including diagonals).
 *          
 * Algorithms/Techniques:
 *   - Game Theory: Optimal play by both players
 *   - Distance Calculation: Manhattan distance to determine minimum steps needed for Doran to catch Krug
 *   - Special Cases: Horizontal or vertical alignment of players 
 *   
 * Time Complexity: O(1) per test case - constant time operations
 * Space Complexity: O(1) - only using a fixed amount of variables regardless of input size
 */

using System;
class Program {
  static void Main() {
    int T;
    if (!int.TryParse(Console.ReadLine(), out T))
      return;
    while (T-- > 0) {
      var input = Console.ReadLine().Split();
      long n = long.Parse(input[0]); // Grid size
      long rk = long.Parse(input[1]); // Krug's row
      long ck = long.Parse(input[2]); // Krug's column
      long rd = long.Parse(input[3]); // Doran's row
      long cd = long.Parse(input[4]); // Doran's column
      long ans = 0;
      
      // If Krug and Doran are on the same row
      if (rk == rd) {
        // Calculate minimum steps to reach Krug from either side of the row
        ans = (ck < cd) ? cd : (n - cd);
      } 
      // If Krug and Doran are on the same column
      else if (ck == cd) {
        // Calculate minimum steps to reach Krug from either side of the column
        ans = (rk < rd) ? rd : (n - rd);
      } 
      else {
        // Otherwise, compute best move for both players based on distance and alignment
        long tr = (rk < rd) ? 0 : n; // Target row (0 or n)
        long tc = (ck < cd) ? 0 : n; // Target column (0 or n)
        ans = Math.Max(Math.Abs(rd - tr), Math.Abs(cd - tc));
      }
      
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/