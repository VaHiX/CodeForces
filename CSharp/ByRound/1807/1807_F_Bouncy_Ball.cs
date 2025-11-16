// Problem: CF 1807 F - Bouncy Ball
// https://codeforces.com/contest/1807/problem/F

/*
 * Problem: F. Bouncy Ball
 * 
 * Algorithm/Techniques: Simulation with Bounce Handling
 * 
 * Time Complexity: O(n * m) per test case in the worst case, where n and m are the dimensions of the grid.
 * Space Complexity: O(n * m) for the visited state tracking 3D array.
 * 
 * The solution simulates the ball's movement in a grid, handling bounces when the ball hits walls.
 * It tracks visited states to detect cycles and avoid infinite loops.
 * 
 * Key aspects:
 * - The ball moves in one of four diagonal directions (DR, DL, UR, UL).
 * - When hitting a wall, direction is flipped along the axis of the wall.
 * - A 3D array is used to track visited (i, j, direction) states to detect cycles.
 * - If the ball reaches the target cell, we return the number of bounces.
 * - If a cycle is detected, we return -1.
 */

using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using System.Text;
using System;
class Solution {
  public static void Main(string[] args) {
    int t1 = Convert.ToInt32(Console.ReadLine());
    for (int a1 = 1; a1 <= t1; a1++) {
      string[] arr = Console.ReadLine().Split(' ');
      int res = 0;
      int n = Convert.ToInt32(arr[0]);
      int m = Convert.ToInt32(arr[1]);
      int i1 = Convert.ToInt32(arr[2]);
      int j1 = Convert.ToInt32(arr[3]);
      int i2 = Convert.ToInt32(arr[4]);
      int j2 = Convert.ToInt32(arr[5]);
      char di = arr[6][0]; // Direction component for rows
      char dj = arr[6][1]; // Direction component for columns
      int[,,] vv = new int[n + 5, m + 5, 4]; // Visited state tracking array for each (i,j) and direction index (0-3)
      int ii = 1; // Step size for row direction (1 or -1)
      int jj = 1; // Step size for column direction (1 or -1)
      if (di == 'U')
        ii = -1;
      if (dj == 'L')
        jj = -1;
      int ni = i1 + ii; // Next row position
      int nj = j1 + jj; // Next column position
      // Check if the initial move goes out of bounds
      if (ni < 1 || ni > n || nj < 1 || nj > m) {
        if (ni == 0)
          ii = 1; // Flip direction if hitting top wall
        if (ni == n + 1)
          ii = -1; // Flip direction if hitting bottom wall
        if (nj == 0)
          jj = 1; // Flip direction if hitting left wall
        if (nj == m + 1)
          jj = -1; // Flip direction if hitting right wall
        res++; // Increment bounce count
      }
      bool chk = true;
      if (i1 == i2 && j1 == j2) {
        chk = false; // If already at target, no movement needed
        res = 0;
      }
      while (chk) {
        i1 += ii; // Update current position
        j1 += jj;
        // Check if reached the target
        if (i1 == i2 && j1 == j2)
          break;
        ni = i1 + ii; // Predict next position
        nj = j1 + jj;
        // Check if bounce is needed
        if (ni < 1 || ni > n || nj < 1 || nj > m) {
          if (ni == 0)
            ii = 1; // Flip row direction
          if (ni == n + 1)
            ii = -1; // Flip row direction
          if (nj == 0)
            jj = 1; // Flip column direction
          if (nj == m + 1)
            jj = -1; // Flip column direction
          res++; // Increment bounce count
        }
        // Map direction to index (0-3) for state tracking
        int dp = 0;
        if (ii == 1 && jj == 1)
          dp = 0; // DR
        else if (ii == 1 && jj == -1)
          dp = 1; // DL
        else if (ii == -1 && jj == 1)
          dp = 2; // UR
        else if (ii == -1 && jj == -1)
          dp = 3; // UL
        // Check for cycle
        if (vv[i1, j1, dp] == 1) {
          res = -1; // Cycle detected, no solution
          break;
        }
        vv[i1, j1, dp] = 1; // Mark current state as visited
      }
      Console.WriteLine(res.ToString());
    }
  }
}


// https://github.com/VaHiX/CodeForces/