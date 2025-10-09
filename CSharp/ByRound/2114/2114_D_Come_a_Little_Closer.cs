// Problem: CF 2114 D - Come a Little Closer
// https://codeforces.com/contest/2114/problem/D

/*
 * Problem: D. Come a Little Closer
 * Purpose: Find the minimum cost to destroy all monsters by moving one monster,
 *          then selecting a rectangle that covers all monsters.
 * Algorithm:
 *   - For each monster, consider it as the one being moved.
 *   - Calculate the minimal rectangle that can cover all monsters after this move.
 *   - The key insight is to minimize area of bounding box around all points except
 *     possibly one which is moved. We precompute sorted x and y coordinates to efficiently
 *     find candidates for bounding rectangle edges.
 * 
 * Time Complexity: O(n log n) per test case (due to sorting)
 * Space Complexity: O(n) for storing input data and arrays
 */

using static System.Math;
using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      getAns(n);
    }
  }
  
  // Function to compute the minimum coins needed to destroy all monsters
  static void getAns(int n) {
    var input = new(int x, int y)[n];
    var a = new int[n];   // x-coordinates
    var b = new int[n];   // y-coordinates
    
    for (int i = 0; i < n; i++) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var x = int.Parse(line[0]);
      var y = int.Parse(line[1]);
      input[i] = (x, y);
      a[i] = x;
      b[i] = y;
    }
    
    Array.Sort(a);  // Sort x-coordinates
    Array.Sort(b);  // Sort y-coordinates
    
    if (n == 1) {
      Console.WriteLine(1);
      return;
    }

    var ans = long.MaxValue;  // Initialize answer to maximum possible value

    // Iterate through each monster, treating it as the one we can move
    foreach (var z in input) {
      // Determine left and right x boundaries of the bounding box excluding current point
      var aL = a[0] == z.x ? a[1] : a[0];
      var ar = a[n - 1] == z.x ? a[n - 2] : a[n - 1];
      var aa = ar - aL + 1;  // Width of region excluding one x coordinate

      // Determine upper and lower y boundaries of the bounding box excluding current point
      var bL = b[0] == z.y ? b[1] : b[0];
      var br = b[n - 1] == z.y ? b[n - 2] : b[n - 1];
      var bb = br - bL + 1;  // Height of region excluding one y coordinate

      var tans = (long)aa * bb;  // Initial area calculation
      
      // If moving the monster reduces cost, adjust accordingly
      if (tans < n)
        tans = (Max(aa, bb) + 1) * Min(aa, bb);
      
      ans = Min(ans, tans);  // Update global minimum
    }
    
    Console.WriteLine(Max(ans, n));  // Ensure we can't go below n (each monster needs at least 1 cell)
  }
}


// https://github.com/VaHiX/CodeForces/