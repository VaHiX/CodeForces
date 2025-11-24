// Problem: CF 2009 D - Satyam and Counting
// https://codeforces.com/contest/2009/problem/D

/*
 * Problem: D. Satyam and Counting
 * 
 * Purpose: Count the number of distinct nondegenerate right triangles that can be formed
 *          from n distinct points in 2D coordinate plane where 0 <= y <= 1.
 * 
 * Algorithm:
 *   - Points are divided into two sets: y=0 (y0) and y=1 (y1).
 *   - For each triangle, one vertex must lie on y=0, another on y=1, and the third can be anywhere.
 *   - To form a right triangle with points from y=0 and y=1:
 *     - One angle is 90 degrees when the two points are horizontally aligned or vertically aligned.
 *     - For each point in y=0 and y=1 that share same x-coordinate, we count how many valid combinations exist.
 *     - Special cases for horizontal alignment (same x) and vertical alignment (different x but same y).
 * 
 * Time Complexity: O(n), where n is the number of points. Each point is processed once.
 * Space Complexity: O(n), for storing points in hashsets.
 */

using System.Collections.Generic;
using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read number of points
      var y0 = new HashSet<int>(); // Store x-coordinates of points where y=0
      var y1 = new HashSet<int>(); // Store x-coordinates of points where y=1
      for (int i = 0; i < n; i++) {
        string[] line = Console.ReadLine().Trim().Split(' ');
        var t = int.Parse(line[0]); // x-coordinate
        if (line[1] == "0")
          y0.Add(t);
        else
          y1.Add(t);
      }
      getAns(n, y0, y1); // Calculate result for current test case
    }
  }

  // Count how many elements of 'a' have both neighbors in 'b'
  static int count(HashSet<int> a, HashSet<int> b) {
    var count = 0;
    foreach (var z in a)
      if (b.Contains(z - 1) && b.Contains(z + 1)) // Check if z-1 and z+1 are both present
        count++;
    return count;
  }

  // Calculate answer using logic based on point sets y0 and y1
  static void getAns(int n, HashSet<int> y0, HashSet<int> y1) {
    var same = 0; // Count of x-coordinates that appear in both y0 and y1 (i.e., points having same x but different y)
    foreach (var z in y0) {
      if (y1.Contains(z)) // If this x coordinate exists in both sets
        same++;
    }
    var ans = (long)same * (n - 2); // For each common x, we can pick any of the (n - 2) others to form triangles
    ans += count(y0, y1); // Add contributions from symmetric cases
    ans += count(y1, y0); // Mirror case
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/