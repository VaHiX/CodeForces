// Problem: CF 1994 A - Diverse Game
// https://codeforces.com/contest/1994/problem/A

using System;
public class DiverseGame {
  /*
   * Problem: Construct a matrix b such that all elements are distinct and from 1 to n*m,
   *          and for all i,j, a[i,j] != b[i,j].
   *          
   * Algorithm:
   *   - If n == 1 and m == 1, it's impossible (only one element, so a[0,0] must equal b[0,0]).
   *   - Otherwise, we can use a cyclic shift approach:
   *     - Take the first element of the matrix (a[0,0]) and store it in tmp.
   *     - For each element in the matrix in row-major order:
   *       - If not the last element in row, assign element to the right.
   *       - Else if not the last row, assign element from the start of next row.
   *       - Else, assign the stored tmp value (last element).
   *   - This ensures no element equals its original position.
   *   
   * Time Complexity: O(n * m) - We process each element once.
   * Space Complexity: O(n * m) - To store the matrix a.
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      byte n = byte.Parse(parts[0]);
      byte m = byte.Parse(parts[1]);
      byte[,] a = new byte[n, m];
      for (byte j = 0; j < n; j++) {
        parts = Console.ReadLine().Split();
        for (byte k = 0; k < m; k++)
          a[j, k] = byte.Parse(parts[k]);
      }
      if (n == 1 && m == 1)
        Console.WriteLine(-1);
      else {
        byte tmp = a[0, 0];
        for (byte j = 0; j < n; j++) {
          for (byte k = 0; k < m; k++) {
            if (k < m - 1)
              a[j, k] = a[j, k + 1];       // Shift right if not last in row
            else if (j < n - 1)
              a[j, k] = a[j + 1, 0];       // Shift down to next row first element
            else
              a[j, k] = tmp;               // Assign stored first element to last position
            Console.Write(a[j, k]);
            if (k < m - 1)
              Console.Write(" ");
          }
          Console.WriteLine();
        }
      }
    }
  }
}

// https://github.com/VaHiX/CodeForces/