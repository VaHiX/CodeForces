// Problem: CF 2148 B - Lasers
// https://codeforces.com/contest/2148/problem/B

/*
 * Problem: B. Lasers
 * 
 * Purpose: This program calculates the minimum number of laser crossings required 
 *          to travel from (0,0) to (x,y) in a 2D plane with horizontal and vertical lasers.
 * 
 * Algorithm/Techniques:
 *   - Use greedy approach to find the minimal number of crossings.
 *   - For horizontal lasers: Count how many are between 0 and y.
 *   - For vertical lasers: Count how many are between 0 and x.
 *   - The minimum crossing number is the minimum of (number of horizontal lasers + 1) 
 *     and (number of vertical lasers + 1), but since we start at (0,0) and end at (x,y),
 *     we need to consider the path going through these laser lines optimally.
 *   
 * Time Complexity: O(n log n + m log m) due to sorting (if required) or just linear scan.
 * Space Complexity: O(1) excluding input storage.
 */

using System;
public class HelloWorld {
  public static void Main(string[] args) {
    int T = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < T; i++) {
      int[] input = Array.ConvertAll(Console.ReadLine().Split(), int.Parse); // Parse n, m, x, y
      int n = input[0];
      int m = input[1];
      int x = input[2];
      int y = input[3];
      
      // Skip reading empty lines
      Console.ReadLine();
      Console.ReadLine();
      
      // Print the sum of n and m (this line seems like placeholder/incorrect logic)
      // Expected logic would count laser crossings, but not present in given code.
      Console.WriteLine(n + m);
    }
  }
}


// https://github.com/VaHiX/codeForces/