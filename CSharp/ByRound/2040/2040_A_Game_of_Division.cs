// Problem: CF 2040 A - Game of Division
// https://codeforces.com/contest/2040/problem/A

using System;
using System.Collections.Generic;
public class GameOfDivision {
  /*
   * Problem: Game of Division
   * 
   * Algorithm:
   * - The first player wants to choose an index such that there exists another index
   *   where the absolute difference is NOT divisible by k.
   * - For this to happen, we need at least one element that has a remainder different
   *   from all other elements when divided by k.
   * - We group elements by their modulo k value.
   * - If there is a group with only one element, that element can be chosen by the first player.
   *   Because the difference with any other element will not be divisible by k.
   * 
   * Time Complexity: O(n * k) where n is the length of array and k is the given number.
   * Space Complexity: O(n + k) for storing the list of indices for each remainder class.
   * 
   * Techniques:
   * - Modular arithmetic
   * - Grouping elements by remainders
   * - Greedy choice of single-element remainder class
   */
  public static void Main() {
    byte t = byte.Parse(Console.ReadLine());
    for (byte i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      byte n = byte.Parse(parts[0]);
      byte k = byte.Parse(parts[1]);
      parts = Console.ReadLine().Split();
      List<byte>[] mods = new List<byte>[k]; // Array of lists to store indices grouped by remainder
      for (byte j = 0; j < n; j++) {
        byte aj = byte.Parse(parts[j]);
        byte r = Convert.ToByte(aj % k); // Calculate remainder
        if (mods[r] == null)
          mods[r] = new List<byte>(); // Initialize list if not already
        mods[r].Add(j); // Add index to corresponding remainder list
      }
      bool win = false;
      byte idx = 0;
      for (byte j = 0; j < k && !win; j++)
        if (mods[j] != null && mods[j].Count == 1) { // If there is only one element with this remainder
          win = true;
          idx = Convert.ToByte(mods[j][0] + 1); // Index in 1-based notation
        }
      Console.WriteLine(win ? "YES" : "NO");
      if (win)
        Console.WriteLine(idx);
    }
  }
}

// https://github.com/VaHiX/CodeForces/