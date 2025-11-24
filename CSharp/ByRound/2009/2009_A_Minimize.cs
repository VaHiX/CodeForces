// Problem: CF 2009 A - Minimize!
// https://codeforces.com/contest/2009/problem/A

﻿/*
 * Problem: Minimize!
 * Task: Given two integers a and b (a <= b), find the minimum value of (c - a) + (b - c) 
 *       for all possible integer values of c where a <= c <= b.
 * 
 * Algorithm/Techniques: 
 *   - Mathematical simplification: (c - a) + (b - c) = b - a
 *   - Since the expression is independent of c, the minimum value is always b - a.
 * 
 * Time Complexity: O(1) - Constant time for each test case
 * Space Complexity: O(1) - Constant space usage
 */

using System;
namespace SandBox {
internal class Program {
  public static void Main() {
    var t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) { // Process each test case
      var numbers = Console.ReadLine().Split(' '); // Split input line into two parts
      var leftBorder = int.Parse(numbers[0]); // Parse the first integer as left border
      var rightBorder = int.Parse(numbers[1]); // Parse the second integer as right border
      Console.WriteLine(rightBorder - leftBorder); // Output the difference (minimum value)
    }
  }
}
}


// https://github.com/VaHiX/codeForces/