// Problem: CF 1909 A - Distinct Buttons
// https://codeforces.com/contest/1909/problem/A

/*
 * Purpose: Determine if all special points can be visited using at most 3 distinct buttons
 *          (U, D, L, R) without breaking the controller.
 * 
 * Algorithm: 
 * - Find the bounding box of all special points.
 * - Check if the bounding box contains the origin (0,0).
 * - If the origin is contained within the bounding box, then we can visit all points
 *   using at most 3 buttons (since we never need to go in all 4 directions).
 * - If the origin is not contained, we must use all 4 buttons to reach all points.
 * 
 * Time Complexity: O(n) per test case, where n is the number of special points.
 * Space Complexity: O(n) for storing the coordinates.
 */
using System;
using System.Text;
public class DistinctButtons {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine());
      short[] x = new short[n];
      short[] y = new short[n];
      for (byte j = 0; j < n; j++) {
        string[] parts = Console.ReadLine().Split();
        x[j] = short.Parse(parts[0]);
        y[j] = short.Parse(parts[1]);
      }
      short xMin = x[0];
      short xMax = xMin;
      short yMin = y[0];
      short yMax = yMin;
      for (short j = 1; j < n; j++) {
        if (x[j] < xMin)
          xMin = x[j];
        else if (x[j] > xMax)
          xMax = x[j];
        if (y[j] < yMin)
          yMin = y[j];
        else if (y[j] > yMax)
          yMax = y[j];
      }
      // If the bounding box contains the origin (0,0), it is possible to visit all points with 3 buttons
      bool ansi = !(xMin < 0 && xMax > 0 && yMin < 0 && yMax > 0);
      ans.Append(ansi ? "YES" : "NO");
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/