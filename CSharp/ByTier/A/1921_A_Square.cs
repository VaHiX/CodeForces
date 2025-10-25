// Problem: CF 1921 A - Square
// https://codeforces.com/contest/1921/problem/A

/*
 * Problem: Find the area of a square given four corner points.
 * Algorithm/Techniques: 
 *   - Determine the bounding box of all four points.
 *   - The side length of the square is the maximum of width and height of the bounding box.
 *   - Area is side length squared.
 * 
 * Time Complexity: O(1) - We perform a constant number of operations for each test case.
 * Space Complexity: O(1) - We use only a fixed amount of extra space regardless of input size.
 */

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      long[] x = new long[4]; // Array to store x-coordinates of corners
      long[] y = new long[4]; // Array to store y-coordinates of corners
      for (int j = 0; j < 4; j++) {
        string[] input = Console.ReadLine().Split(); // Read and split input line
        x[j] = long.Parse(input[0]); // Parse and store x-coordinate
        y[j] = long.Parse(input[1]); // Parse and store y-coordinate
      }
      // Find minimum and maximum x and y coordinates to determine the bounding box
      long minX = Math.Min(Math.Min(x[0], x[1]), Math.Min(x[2], x[3]));
      long maxX = Math.Max(Math.Max(x[0], x[1]), Math.Max(x[2], x[3]));
      long minY = Math.Min(Math.Min(y[0], y[1]), Math.Min(y[2], y[3]));
      long maxY = Math.Max(Math.Max(y[0], y[1]), Math.Max(y[2], y[3]));
      
      // Side length of the square is the maximum of width and height
      long sideLength = Math.Max(maxX - minX, maxY - minY);
      
      // Calculate and output the area
      long area = sideLength * sideLength;
      Console.WriteLine(area);
    }
  }
}


// https://github.com/VaHiX/CodeForces/