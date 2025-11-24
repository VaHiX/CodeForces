// Problem: CF 2093 D - Skibidi Table
// https://codeforces.com/contest/2093/problem/D

/*
 * Code Purpose:
 * This program solves the Skibidi Table problem where a 2^n x 2^n table is filled recursively
 * in a specific order: top-left, bottom-right, bottom-left, top-right for each quadrant.
 * It supports two types of queries:
 * 1. Given coordinates (x,y), find the number at that position.
 * 2. Given a number d, find its coordinates (x,y).
 *
 * Algorithms/Techniques:
 * - Recursive decomposition of the table into four quadrants.
 * - For each recursive call, determine which quadrant the query belongs to.
 * - Use bit manipulation for efficient calculation of powers of 2.
 *
 * Time Complexity: O(n * q) where n is the size of the table (2^n x 2^n) and q is the number of queries.
 * Space Complexity: O(n) due to the recursion depth (height of the recursive tree).
 */

using System;
class Program {
  // Returns the value at position (x, y) in the 2^n x 2^n table
  static long GetVal(int n, int x, int y) {
    // Base case: for 2x2 table, fill as described in the problem
    if (n == 1) {
      if (x == 1 && y == 1)
        return 1;
      if (x == 2 && y == 2)
        return 2;
      if (x == 2 && y == 1)
        return 3;
      return 4;
    }
    
    // Calculate half of the current table size
    int half = 1 << (n - 1);
    // Base value represents how many elements are in a quadrant (2^(2*(n-1)))
    long baseVal = 1L << (2 * (n - 1));
    
    // Determine the quadrant and recursively process:
    if (x <= half && y <= half)
      // Top-left quadrant: no offset
      return 0 * baseVal + GetVal(n - 1, x, y);
    if (x > half && y > half)
      // Bottom-right quadrant: offset by 1 * baseVal
      return 1 * baseVal + GetVal(n - 1, x - half, y - half);
    if (x > half && y <= half)
      // Bottom-left quadrant: offset by 2 * baseVal
      return 2 * baseVal + GetVal(n - 1, x - half, y);
    // Top-right quadrant: offset by 3 * baseVal
    return 3 * baseVal + GetVal(n - 1, x, y - half);
  }
  
  // Returns the coordinates (x, y) of the number d in the table
  static (int, int) GetCoords(int n, long d) {
    // Base case: for 2x2 table, return fixed positions
    if (n == 1) {
      if (d == 1)
        return (1, 1);
      if (d == 2)
        return (2, 2);
      if (d == 3)
        return (2, 1);
      return (1, 2);
    }
    
    // Calculate half of the current table size
    int half = 1 << (n - 1);
    // Base value represents how many elements are in a quadrant (2^(2*(n-1)))
    long baseVal = 1L << (2 * (n - 1));
    
    // Determine which quadrant the number d belongs to
    int quad = (int)((d - 1) / baseVal);
    long rem = d - quad * baseVal;
    
    // Recursively find the coordinates in the smaller quadrant
    var (rx, ry) = GetCoords(n - 1, rem);
    
    // Adjust the coordinates based on the quadrant number:
    if (quad == 0)
      return (rx, ry);                   // Top-left
    if (quad == 1)
      return (rx + half, ry + half);     // Bottom-right
    if (quad == 2)
      return (rx + half, ry);            // Bottom-left
    return (rx, ry + half);              // Top-right
  }
  
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      int q = int.Parse(Console.ReadLine());
      while (q-- > 0) {
        string line = Console.ReadLine();
        string[] parts = line.Split();
        if (parts[0] == "->") {
          int x = int.Parse(parts[1]);
          int y = int.Parse(parts[2]);
          Console.WriteLine(GetVal(n, x, y));
        } else {
          long d = long.Parse(parts[1]);
          var (x, y) = GetCoords(n, d);
          Console.WriteLine(x + " " + y);
        }
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/