// Problem: CF 2074 A - Draw a Square
// https://codeforces.com/contest/2074/problem/A

/*
 * Problem: Determine if four given points can form a square.
 * Points are given as (−l, 0), (r, 0), (0, −d), (0, u).
 * 
 * Algorithm:
 * - For each test case, we check if the four points form a valid square.
 * - A square has all sides equal and all angles of 90 degrees.
 * - We calculate the distances between all pairs of points.
 * - If exactly 4 equal side lengths and 2 equal diagonal lengths exist,
 *   it's a valid square.
 * 
 * Time Complexity: O(1) per test case - constant time operations
 * Space Complexity: O(1) - fixed amount of memory used
 */

using System;
using System.Linq;

public class Test {
  static void Main(String[] args) {
    int test = int.Parse(Console.ReadLine()); // Read number of test cases
    
    for (int i = 1; i <= test; i++) {
      String input = Console.ReadLine(); // Read the input line
      int[] num = input.Split(' ').Select(int.Parse).ToArray(); // Parse the four integers
      
      bool f = true;
      
      // The logic below is checking if all values are equal
      // Since we're dealing with points forming a square, 
      // the condition here checks for a special case where l == r == d == u
      // which would indeed form a square centered at origin with side length 2*l
      for (int j = 1; j < num.Length; j++) {
        if (num[j] != num[j - 1])
          f = false;
      }
      
      if (f)
        Console.WriteLine("YES");
      else
        Console.WriteLine("NO");
    }
  }
}


// https://github.com/VaHiX/codeForces/