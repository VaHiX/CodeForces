// Problem: CF 1904 A - Forked!
// https://codeforces.com/contest/1904/problem/A

/*
 * Problem: Forked!
 * Purpose: Determine the number of positions on an infinite chessboard where a modified knight (with move pattern a,b) 
 *          can attack both the king and queen simultaneously (a fork).
 * 
 * Algorithm:
 * 1. For each test case:
 *    - Read knight move parameters (a, b) and positions of king (xk, yk) and queen (xq, yq).
 *    - Generate all possible knight moves from the king's position (8 possible moves if a != b, 4 if a == b).
 *    - Check for each such move if the knight can also attack the queen in one of its valid moves.
 *    - Count such valid positions.
 *
 * Time Complexity: O(1) per test case, since a fixed number of operations (8 or 4 moves) are performed.
 * Space Complexity: O(1), as only a fixed-size array and a few variables are used.
 */

using System;
using System.Text;
public class Forked {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int a = int.Parse(parts[0]); // Knight's first move distance
      int b = int.Parse(parts[1]); // Knight's second move distance
      parts = Console.ReadLine().Split();
      int xk = int.Parse(parts[0]); // King's x-coordinate
      int yk = int.Parse(parts[1]); // King's y-coordinate
      parts = Console.ReadLine().Split();
      int xq = int.Parse(parts[0]); // Queen's x-coordinate
      int yq = int.Parse(parts[1]); // Queen's y-coordinate
      
      // Number of possible knight moves based on whether a and b are equal
      byte n = Convert.ToByte(a == b ? 4 : 8);
      
      // Arrays to store coordinates of potential knight positions
      int[] x = new int[n];
      int[] y = new int[n];
      
      // Array of knight move deltas (8 or 4 total moves depending on a == b)
      int[] dx = new int[8] { a, a, -a, -a, b, b, -b, -b };
      int[] dy = new int[8] { -b, b, -b, b, -a, a, -a, a };
      
      byte ansi = 0; // Counter for valid fork positions
      
      // Iterate through each possible knight move from king's position
      for (byte j = 0; j < n; j++) {
        x[j] = xk + dx[j]; // Calculate new x-coordinate of knight
        y[j] = yk + dy[j]; // Calculate new y-coordinate of knight
        
        // Check if this position can also attack the queen
        // A knight attacks the queen if the distance matches (a,b) or (b,a)
        if ((Math.Abs(xq - x[j]) == a && Math.Abs(yq - y[j]) == b) ||
            (Math.Abs(xq - x[j]) == b && Math.Abs(yq - y[j]) == a))
          ansi++; // Increment counter if valid
      }
      
      // Append result for current test case
      ans.Append(ansi);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/