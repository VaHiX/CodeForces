// Problem: CF 2109 B - Slice to Survive
// https://codeforces.com/contest/2109/problem/B

/* 
 * Problem: B. Slice to Survive
 * 
 * Purpose: Determine the minimum number of turns required to reduce an n×m grid to a single cell,
 *          given that Mouf cuts the grid optimally to minimize turns, and Fouad moves the monster
 *          optimally to maximize turns.
 * 
 * Algorithm:
 * - The key idea is to model how each player plays optimally.
 * - Mouf chooses the cut (either row or column) that minimizes the maximum number of steps needed to reduce the grid.
 * - Fouad, on the other hand, chooses a move that maximizes the number of steps required, effectively moving towards
 *   the side furthest from the center in terms of required operations.
 * - We use a helper function `calc` to compute the minimum number of cuts (division by 2 or adding 1 and dividing) needed
 *   to reduce a number to 1, which mimics binary reduction steps.
 * 
 * Time Complexity: O(1) per test case — Each calculation involves constant-time operations and a fixed number of steps.
 * Space Complexity: O(1) — Only a fixed amount of memory is used for variables.
 */
using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read grid dimensions and monster position
      var h = long.Parse(line[0]);
      var w = long.Parse(line[1]);
      var a = long.Parse(line[2]);
      var b = long.Parse(line[3]);
      getAns(h, w, a, b); // Calculate and print answer for current test case
    }
  }
  
  static int calc(long t) {
    var c = 0; // Count of operations to reduce t to 1
    while (t > 1) {
      if (t % 2 == 0)
        t /= 2; // If even, divide by 2
      else
        t = (t + 1) / 2; // If odd, add 1 and divide by 2
      c++; // Increment operation count
    }
    return c;
  }
  
  static void getAns(long h, long w, long a, long b) {
    var c1 = Min(calc(b), calc(w - b + 1)); // Minimum cuts needed for column
    var c2 = Min(calc(a), calc(h - a + 1)); // Minimum cuts needed for row
    var ans = Min(calc(h) + c1, calc(w) + c2); // Compute optimal turns based on strategy
    Console.WriteLine(ans + 1); // Add one because the first move starts the count from 1
  }
}


// https://github.com/VaHiX/codeForces/