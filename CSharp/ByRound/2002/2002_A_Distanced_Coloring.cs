// Problem: CF 2002 A - Distanced Coloring
// https://codeforces.com/contest/2002/problem/A

/*
 * Problem: Grid Coloring with Minimum Colors
 * 
 * Purpose: Given an n×m grid and a magic constant k, color the grid such that 
 *          any two cells with the same color are at least distance k apart 
 *          (in terms of maximum of row/column differences). Find the minimum 
 *          number of colors needed.
 * 
 * Algorithm: Distanced Coloring
 * 
 * Approach:
 * - To minimize colors, we use a grid-based coloring strategy where we place 
 *   cells with the same color in a pattern that ensures they are at least k 
 *   units apart.
 * - We can cover the grid by placing a "color block" of size k×k.
 * - Within each block, we assign one color to a cell, ensuring no conflict.
 * - The number of such blocks needed in the grid determines the colors required.
 * 
 * Time Complexity: O(1) per test case — all operations are constant time.
 * Space Complexity: O(1) — only using fixed amount of variables regardless of input size.
 */

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read n, m, k from input
      var n = int.Parse(line[0]);
      var m = int.Parse(line[1]);
      var k = int.Parse(line[2]);
      getAns(n, m, k); // Calculate and print the answer for this case
    }
  }
  
  static void getAns(int n, int m, int k) {
    var a = Min(n, k); // Determine how many rows we can color with one color in vertical direction (at most k)
    var b = Min(m, k); // Determine how many columns we can color with one color in horizontal direction (at most k)
    Console.WriteLine(a * b); // Output the result
  }
}


// https://github.com/VaHiX/codeForces/