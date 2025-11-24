// Problem: CF 1700 F - Puzzle
// https://codeforces.com/contest/1700/problem/F

/*
Purpose: Solve a puzzle problem where we need to transform a 2xN binary matrix into a target configuration using adjacent swaps.
Algorithm: 
    - For each column, calculate the difference in counts of 0s and 1s between the current and target matrices.
    - Use greedy approach to balance the differences and count the minimum swaps.
    - If total mismatch is not zero, return -1.

Time Complexity: O(n) where n is the number of columns.
Space Complexity: O(1) ignoring input storage.
*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace CodeForces {
internal class Program {
  static void Main(string[] args) {
    int n = Read.Int(); // Read number of columns
    int[,] notSolved = new int[2, n]; // Current state of puzzle
    int[,] solved = new int[2, n]; // Target state of puzzle
    int ch0 = 0, ch1 = 0; // Track differences in counts of 0s and 1s
    long ch = 0; // Total number of operations
    for (int i = 0; i < 2; i++) {
      int[] line = Read.Ints(); // Read current row
      for (int j = 0; j < n; j++) {
        notSolved[i, j] = line[j]; // Store in notSolved matrix
      }
    }
    for (int i = 0; i < 2; i++) {
      int[] line = Read.Ints(); // Read target row
      for (int j = 0; j < n; j++) {
        solved[i, j] = line[j]; // Store in solved matrix
      }
    }
    for (int i = 0; i < n; i++) {
      ch0 += (notSolved[0, i] - solved[0, i]); // Difference for row 0
      ch1 += (notSolved[1, i] - solved[1, i]); // Difference for row 1
      // Adjust differences greedily to minimize swaps
      while (ch0 > 0 && ch1 < 0) {
        ch0--;
        ch1++;
        ch++; // Increment swap counter
      }
      while (ch0 < 0 && ch1 > 0) {
        ch1--;
        ch0++;
        ch++; // Increment swap counter
      }
      ch += Math.Abs(ch0) + Math.Abs(ch1); // Add remaining differences to total swaps
    }
    if (ch0 > 0 || ch1 > 0) {
      Console.WriteLine("-1"); // If imbalance remains, impossible to solve
      return;
    }
    Console.WriteLine(ch); // Output total swaps needed
  }
  class Read {
    public static string String() { return Console.ReadLine(); }
    public static char Char() { return char.Parse(String()); }
    public static int Int() { return int.Parse(String()); }
    public static long Long() { return long.Parse(String()); }
    public static double Double() { return double.Parse(String()); }
    public static string[] Strings() { return String().Split(' '); }
    public static char[] Chars() {
      return Array.ConvertAll(String().Split(' '), char.Parse);
    }
    public static int[] Ints() {
      return Array.ConvertAll(String().Split(' '), int.Parse);
    }
    public static long[] Longs() {
      return Array.ConvertAll(String().Split(' '), long.Parse);
    }
    public static double[] Doubles() {
      return Array.ConvertAll(String().Split(' '), double.Parse);
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/