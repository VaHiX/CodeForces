// Problem: CF 1797 C - Li Hua and Chess
// https://codeforces.com/contest/1797/problem/C

/*
 * Problem: Li Hua and Chess
 * 
 * Purpose: 
 *   This code solves an interactive problem where Li Hua needs to determine the position of a king
 *   on an n×m chessboard using at most 3 queries. Each query tells the minimum number of moves
 *   a king needs to reach a specified cell.
 *   
 *   The solution uses geometric reasoning based on the king's movement distance.
 *   The key idea is to:
 *   1. Query (1,1) to find the minimum steps to reach it.
 *   2. Use this information to deduce the king's position relative to a second query point.
 *   3. Then perform a third query to confirm the exact row/column.
 * 
 * Algorithm:
 *   - Start by querying (1,1) to get distance d1.
 *   - Based on d1, choose a second query point (x2, y2) such that it's at most d1 steps away from (1,1).
 *   - Query (x2, y2) and get distance d2.
 *   - Using the two distances and the constraints of the board, deduce possible positions.
 *   - Perform a third query to disambiguate the position.
 * 
 * Time Complexity: O(1) - constant number of operations per test case.
 * Space Complexity: O(1) - only a few variables are used regardless of input size.
 */

using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int fyt = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int hz = 0; hz < fyt; hz++) {
      var a =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      Console.WriteLine("? 1 1"); // First query at corner (1,1)
      int c1 = int.Parse(Console.ReadLine()); // Distance from king to (1,1)
      
      // Calculate a second test point (x2, y2) such that it's at most c1 steps from (1,1)
      int x2 = Math.Min(c1 + 1, a[0]); 
      int y2 = Math.Min(c1 + 1, a[1]);
      Console.WriteLine("? " + x2.ToString() + " " + y2.ToString());
      int c2 = int.Parse(Console.ReadLine()); // Distance from king to (x2, y2)
      
      // Calculate backtracking point (x3, y3) using the second query
      int x3 = Math.Max(x2 - c2, 1);
      int y3 = Math.Max(y2 - c2, 1);
      
      int x4 = 0;
      int y4 = 0;
      
      // If x2 is at max row, then the king must be in the same row but shifted in column
      if (c1 + 1 > a[0]) {
        x4 = x3;
        y4 = y2;
        Console.WriteLine("! " + x4.ToString() + " " + y4.ToString());
        continue;
      }
      // If y2 is at max column, then the king must be in the same column but shifted in row
      if (c1 + 1 > a[1]) {
        x4 = x2;
        y4 = y3;
        Console.WriteLine("! " + x4.ToString() + " " + y4.ToString());
        continue;
      }
      
      // Final third query to determine final row/column
      Console.WriteLine("? " + x2.ToString() + " " + y3.ToString());
      int c3 = int.Parse(Console.ReadLine());
      
      // Based on the result of third query, determine exact location
      if (c3 == 0) {
        x4 = x2;
        y4 = y3; // King at (x2, y3)
      } else {
        x4 = x3;
        y4 = y2; // King at (x3, y2)
      }
      
      Console.WriteLine("! " + x4.ToString() + " " + y4.ToString());
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/